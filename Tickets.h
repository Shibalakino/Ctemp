#pragma once
#include "Performance.h"
#include <string>

class Tickets : private Performance
{
public:
	Tickets();
	Tickets(Tickets& copy, Performance& daddy);
	std::string getPerformance();
	std::string getAutor();
	Tickets(const Tickets& copy);
	void ChangePlaceAndRow(int place, int row);
	std::string getDate();
	int getMoney();
	int GetHallSize();
	Tickets(std::string time, double price,int hallSize, Performance& daddy);
	void ConsoleOutput();

private:
	std::string _time;
	int _place;
	int _row;
	double _price;
	int _hallSize;
};

