#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <QVector>


class Room {
public:
    int roomNumber;
    QString roomType;
    bool isAvailable;

    Room(int number, const QString& type) : roomNumber(number), roomType(type), isAvailable(true) {}

    QString toString() const {
        return QString("%1 %2 %3").arg(roomNumber).arg(roomType).arg(isAvailable);
    }
};

QVector<Room> initializeRooms() {
    QVector<Room> rooms;

    Room room1(101, "Deluxe");
    Room room2(102, "Deluxe");
    Room room3(103, "Deluxe");
    Room room4(104, "Deluxe");
    Room room5(201, "Luxury");
    Room room6(202, "Luxury");
    Room room7(203, "Luxury");
    Room room8(204, "Grande");
    Room room9(301, "Grande");
    Room room10(302, "Grande");
    Room room11(303, "Grande");
    Room room12(304, "Grande");

    room1.isAvailable = true;
    room2.isAvailable = true;
    room3.isAvailable = true;
    room4.isAvailable = true;
    room5.isAvailable = true;
    room6.isAvailable = true;
    room7.isAvailable = true;
    room8.isAvailable = true;
    room9.isAvailable = true;
    room10.isAvailable = true;
    room11.isAvailable = true;
    room12.isAvailable = true;

    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);
    rooms.push_back(room4);
    rooms.push_back(room5);
    rooms.push_back(room6);
    rooms.push_back(room7);
    rooms.push_back(room8);
    rooms.push_back(room9);
    rooms.push_back(room10);
    rooms.push_back(room11);
    rooms.push_back(room12);

    QFile file("roomdata.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Room& room : rooms) {
            out << room.toString() << "\n";
        }
        file.close();
    }

    return rooms;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QVector<Room> rooms = initializeRooms();

    MainWindow w;
    w.show();
    return a.exec();
}
