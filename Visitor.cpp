#include "Visitor.h"
#include <iostream>

Visitor::Visitor()
{
	this->money = 0;
	this->pocket = nullptr;
	this->userSearch = nullptr;
	this->userSearchSize = 0;
	this->pocketSize = 0;
}

Visitor::Visitor(const Visitor& copy)
{
	this->userSearchSize = copy.userSearchSize;
	this->pocketSize = copy.pocketSize;
	this->money = copy.money;
	this->pocket = copy.pocket;
	this->userSearch = copy.userSearch;
}

double Visitor::GetBalance()
{
	return money;
}

void Visitor::ShowUserSearch()
{
	for (int i = 0; i < userSearchSize; i++)
	{
		userSearch[i].ConsoleOutput();
	}
	std::cout << std::endl;
}

void Visitor::ShowUserPocket()
{
	std::cout << std::endl;
	for (int i = 0; i < pocketSize; i++)
	{
		pocket[i].ConsoleOutput();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Visitor::TopUpBalance(double money)
{
	this->money += money;
}

Performance Visitor::FindPerformance(TicketWindow data, std::string name)
{
	Performance result;
	for (int i = 0; i < data.getSizeAll(); i++)
	{
		if (data.FindPerformance(name, i))
		{
			result = data[i].GetPerformance();
			if (userSearchSize == 0)
			{
				this->userSearchSize++;
				this->userSearch = new Performance[userSearchSize];
				this->userSearch[0] = result;
			}
			else
			{
				Performance* copy = new Performance[userSearchSize];
				for (int i = 0; i < userSearchSize; i++)
				{
					copy[i] = userSearch[i];
				}
				this->userSearchSize++;
				this->userSearch = new Performance[userSearchSize];
				for (int i = 0; i < userSearchSize - 1; i++)
				{
					this->userSearch[i] = copy[i];
				}
				this->userSearch[i] = data[i].GetPerformance();
				delete[] copy;
			}
		}
	}
	return result;
}

Tickets Visitor::BuyTicket(TicketWindow data, std::string name, int place, int row)
{

	Tickets result;
	for (int i = 0; i < data.getSizeAll(); i++)
	{
		if (data.FindPerformance(name, i))
		{
			if (money > data.getMoney(name))
			{
				if (pocketSize == 0)
				{
					result = data[i].GetTicket();
					this->pocketSize++;
					this->pocket = new Tickets[1];
					this->pocket[0] = data.BuyTicket(name, place, row);
					pocket[0].ChangePlaceAndRow(place, row);
					this->money -= data.getMoney(name);
				}
				else
				{
					Tickets* copy = new Tickets[pocketSize];
					for (int i = 0; i < pocketSize; i++)
					{
						copy[i] = pocket[i];
					}
					this->pocket = new Tickets[pocketSize+1];
					for (int i = 0; i < pocketSize; i++)
					{
						this->pocket[i] = copy[i];
					}
					pocket[pocketSize] = data.BuyTicket(name, place, row);
					pocket[pocketSize].ChangePlaceAndRow(place, row);
					this->pocketSize++;
					delete[] copy;
					this->money - data.getMoney(name);
				}
			}
			else
			{

				std::cout << " You don't have enough money  :( " << std::endl;
			}
		}
	}
	return result;
}
Tickets Visitor::BuyReservedTicket(TicketWindow data, std::string name, int place, int row)
{

	Tickets result;
	for (int i = 0; i < data.getSizeAll(); i++)
	{
		if (data.FindReservedPerformance(name, i))
		{
			if (money > data.getMoney(name))
			{
				if (pocketSize == 0)
				{
					result = data[i].GetTicket();
					this->pocketSize++;
					this->pocket = new Tickets[1];
					this->pocket[0] = data.BuyTicket(name, place, row);
					pocket[0].ChangePlaceAndRow(place, row);
					this->money -= data.getMoney(name);
				}
				else
				{
					Tickets* copy = new Tickets[pocketSize];
					for (int i = 0; i < pocketSize; i++)
					{
						copy[i] = pocket[i];
					}
					this->pocket = new Tickets[pocketSize + 1];
					for (int i = 0; i < pocketSize; i++)
					{
						this->pocket[i] = copy[i];
					}
					pocket[pocketSize] = data.BuyReservedTicket(name, place, row);
					pocket[pocketSize].ChangePlaceAndRow(place, row);
					this->pocketSize++;
					delete[] copy;
					this->money - data.getMoney(name);
				}
			}
			else
			{

				std::cout << " You don't have enough money  :( " << std::endl;
			}
		}
	}
	return result;
}
void Visitor::ReservTicket(TicketWindow data, std::string name, int place, int row)
{
	data.ReservTicket(name, place, row);
}

Visitor::~Visitor()
{
	if (pocket == nullptr && userSearch == nullptr)
	{
		delete[] pocket;
		delete[] userSearch;
	}
}
