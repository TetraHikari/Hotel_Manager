#pragma once

#include <QDialog>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class ReservationClass; }
QT_END_NAMESPACE

class Reservation : public QDialog
{
    Q_OBJECT

public:
    Reservation(QWidget* parent = nullptr);
    ~Reservation();

    bool isRoomAvailable(QString& roomNumber, QString& checkin, QString& checkout);


private:
    Ui::ReservationClass* ui;

    
private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();


};
