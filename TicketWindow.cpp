#include "TicketWindow.h"
#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include "Performance.h"
#include "Tickets.h"
#include "TicketWindowStructure.h"
#include <iostream>

using json = nlohmann::json;


TicketWindow::TicketWindow()
{
	this->_size = 0;
	this->_till = nullptr;
	this->_sizeForSold = 0;
	this->_sold = nullptr;
	this->_sizeForReserved = 0;
	this->_reserved = nullptr;
}

TicketWindow::TicketWindow(const TicketWindow& copy)
{
	this->_size = copy._size;
	this->_till = copy._till;
	this->_sizeForSold = copy._sizeForSold;
	this->_sold = copy._sold;
	this->_sizeForReserved = copy._sizeForReserved;
	this->_reserved = copy._reserved;
}


TicketWindow::TicketWindow(std::string fileNamePerformance, std::string fileNameTickets)
{
	std::ifstream i(fileNamePerformance);
	json j;
	i >> j;
	std::ifstream n(fileNameTickets);
	json k;
	n >> k;
	this->_size = j["Poster"].size();
	_till = new TicketWindowStructure[_size];
	for (int i = 0; i < _size; i++)
	{
		Performance temp0((j["Poster"][i]["autor"]).get<std::string>(),
			j["Poster"][i]["name"].get<std::string>(),
			j["Poster"][i]["genre"].get<std::string>(),
			j["Poster"][i]["date"].get<std::string>());
		Tickets temp1((k["Ticket"][i]["time"]).get<std::string>(),
			k["Ticket"][i]["price"].get<int>(),
			k["Ticket"][i]["hallSize"].get<int>(), temp0);
		TicketWindowStructure _till(temp0, temp1);
		_sizeForReserved = 0;
		_sizeForSold = 0;
		this->_till[i] = _till;
	}
}

bool TicketWindow::FindPerformance(std::string value, int i)
{
	bool result = false;
	if (value == _till[i].GetTicket().getPerformance() || value == _till[i].GetTicket().getAutor() || value == _till[i].GetTicket().getDate())
	{
		result = true;
	}
	return result;
}

bool TicketWindow::FindReservedPerformance(std::string value, int i)
{
	bool result = false;
	if (value == _reserved[i].GetTicket().getPerformance() || value == _reserved[i].GetTicket().getAutor() || value == _reserved[i].GetTicket().getDate())
	{
		result = true;
	}
	return result;
}

int TicketWindow::getSizeForSold()
{
	return _sizeForSold;
}

int TicketWindow::getSizeReserved()
{
	return _sizeForReserved;
}

int TicketWindow::getSizeAll()
{
	return _size;
}

int TicketWindow::getMoney(std::string name)
{
	for (int i = 0; i < _size; i++)
	{
		if (FindPerformance(name, i))
		{
			return _till[i].GetTicket().getMoney();
		}
	}
	return 0;
}

TicketWindowStructure* TicketWindow::GetBuy()
{
	TicketWindowStructure* result(_sold);
	return result;
}

TicketWindowStructure* TicketWindow::GetReserved()
{
	TicketWindowStructure* result(_reserved);
	return result;
}

void TicketWindow::ReservTicket(std::string value, int place, int row)
{

	int counter = 0;
	for (int i = 0; i < _size; i++)
	{
		if (FindPerformance(value, i))
		{
			counter++;
		}
	}
	if (counter > 1)
	{
		std::cout << "Input more details" << std::endl;
		std::string temp;
		std::cin >> temp;
		ReservTicket(temp, place, row);
	}
	else
	{
		for (int i = 0; i < _size; i++)
		{
			if (FindPerformance(value, i))
			{
				if (_till[i].GetTicketSize() <= 0)
				{
					std::cout << " Sorry, but all tickets have been sold " << std::endl;
				}
				else
				{
					if (_till[i].hall[place][row] == "Sold" || _till[i].hall[place][row] == "Reserved")
					{
						std::cout << "This place already busy" << std::endl;
					}
					else
					{
						_till[i].ChangeTicketSize(_till[i].GetTicketSize() - 1); //=-1
						_till[i].hall[place][row] = "Reserved";
						if (_sizeForReserved > 0)
						{
							AddLine(_till[i], _reserved, _sizeForReserved);
						}
						else
						{
							this->_sizeForReserved++;
							TicketWindowStructure* _reserved = new TicketWindowStructure[0];
							_reserved[0] = _till[i];
							_till[0].GetTicket();
						}
					}
				}
			}
		}
	}
}


