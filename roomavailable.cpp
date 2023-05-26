#include "roomavailable.h"
#include "ui_roomavailable.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Roomavailable::Roomavailable(QWidget* parent)
    : QDialog(parent), ui(new Ui::RoomavailableClass())
{
    ui->setupUi(this);
    readData(); // Call the readData function when the dialog is constructed
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

// Read the data from the roomdata.txt file and update the label background colors accordingly
void Roomavailable::readData()
{
    const QStringList roomLabels = { "label101", "label102", "label103", "label104", "label201", "label202",
                                      "label203", "label204", "label301", "label302", "label303", "label304" };

    std::vector<int> roomsAvailable;

    // Read the data from the file
    QFile file("roomdata.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(" ");
        if (data.size() == 3) {
            roomsAvailable.push_back(data[2].toInt());
        }
    }

    file.close();

    // Update the label background colors
    for (int i = 0; i < roomLabels.size(); i++) {
        QLabel* label = Roomavailable::findChild<QLabel*>(roomLabels[i]);
        if (!label) {
            continue;
        }

        if (roomsAvailable[i] == 0) {
            label->setStyleSheet("background-color: red;");
        }
        else {
            label->setStyleSheet("background-color: green;");
        }
    }
}
