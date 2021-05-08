#pragma once
#include "TicketWindowStructure.h"

class TicketWindow
{
public:
	TicketWindow();
	TicketWindow(const TicketWindow& copy);
	TicketWindow(std::string fileNamePerformance, std::string fileNameTickets);
	Tickets BuyTicket(std::string value, int place, int row);
	Tickets BuyReservedTicket(std::string value, int place, int row);
	void AddLine(TicketWindowStructure till, TicketWindowStructure* nameSpace, int someSize);
	TicketWindowStructure operator[](int index);
	bool FindPerformance(std::string, int i);
	bool FindReservedPerformance(std::string, int i);
	int getSizeForSold();
	int getSizeReserved();
	int getSizeAll();
	int getMoney(std::string name);
	TicketWindowStructure* GetBuy();
	TicketWindowStructure* GetReserved();
	void ReservTicket(std::string value, int place, int row);
	~TicketWindow();
	void ConsoleOutput();

private:
	int _size;
	TicketWindowStructure* _till;
	int _sizeForSold;
	TicketWindowStructure* _sold;
	int _sizeForReserved;
	TicketWindowStructure* _reserved;
};

