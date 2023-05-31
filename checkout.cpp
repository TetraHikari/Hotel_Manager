#include "checkout.h"
#include "ui_checkout.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <QDate>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

CheckOut::CheckOut(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::CheckOutClass())
{
	ui->setupUi(this);
	// Populate the combo box with available years
	populateComboBox();
	//when data in comboBox is changed, the another comboBox (comboBox1)is updated
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBox1(int)));
	//after data om comboBox1 is changed, update lineEdit_1 lineEdit_2 lineEdit_3 lineEdit_4 lineEdit_5 with data based on comboBox (name) and comboBox1 (surname)
	// connect comboBox1 to lineEdit_1
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_1(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_2(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_3(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_4(int)));
	connect(ui->comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updatelineEdit_5(int)));
}

CheckOut::~CheckOut()
{
	delete ui;
}


void CheckOut::populateComboBox()
{
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				ui->comboBox->addItem(name);
			}
		}
	}
}

void CheckOut::updateComboBox1(int index)
{
	// clear comboBox1
	ui->comboBox1->clear();
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText()) {
					ui->comboBox1->addItem(surname);
				}
			}
		}
	}
}

void CheckOut::updatelineEdit_1(int index)
{
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText() && surname == ui->comboBox1->currentText()) {
					ui->lineEdit_1->setText(data[2]);
				}
			}
		}
	}
}

void CheckOut::updatelineEdit_2(int index)
{
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText() && surname == ui->comboBox1->currentText()) {
					ui->lineEdit_2->setText(data[3]);
				}
			}
		}
	}
}

void CheckOut::updatelineEdit_3(int index)
{
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText() && surname == ui->comboBox1->currentText()) {
					ui->lineEdit_3->setText(data[4]);
				}
			}
		}
	}
}

void CheckOut::updatelineEdit_4(int index)
{
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText() && surname == ui->comboBox1->currentText()) {
					ui->lineEdit_4->setText(data[5]);
				}
			}
		}
	}
}

void CheckOut::updatelineEdit_5(int index)
{
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText() && surname == ui->comboBox1->currentText()) {
					ui->lineEdit_5->setText(data[6]);
				}
			}
		}
	}
}

// store the data in the database showing the check-in information : name, surname, room number, check-in date into currentcheckout.txt
void CheckOut::on_pushButton1_clicked() {
	// Open the user database file
	QFile file("currentcheckin.txt");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
		return;
	}

	QByteArray fileData = file.readAll();
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(fileData);
	QStringList fields = text.split("\n");
	file.close();

	// Remove the first and last lines
	if (fields.size() >= 2) {
		fields.removeLast();
	}

	// current date
	QDate currentDate = QDate::currentDate();

	// data example: Peeranat Patarakittisopol 101 20.10.2020 21.10.2020 peeranat.patarakittisopol@gmailcom 1
	// Populate the combo box with the data who have already checked in from currentcheckin.txt
	for (int i = 0; i < fields.size(); i++) {
		QStringList data = fields[i].split(" ");
		if (data.size() >= 6) {
			QString checkin = data[3];
			QString yearFromCheckin = checkin.split(".")[2];
			QString monthFromCheckin = checkin.split(".")[1];
			QString dayFromCheckin = checkin.split(".")[0];
			QDate checkinDate = QDate(yearFromCheckin.toInt(), monthFromCheckin.toInt(), dayFromCheckin.toInt());
			if (checkinDate <= currentDate) {
				QString name = data[0];
				QString surname = data[1];
				if (name == ui->comboBox->currentText() && surname == ui->comboBox1->currentText()) {
					// Open the user database file
					QFile file("currentcheckout.txt");
					if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
						QMessageBox::information(0, "Error", file.errorString());
						return;
					}

					// Write the data into the database
					QTextStream out(&file);
					out << name << " " << surname << " " << data[2] << " " << data[3] << " " << data[4] << " " << data[5] << " " << data[6] << "\n";
					file.close();
				} 
			} 
		}
	}
	MainWindow* mainwindow = new MainWindow();
	mainwindow->show();
	this->close();
}


//pushButton_2 go back to mainwindow
void CheckOut::on_pushButton2_clicked()
{
	MainWindow* mainwindow = new MainWindow();
	mainwindow->show();
	this->close();
}


