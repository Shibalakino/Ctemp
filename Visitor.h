#pragma once
#include <string>
#include "Tickets.h"
#include "Performance.h";
#include "TicketWindow.h"

class Visitor
{
public:
	Visitor();
	Visitor(const Visitor &copy);
	double GetBalance();
	void ShowUserSearch();
	void ShowUserPocket();
	void TopUpBalance(double money);
	Performance FindPerformance(TicketWindow data, std::string name);
	Tickets BuyTicket(TicketWindow data, std::string, int place, int row);
	Tickets BuyReservedTicket(TicketWindow data, std::string, int place, int row);
	void ReservTicket(TicketWindow data, std::string name, int place, int row);
	~Visitor();

protected:
	int userSearchSize;
	int pocketSize;
	double money;
	Tickets* pocket;
	Performance* userSearch;
};

