#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reservation.h"
#include "ui_reservation.h"



// include message box
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindowClass())
{
	ui->setupUi(this);

	reservation = new Reservation(this);
	roomavailable = new Roomavailable(this);
	datarecord = new DataRecord(this);
	checkin = new CheckIn(this);
	checkout = new CheckOut(this);

	// append data to tableWidget1 : it has 5 columns : name, surname, room number, checkin date
	// open currentcheckin.txt file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList fields = line.split(" ");

		ui->tableWidget1->insertRow(ui->tableWidget1->rowCount());
		for (int i = 0; i < fields.size(); i++) {
			ui->tableWidget1->setItem(ui->tableWidget1->rowCount() - 1, i, new QTableWidgetItem(fields.at(i)));
		}
	}

	file.close();

	// append data to tableWidget2 : it has 5 columns : name, surname, room number, checkin date
	// open currentcheckout.txt file
	QFile file2("currentcheckout.txt");
	if (!file2.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file2.errorString());
		return;
	}

	QTextStream in2(&file2);
	while (!in2.atEnd()) {
		QString line = in2.readLine();
		QStringList fields = line.split(" ");

		ui->tableWidget2->insertRow(ui->tableWidget2->rowCount());
		for (int i = 0; i < fields.size(); i++) {
			ui->tableWidget2->setItem(ui->tableWidget2->rowCount() - 1, i, new QTableWidgetItem(fields.at(i)));
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
	delete reservation;
	delete roomavailable;
	delete datarecord;
	delete checkin;
}

void MainWindow::on_pushButton1_clicked()
{
	roomavailable->show();
	this->hide();
}

// show the reservation dialog and hide the main window
void MainWindow::on_pushButton2_clicked()
{
    reservation->show();
	this->hide();
}

void MainWindow::on_pushButton3_clicked()
{
	checkin->show();
	this->hide();
}
// Data record button
void MainWindow::on_pushButton4_clicked()
{
	datarecord->show();
	this->hide();
}

void MainWindow::on_pushButtonExit_clicked()
{
	QApplication::quit();
}

void MainWindow::on_pushButton6_clicked()
{
	checkout->show();
	this->hide();
}
