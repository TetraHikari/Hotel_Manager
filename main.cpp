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

// check database user_database.sql currentcheckin.txt to skip 1 line on the first line
// check database user_database.sql currentcheckout.txt to skip 1 line on the first line

void readDatabase(std::vector<std::string>& database)
{
	std::ifstream file("user_database.sql");
	std::string str;
	while (std::getline(file, str))
	{
		database.push_back(str);
	}

	// check if there if information in the database
	if (database.size() == 0)
	{
		// if there is no information in the database, add a line to the database
		std::ofstream file("user_database.sql");
		file << "0" << std::endl;
		file.close();

	}
}

void readCurrentCheckin(std::vector<std::string>& database)
{
	std::ifstream file("currentcheckin.txt");
	std::string str;
	while (std::getline(file, str))
	{
		database.push_back(str);
	}

	// check if there if information in the database
	if (database.size() == 0)
	{
		// if there is no information in the database, add a line to the database
		std::ofstream file("currentcheckin.txt");
		file << "0" << std::endl;
		file.close();

	}
}



int main(int argc, char* argv[])
{
	std::vector<std::string> database;
	readDatabase(database);


	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

