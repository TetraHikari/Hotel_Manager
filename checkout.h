#pragma once

#include <QDialog>
#include "ui_checkout.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CheckOutClass; };
QT_END_NAMESPACE

class CheckOut : public QDialog
{
	Q_OBJECT

public:
	CheckOut(QWidget *parent = nullptr);
	~CheckOut();

	void populateComboBox();
	



	

private:
	Ui::CheckOutClass *ui;

private slots:
	void updateComboBox1(int index);
	void on_pushButton1_clicked();
	void on_pushButton2_clicked();
	void updatelineEdit_1(int index);
	void updatelineEdit_2(int index);
	void updatelineEdit_3(int index);
	void updatelineEdit_4(int index);
	void updatelineEdit_5(int index);

};
