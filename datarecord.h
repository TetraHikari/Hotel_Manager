#pragma once

#include <QDialog>
#include "ui_datarecord.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DataRecordClass; };
QT_END_NAMESPACE

class DataRecord : public QDialog
{
	Q_OBJECT

public:
	DataRecord(QWidget *parent = nullptr);
	~DataRecord();

	void populateComboBox();
	void generateBarChart();
	

private:
	Ui::DataRecordClass *ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton1_clicked();
	void on_pushButton2_clicked();
};