Tickets TicketWindow::BuyTicket(std::string value, int place, int row)
{
	int resultPosition = 0;
	int counter = 0;
	for (int i = 0; i < _size; i++)
	{
		if (FindPerformance(value, i))
		{
			counter++;
		}
	}
	if (counter > 1)
	{
		std::cout << "Input more details" << std::endl;
		std::string temp;
		std::cin >> temp;
		BuyTicket(temp, place, row);
	}
	else
	{
		for (int i = 0; i < _size; i++)
		{
			if (FindPerformance(value, i))
			{
				if (_till[i].GetTicketSize() <= 0)
				{
					std::cout << " Sorry, but all tickets have been sold " << std::endl;
				}
				else
				{
					if (_till[i].hall[place][row] == "Sold" || _till[i].hall[place][row] == "Reserved")
					{
						std::cout << "This place already busy" << std::endl;
					}
					else
					{
						_till[i].ChangeTicketSize(_till[i].GetTicketSize() - 1); // -= 1;
						_till[i].hall[place][row] = "Sold";
						if (_sizeForSold > 0)
						{
							AddLine(_till[i], _sold, _sizeForSold);
							resultPosition = i;
						}
						else
						{
							this->_sizeForSold++;
							TicketWindowStructure* _sold = new TicketWindowStructure[_sizeForSold];
							_sold[0] = _till[i];
							resultPosition = i;
						}
					}
				}
			}
		}
	}
	return _till[resultPosition].GetTicket();
}

Tickets TicketWindow::BuyReservedTicket(std::string value, int place, int row)
{
	int resultPosition = 0;
	int counter = 0;
	for (int i = 0; i < _sizeForReserved; i++)
	{
		if (FindReservedPerformance(value, i))
		{
			counter++;
		}
	}
	if (counter > 1)
	{
		std::cout << "Input more details" << std::endl;
		std::string temp;
		std::cin >> temp;
		BuyReservedTicket(temp, place, row);
	}
	else
	{
		for (int i = 0; i < _sizeForReserved; i++)
		{
			if (FindReservedPerformance(value, i))
			{
				if (_reserved[i].GetTicketSize() <= 0)
				{
					std::cout << " Sorry, but all tickets have been sold " << std::endl;
				}
				else
					_reserved[i].ChangeTicketSize(_reserved[i].GetTicketSize() - 1); // -= 1;
				_till[i].hall[place][row] = "Sold";
				if (_sizeForSold > 0)
				{
					AddLine(_reserved[i], _sold, _sizeForSold);
					resultPosition = i;
				}
				else
				{
					this->_sizeForSold++;
					TicketWindowStructure* _sold = new TicketWindowStructure[_sizeForSold];
					_sold[0] = _till[i];
					resultPosition = i;
				}
			}
		}
	}
	return _reserved[resultPosition].GetTicket();
}

void TicketWindow::AddLine(TicketWindowStructure till, TicketWindowStructure* nameSpace, int someSize)
{
	TicketWindowStructure* temp = new TicketWindowStructure[someSize];
	for (int i = 0; i < someSize; i++)
	{
		temp[i] = nameSpace[i];
	}
	someSize++;
	nameSpace = new TicketWindowStructure[someSize];
	for (int i = 0; i < someSize; i++)
	{
		nameSpace[i] = temp[i];
	}
	nameSpace[someSize] = till;
}


TicketWindowStructure TicketWindow::operator[](int index)
{
	return _till[index];
}


void TicketWindow::ConsoleOutput()
{
	for (int i = 0; i < _size; i++)
	{
		_till[i].ConsoleOutput();
	}
	std::cout << std::endl;
}

TicketWindow::~TicketWindow()
{
	if (_till == nullptr)
	{
		delete[] _till;
	}
}
