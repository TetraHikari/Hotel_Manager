#include "checkin.h"
#include "ui_checkin.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include <QDate>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


CheckIn::CheckIn(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::CheckInClass())
{
	ui->setupUi(this);
	// Populate the combo box with available years
	populateComboBox();
	//when data in comboBox is changed, the another comboBox (comboBox1)is updated
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBox1(int)));
	//after data om comboBox1 is changed, update lineEdit_1 lineEdit_2 lineEdit_3 lineEdit_4 lineEdit_5 with data based on comboBox (name) and comboBox1 (surname)
	// connect comboBox1 to lineEdit_1
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_1(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_2(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_3(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_4(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_5(int)));
}

CheckIn::~CheckIn()
{
	delete ui;
	

}

void CheckIn::populateComboBox()
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	//Populate the combo box with names of people who have checked in today
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		if (checkinDate == currentDate.toString("dd.MM.yyyy")) {
			ui->comboBox->addItem(data.at(0));
		}
	}
}


void CheckIn::updateComboBox1(int index)
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with surnames of people who have the name inputted in the first comboBox (comboBox) and have checked in today
	ui->comboBox1->clear();
	// Get the name from the first comboBox
	QString name = ui->comboBox->itemText(index).trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the surname to the second comboBox
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name) { // Trim leading and trailing whitespaces
			ui->comboBox1->addItem(data.at(1));
		}
	}
}


// Update lineEdit_1 based on the comboBox (name) and comboBox1 (surname)
void CheckIn::updatelineEdit_1(int index)
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Get the name from the first comboBox
	QString name = ui->comboBox->itemText(ui->comboBox->currentIndex()).trimmed(); // Trim leading and trailing whitespaces
	// Get the surname from the second comboBox
	QString surname = ui->comboBox1->itemText(index).trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the surname to the second comboBox
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name && data.at(1).trimmed() == surname) { // Trim leading and trailing whitespaces
					ui->lineEdit_1->setText(data.at(2));
				}
	}
}

// Update lineEdit_2 based on the comboBox (name) and comboBox1 (surname)
void CheckIn::updatelineEdit_2(int index)
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Get the name from the first comboBox
	QString name = ui->comboBox->itemText(ui->comboBox->currentIndex()).trimmed(); // Trim leading and trailing whitespaces
	// Get the surname from the second comboBox
	QString surname = ui->comboBox1->itemText(index).trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the surname to the second comboBox
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name && data.at(1).trimmed() == surname) { // Trim leading and trailing whitespaces
					ui->lineEdit_2->setText(data.at(3));
				}
	}
}

// Update lineEdit_3 based on the comboBox (name) and comboBox1 (surname)
void CheckIn::updatelineEdit_3(int index)
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Get the name from the first comboBox
	QString name = ui->comboBox->itemText(ui->comboBox->currentIndex()).trimmed(); // Trim leading and trailing whitespaces
	// Get the surname from the second comboBox
	QString surname = ui->comboBox1->itemText(index).trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the surname to the second comboBox
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name && data.at(1).trimmed() == surname) { // Trim leading and trailing whitespaces
							ui->lineEdit_3->setText(data.at(4));
						}
	}
}

// Update lineEdit_4 based on the comboBox (name) and comboBox1 (surname)
void CheckIn::updatelineEdit_4(int index)
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Get the name from the first comboBox
	QString name = ui->comboBox->itemText(ui->comboBox->currentIndex()).trimmed(); // Trim leading and trailing whitespaces
	// Get the surname from the second comboBox
	QString surname = ui->comboBox1->itemText(index).trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the surname to the second comboBox
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name && data.at(1).trimmed() == surname) { // Trim leading and trailing whitespaces
									ui->lineEdit_4->setText(data.at(5));
								}
	}
}

// Update lineEdit_5 based on the comboBox (name) and comboBox1 (surname)
void CheckIn::updatelineEdit_5(int index)
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

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Get the name from the first comboBox
	QString name = ui->comboBox->itemText(ui->comboBox->currentIndex()).trimmed(); // Trim leading and trailing whitespaces
	// Get the surname from the second comboBox
	QString surname = ui->comboBox1->itemText(index).trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the surname to the second comboBox
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name && data.at(1).trimmed() == surname) { // Trim leading and trailing whitespaces
													ui->lineEdit_5->setText(data.at(6));
												}
	}
}

// return back to the main window when the button is clicked
void CheckIn::on_pushButton2_clicked() {
	// Open the main window
	MainWindow* mainwindow = new MainWindow();
	mainwindow->show();
	// Close the current window
	this->close();
}

// store the data in the database showing the check-in information : name, surname, room number, check-in date into currentcheckin.txt
void CheckIn::on_pushButton1_clicked() {
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

	// current date
	QDate currentDate = QDate::currentDate();

	// Collect matching check-in entries
	QList<QStringList> matchingEntries;

	// Get the name from the first comboBox
	QString name = ui->comboBox->currentText().trimmed(); // Trim leading and trailing whitespaces
	// Get the surname from the second comboBox
	QString surname = ui->comboBox1->currentText().trimmed(); // Trim leading and trailing whitespaces

	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields.at(i).split(" ");
		QString checkinDate = data.at(3);
		QString checkoutDate = data.at(4);
		// If the name is the same as the name in the database and the check-in date is today, add the entry to the matching list
		if (checkinDate == currentDate.toString("dd.MM.yyyy") && data.at(0).trimmed() == name && data.at(1).trimmed() == surname) { // Trim leading and trailing whitespaces
			matchingEntries.append(data);
		}
	}

	// add  the check-in information to the currentcheckin.txt also not remove the previous data
	QFile outFile("currentcheckin.txt");
	if (!outFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QMessageBox::information(0, "Error", outFile.errorString());
		return;
	}

	QTextStream out(&outFile);
	for (int i = 0; i < matchingEntries.size(); i++) {
		QStringList data = matchingEntries.at(i);
		out << data.at(0) << " " << data.at(1) << " " << data.at(2) << " " << data.at(3) << " " << data.at(4) << " " << data.at(5) << " " << data.at(6) << "\n";
	}

	outFile.close();

	MainWindow* mainwindow = new MainWindow();
	mainwindow->show();
	this->close();
}




