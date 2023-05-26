#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reservation.h"
#include "ui_reservation.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);

    reservation = new Reservation(this);
	roomavailable = new Roomavailable(this);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete reservation;
	delete roomavailable;
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
	// close the main window and exit the application
	this->close();
}

void MainWindow::on_pushButton4_clicked()
{
	// close the main window and exit the application
	this->close();
}

void MainWindow::on_pushButton5_clicked()
{
	// close the main window and exit the application
	this->close();
}

void MainWindow::on_pushButton6_clicked()
{
	// close the main window and exit the application
	this->close();
}
