#include "datarecord.h"
#include "ui_datarecord.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <QVBoxLayout>
#include <QTextCodec>
#include <QDate>
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QStringList>
#include <QSvgGenerator>
#include <QPainter>
#include <QFileDialog>


DataRecord::DataRecord(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DataRecordClass())
{
	ui->setupUi(this);

	// Populate the combo box with available years
	populateComboBox();

}

DataRecord::~DataRecord()
{
	delete ui;
}

// "Find" button clicked then it takes the input from the combo box (year) and searches for the data in the user_database.sql file (checkin) and displays the data in the table widget
// table widget has 6 columns: name, surname, room number, checkin, checkout, email, guest number
void DataRecord::on_pushButton_clicked()
{
	// Get the selected year from the combo box
	QString year = ui->comboBox0->currentText();
	// Clear the table widget
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);

	// Open the user database file
	QFile file("user_database.sql");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	// Read the file and decode the contents
	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	file.close();

	// Split the text into lines
	QStringList fields = text.split("\n");

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeFirst();
		fields.removeLast();
	}

	// Populate the table widget with the data
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			if (yearFromCheckin == year) {
				QString name = data[0];
				QString surname = data[1];
				QString roomNumber = data[2];
				QString checkin = data[3];
				QString checkout = data[4];
				QString email = data[5];
				QString guestNumber = data[6];

				int row = ui->tableWidget->rowCount();
				ui->tableWidget->insertRow(row);
				ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
				ui->tableWidget->setItem(row, 1, new QTableWidgetItem(surname));
				ui->tableWidget->setItem(row, 2, new QTableWidgetItem(roomNumber));
				ui->tableWidget->setItem(row, 3, new QTableWidgetItem(checkin));
				ui->tableWidget->setItem(row, 4, new QTableWidgetItem(checkout));
				ui->tableWidget->setItem(row, 5, new QTableWidgetItem(email));
				ui->tableWidget->setItem(row, 6, new QTableWidgetItem(guestNumber));
			}
		}
	}
}

// go back to the main window and close the current window
void DataRecord::on_pushButton1_clicked() {
	// close the current window
	close();
	// open the main window
	MainWindow* mainwindow = new MainWindow();
	mainwindow->show();
}

// get the data from the table widget and generate a SVG bar chart pop up window without using Qt
void DataRecord::on_pushButton2_clicked() {
	// activathe generateBarChart function
	generateBarChart();

}

void DataRecord::populateComboBox()
{
	// Open the user database file
	QFile file("user_database.sql");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeFirst();
		fields.removeLast();
	}

	// Populate the combo box with available years
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString year = data[3].split(".")[2]; // Changed index from 4 to 3
			if (ui->comboBox0->findText(year) == -1) { // Changed condition
				ui->comboBox0->addItem(year);
			} 
		} 
	} 
} 

void DataRecord::generateBarChart()
{
    // Get the selected year from the combo box
    QString year = ui->comboBox0->currentText();

    // Count the number of check-ins for each month
    int checkInCount[12] = {0};

    // Open the user database file
    QFile file("user_database.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error", file.errorString());
        return;
    }

    // Read the file and decode the contents
    QByteArray fileData = file.readAll();
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QString text = codec->toUnicode(fileData);
    file.close();

    // Split the text into lines
    QStringList fields = text.split("\n");

    // Remove the first and last lines
    if (fields.size() >= 2) {
        fields.removeFirst();
        fields.removeLast();
    }

    // Count the check-ins for each month
    for (int i = 0; i < fields.size(); i++) {
        QStringList data = fields[i].split(" ");
        if (data.size() >= 6) {
            QString checkin = data[3];
            QString yearFromCheckin = checkin.split(".")[2];
            if (yearFromCheckin == year) {
                QString month = checkin.split(".")[1];
                int monthIndex = month.toInt() - 1;
                checkInCount[monthIndex]++;
            }
        }
    }

    // Determine the maximum count for scaling the chart
    int maxCount = *std::max_element(checkInCount, checkInCount + 12);

    // Create an SVG generator and set its properties
    QSvgGenerator generator;
    generator.setFileName("barchart.svg");
    generator.setSize(QSize(800, 600));
    generator.setViewBox(QRect(0, 0, 800, 600));
    generator.setTitle("Check-in Count by Month");
    generator.setDescription("Bar chart showing the number of check-ins for each month in " + year);

    // Create a painter to draw on the generator
    QPainter painter;
    painter.begin(&generator);

    // Set the font and color for the chart
    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setPen(Qt::black);

	// Draw the bars of the bar chart
// Draw the bars of the bar chart
	int barSpacing = 10;
	int startX = 50;
	int startY = 550;
	int barWidth = (800 - 2 * startX - (11 * barSpacing)) / 12; // Calculate the bar width dynamically
	int startPosX = startX; // Start position X for the first bar

	QStringList monthNames = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	for (int i = 0; i < 12; i++) {
		int barHeight = (checkInCount[i] * 250) / maxCount; // Scale the bar height
		int xPos = startPosX + (i * (barWidth + barSpacing));
		int yPos = startY - barHeight;
		QRect barRect(xPos, yPos, barWidth, barHeight);

		// Draw the bar
		painter.setBrush(Qt::blue);
		painter.drawRect(barRect);

		// Draw the month label below the bar
		QString monthLabel = monthNames.at(i);
		QRect labelRect(xPos, startY, barWidth, 30);
		painter.drawText(labelRect, Qt::AlignCenter, monthLabel);

		// Draw the check-in count on top of the bar
		QString countLabel = QString::number(checkInCount[i]);
		QRect countRect(xPos, yPos - 20, barWidth, 20);
		painter.drawText(countRect, Qt::AlignCenter, countLabel);

		// Draw the year label below the bar chart


		// Draw the y-axis label
		QRect yAxisRect(0, 0, 50, 600);
		painter.drawText(yAxisRect, Qt::AlignCenter, "Count");


		// Draw the x-axis label
		QRect xAxisRect(0, 550, 800, 50);
		painter.drawText(xAxisRect, Qt::AlignCenter, "Month");

		// Draw the title
		QRect titleRect(0, 0, 500, 50);
		painter.drawText(titleRect, Qt::AlignCenter, "Booked count");

		// Type the year
		QRect yearTRect(0, 0, 700, 50);
		painter.drawText(yearTRect, Qt::AlignCenter, "year");

		// Put year next to the title
		QRect yearRect(0, 0, 800, 50);
		painter.drawText(yearRect, Qt::AlignCenter, year);



	}


    painter.end();

    // Show a message box with the file path
    QMessageBox::information(this, "Bar Chart Generated", "The bar chart has been generated and saved as 'barchart.svg'.");
}
