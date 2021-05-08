#include "TicketWindowStructure.h"
#include "Performance.h"
#include "Tickets.h"
#include <iostream>
#include <iomanip>

TicketWindowStructure::TicketWindowStructure(Performance per, Tickets tick)
{
	Performance temp0(per);
	this->_p = temp0;
	Tickets temp1(tick, _p);
	this->_t = temp1;
	int hallSize = tick.GetHallSize();
	this->ticketSize = hallSize* hallSize;
	this->_hallSize = hallSize;
	hall = new std::string * [_hallSize];
	for (int i = 0; i < _hallSize; i++)
	{
		hall[i] = new std::string[_hallSize];
		for (int j = 0; j < _hallSize; j++)
		{
			this->hall[i][j] = "Avaible";
		}
	}
}

Tickets TicketWindowStructure::GetTicket()
{
	Tickets temp(this->_t);
	return temp;
}

int TicketWindowStructure::GetTicketSize()
{
	return this->ticketSize;
}

Performance TicketWindowStructure::GetPerformance()
{
	Performance temp(this->_p);
	return temp;
}

void TicketWindowStructure::ChangeTicketSize(int num)
{
	this->ticketSize = num;
}

TicketWindowStructure::TicketWindowStructure()
{
	this->_hallSize = 0;
	this->ticketSize = 0;
	this->hall = nullptr;
}

void TicketWindowStructure::operator=(TicketWindowStructure right)
{
	this->_p = right._p;
	this->_t = right._t;
	this->ticketSize = right.ticketSize;
	this->_hallSize = right._hallSize;
	this->hall = right.hall;
}

TicketWindowStructure::TicketWindowStructure(int size)
{
	this->ticketSize = size;
	hall = new std::string * [ticketSize];
	for (int i = 0; i < ticketSize; i++)
	{
		hall[i] = new std::string[ticketSize];
		for (int j = 0; j < ticketSize; j++)
		{
			hall[i][j] = " ";
		}
	}
}

TicketWindowStructure::TicketWindowStructure(TicketWindowStructure& copy)
{
	this->_p = copy._p;
	this->_t = copy._t;
	this->ticketSize = copy.ticketSize;
	this->_hallSize = copy._hallSize;
	this->hall = copy.hall;
}



void TicketWindowStructure::ConsoleOutput()
{
	_t.ConsoleOutput();
	std::cout << "Hall : " << std::endl;
	std::cout << "            ";
	for (int i = 0; i < _hallSize; i++)
	{
		std::cout << i;
		std::cout << std::setw(13+1);
	}
	std::cout << std::endl;
	for (int i = 0; i < _hallSize; i++)
	{ 
		std::cout << std::setw(0);
		std::cout << i;
		std::cout << "     ";
		for (int j = 0; j < _hallSize; j++)
		{
		    std::cout << std::setw(10);
			std::cout  << hall[i][j] << "    ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


TicketWindowStructure::~TicketWindowStructure()
{
	if (hall == nullptr)
	{
		for (int i = 0; i < _hallSize; i++)
		{
			delete[] hall[i];
		}
		delete[] hall;
	}
}
