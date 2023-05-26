#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "reservation.h"
#include "ui_reservation.h"
#include "roomavailable.h"
#include "ui_roomavailable.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Reservation *reservation;
    Roomavailable *roomavailable;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;

private slots:
    void on_pushButton1_clicked(); // room availables
    void on_pushButton2_clicked(); // reservation
    void on_pushButton3_clicked(); // check in
    void on_pushButton4_clicked(); // expenses
    void on_pushButton5_clicked(); // food orders
    void on_pushButton6_clicked(); // check out
};
