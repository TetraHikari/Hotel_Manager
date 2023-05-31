#pragma once

#include <QDialog>
#include "ui_checkin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CheckInClass; };
QT_END_NAMESPACE

class CheckIn : public QDialog
{
	Q_OBJECT

public:
	CheckIn(QWidget *parent = nullptr);
	~CheckIn();

	void populateComboBox();


private:
	Ui::CheckInClass *ui;

private slots:
	void updateComboBox1(int index);
	void updatelineEdit_1(int index);
	void updatelineEdit_2(int index);
	void updatelineEdit_3(int index);
	void updatelineEdit_4(int index);
	void updatelineEdit_5(int index);
	void on_pushButton2_clicked();
	void on_pushButton1_clicked();
	
};
