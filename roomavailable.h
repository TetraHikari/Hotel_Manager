#pragma once

#include <QDialog>
#include "ui_roomavailable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RoomavailableClass; };
QT_END_NAMESPACE

class Roomavailable : public QDialog
{
	Q_OBJECT

public:
	Roomavailable(QWidget *parent = nullptr);
	~Roomavailable();
	void readData();

private:
	Ui::RoomavailableClass *ui;

private slots:
	void on_pushButton0_clicked();
};
