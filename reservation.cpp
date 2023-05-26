#include "reservation.h"
#include "ui_reservation.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Reservation::Reservation(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::ReservationClass())
{
	ui->setupUi(this);
	// set combobox to show the available room numbers from the roomdata.txt file
	QFile file("roomdata.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(this, "Error", "Could not open data file");
		exit(1);
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList tokens = line.split(" ");
		if (tokens.size() >= 3) {
			QString roomNumber = tokens[0];
			QString roomType = tokens[1];
			bool isAvailable = (tokens[2].toInt() == 1);
			if (isAvailable) {
				ui->comboBox1->addItem(roomNumber + " " + roomType);
			}
		}
	}
}

Reservation::~Reservation()
{
	delete ui;
}

// Check if the selected room type is available
bool Reservation::isRoomTypeAvailable(const QString& roomType)
{
	// Read room availability from the data.txt file
	QFile file("roomdata.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(this, "Error", "Could not open data file");
		exit(1);
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList tokens = line.split(" ");
		if (tokens.size() >= 3) {
			QString currentRoomType = tokens[1];
			bool isAvailable = (tokens[2].toInt() == 1);
			if (currentRoomType == roomType && !isAvailable) {
				file.close();
				return false; // Room type is not available
			}
		}
	}

	file.close();
	return true; // Room type is available
}

// Save the reservation into guest_database.txt file and close the reservation dialog and show the main window
void Reservation::on_pushButton1_clicked()
{
	QString name = ui->lineEdit1->text();
	QString surename = ui->lineEdit2->text();
	QString email = ui->lineEdit3->text();
	QString room = ui->comboBox1->currentText();
	QString checkin = ui->dateEdit1->date().toString("dd.MM.yyyy");
	QString checkout = ui->dateEdit2->date().toString("dd.MM.yyyy");
	int guest_number = ui->spinBox1->value();


	// Check if the selected room type is available
	if (!isRoomTypeAvailable(room)) {
		QMessageBox::information(this, "Room Not Available", "The selected room type is not available.");
		return;
	}

	// Insert the values into the guest_database.txt file
	QFile file("guest_database.txt");
	if (!file.open(QIODevice::Append | QIODevice::Text)) {
		QMessageBox::critical(this, "Error", "Could not open database file");
		exit(1);
	}
	QTextStream out(&file);
	out << name << " " << surename << " " << email << " " << room << " " << checkin << " " << checkout << " " << guest_number << "\n";
	file.close();



	
	


	// Close the reservation dialog and show the main window
	QMessageBox::information(this, "Reservation", "Reservation successful.");


	// Clear the form
	ui->lineEdit1->clear();
	ui->lineEdit2->clear();
	ui->lineEdit3->clear();
	ui->comboBox1->setCurrentIndex(0);
	ui->dateEdit1->setDate(QDate::currentDate());
	ui->dateEdit2->setDate(QDate::currentDate());
	ui->spinBox1->setValue(1);

	this->close();
	((MainWindow*)parentWidget())->show();
}

// Close the reservation dialog and show the main window
void Reservation::on_pushButton2_clicked()
{
	this->close();
	((MainWindow*)parentWidget())->show();
}
