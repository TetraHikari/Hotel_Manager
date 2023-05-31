#include "reservation.h"
#include "ui_reservation.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <QtSql>
#include <QTextCodec>

#include <iostream>


Reservation::Reservation(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::ReservationClass)
{
	ui->setupUi(this);
	// Set the date to the current date
	ui->dateEdit1->setDate(QDate::currentDate());
	ui->dateEdit2->setDate(QDate::currentDate());
	// Append the room numbers and types to the combo box
	QFile file("room_database.sql");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}
	QTextStream in(&file);
	QStringList fields;
	while (!in.atEnd()) {
		QString line = in.readLine();
		fields = line.split(" ");
		if (fields.size() >= 2) {
			ui->comboBox1->addItem(fields[0] + " " + fields[1]);
		}
	}
	file.close();
	// Set the date format
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
}

Reservation::~Reservation()
{
	delete ui;
}

// Check if the room is available for the given check-in and check-out dates
// data example: Peeranat Patarakittisopol 101 01.01.20 01.02.20 peeranatpee1@gmailcom
bool Reservation::isRoomAvailable(QString& roomNumber, QString& checkin, QString& checkout)
{
	QDate checkinDate = QDate::fromString(checkin, "dd.MM.yyyy");
	QDate checkoutDate = QDate::fromString(checkout, "dd.MM.yyyy");

	QFile file("user_database.sql");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(nullptr, "Error", "Could not open data file");
		return false;
	}

	if (checkinDate > checkoutDate) {
		QMessageBox::critical(nullptr, "Error", "Check-in date must be before check-out date");
		return false;
	}

	if (checkinDate == checkoutDate) {
		QMessageBox::critical(nullptr, "Error", "Check-in date must be before check-out date");
		return false;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString reservationData = codec->toUnicode(fileData);

	QStringList lines = reservationData.split("\n");
	lines.removeFirst();

	for (const QString& line : lines) {
		QStringList fields = line.split(" ");
		if (fields.size() >= 7) {
			QString room = fields[2];
			QString checkin = fields[3];
			QString checkout = fields[4];
			QDate checkinDateDB = QDate::fromString(checkin, "dd.MM.yyyy");
			QDate checkoutDateDB = QDate::fromString(checkout, "dd.MM.yyyy");
			if (room == roomNumber) {
				if (checkinDate <= checkoutDateDB && checkoutDate >= checkinDateDB) {
					return false;
				}
				
			}

		}
	}
	return true;
}



// Save the reservation into user_database.sql file, close the reservation dialog, and show the main window : // data examplle : Peeranat Patarakittisopol 101 01.01.2020 03.01.2020 peeranatpee1@gmailcom
void Reservation::on_pushButton1_clicked()
{
	// Get the roomNumber, checkin, and checkout from the user interface
	QString roomNumber = ui->comboBox1->currentText().split(" ")[0]; // example data : 
	QString checkin = ui->dateEdit1->date().toString("dd.MM.yyyy");
	QString checkout = ui->dateEdit2->date().toString("dd.MM.yyyy");
	QString name = ui->lineEdit1->text();
	QString surname = ui->lineEdit2->text();
	QString email = ui->lineEdit3->text();
	QString guest = ui->spinBox1->text();

	// Show a message if the room is available or not
	if (isRoomAvailable(roomNumber, checkin, checkout)) {
		QMessageBox::information(this, "Success", "Room is available");
	}
	else {
		QMessageBox::critical(this, "Error", "Room is not available");
		return;
	}

	// Save the reservation into user_database.sql file
	QFile file("user_database.sql");
	if (!file.open(QIODevice::Append | QIODevice::Text)) {
		QMessageBox::critical(this, "Error", "Could not open file");
		return;
	}
	QTextStream out(&file);
	out << name << " " << surname << " " << roomNumber << " " << checkin << " " << checkout << " " << email << " " << guest << "\n";
	file.close();

	// Close the reservation dialog and show the main window
	MainWindow* mainWindow = new MainWindow();
	mainWindow->show();
	this->close();
}


// button to return to the main window and close the reservation dialog as well as clear the data in the reservation dialog
void Reservation::on_pushButton2_clicked()
{
	// Close the reservation dialog and show the main window
	MainWindow* mainWindow = new MainWindow();
	mainWindow->show();
	this->close();
}

void Reservation::on_pushButton3_clicked()
{
	// Read the reservation data from user_database.sql file (skip reading the first line)
	QFile file("user_database.sql");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::critical(this, "Error", "Could not open data file");
		return;
	}
	QByteArray fileData = file.readAll();

	// Convert from UTF-8 to Unicode
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString reservationData = codec->toUnicode(fileData);

	//cutting the first line
	reservationData = reservationData.mid(reservationData.indexOf("\n") + 1);

	file.close();

	// Show the reservation data
	QMessageBox::information(this, "Reservation Data", reservationData);
}