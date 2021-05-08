#pragma once
#include "Performance.h"
#include "Tickets.h"

class TicketWindowStructure
{
public:
	
	std::string** hall;
	Tickets GetTicket();
	int GetTicketSize();
	Performance GetPerformance();
	void ChangeTicketSize(int num);
	TicketWindowStructure();
	TicketWindowStructure(int size);
	TicketWindowStructure(TicketWindowStructure& copy);
	TicketWindowStructure(Performance per, Tickets tick);
	void operator=(TicketWindowStructure right);
	void ConsoleOutput();
	~TicketWindowStructure();

private:
	int ticketSize;
	Performance _p;
	Tickets _t;
	int _hallSize;
};

