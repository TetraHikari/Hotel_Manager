#include "roomavailable.h"
#include "ui_roomavailable.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <QVector>
#include <QTextCodec>
#include <QDate>


Roomavailable::Roomavailable(QWidget* parent)
	: QDialog(parent), ui(new Ui::RoomavailableClass())
{
	ui->setupUi(this);
	connect(ui->pushButton1, &QPushButton::clicked, this, &Roomavailable::on_pushButton1_clicked); // Connect the button signal to the slot
	// Set the date to today
	QDate today = QDate::currentDate();
	ui->dateEdit1->setDate(today);
	ui->dateEdit2->setDate(today);
}

Roomavailable::~Roomavailable()
{
    delete ui;
}

// Close the window and go back to the main window
void Roomavailable::on_pushButton0_clicked()
{
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

// Check if the room is available for todays date anreturn true if it is available  (read from user_database.sql)
bool Roomavailable::isRoomAvailable(QString& roomNumber, QString& checkin, QString& checkout)
{
    //QMessageBox::information(this, "Room number: " + roomNumber + ", Check-in: " + checkin + ", Check-out: " + checkout, "Room number: " + roomNumber + ", Check-in: " + checkin + ", Check-out: " + checkout);


    QDate checkinDate = QDate::fromString(checkin, "dd.MM.yyyy");
    QDate checkoutDate = QDate::fromString(checkout, "dd.MM.yyyy");

    if (checkinDate > checkoutDate) {
        return false; // Invalid date
    }
    
    if (checkinDate < QDate::currentDate()) {
		return false; // Invalid date
	}

    if (checkoutDate < QDate::currentDate()) {
        return false; // Invalid date
    }

    if (checkinDate == checkoutDate) {
		return false; // Invalid date
	}

    QFile file("user_database.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not open data file");
        return false;
    }

    QByteArray fileData = file.readAll();
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QString reservationData = codec->toUnicode(fileData);

    QStringList lines = reservationData.split("\n");
    lines.removeFirst();
    lines.removeLast();

    for (const QString& line : lines) {
        QStringList fields = line.split(" ");

        if (fields.size() >= 5) {
            QString lineRoomNumber = fields[2];
            QDate lineCheckinDate = QDate::fromString(fields[3], "dd.MM.yyyy");
            QDate lineCheckoutDate = QDate::fromString(fields[4], "dd.MM.yyyy");

            if (roomNumber == lineRoomNumber &&
                (checkinDate < lineCheckoutDate && checkoutDate > lineCheckinDate)) {
                return false; // Room is not available
            }
        }
    }

    return true; // Room is available
}




// new readData()

// Check button for taking the user input (checkin and checkout dates) in QDate box and check if the room is available for the given dates as well as change the color of the label accordingly
void Roomavailable::on_pushButton1_clicked()
{
    QStringList roomLabels = { "label101", "label102", "label103", "label104", "label201", "label202",
                              "label203", "label204", "label301", "label302", "label303", "label304" };

    QString checkin = ui->dateEdit1->date().toString("dd.MM.yyyy");
    QString checkout = ui->dateEdit2->date().toString("dd.MM.yyyy");

    for (int i = 0; i < roomLabels.size(); i++) {
        QString roomNumber = roomLabels[i].right(3);
        bool isAvailable = isRoomAvailable(roomNumber, checkin, checkout);
        if (isAvailable) {
            QLabel* label = this->findChild<QLabel*>(roomLabels[i]);
            label->setStyleSheet("QLabel { background-color : lightgreen; }");
        }
        else {
            QLabel* label = this->findChild<QLabel*>(roomLabels[i]);
            label->setStyleSheet("QLabel { background-color : red; }");
        }
    }
}





    