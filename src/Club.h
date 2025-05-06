#ifndef CLUB_H
#define CLUB_H

#include "Table.h"
#include "Client.h"
#include "Utils.h"
#include "events/ClientEvent.h"
#include "events/ErrorEvent.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>

class Club {

public:

private:
	
	int tables_amount;
	Time start_time;
	Time end_time;
	int rate;

	std::queue<std::string> clients_queue;
	std::queue<std::unique_ptr<Event>> events_queue;
	std::vector<Table> tables;
	std::unordered_map<std::string, Client> clients_names;

	void clientArrive (const ClientEvent& event);
	void clientTakeTable (const ClientEvent& event);
	void clientsAwaits (const ClientEvent& event);
	void clientLeft (const ClientEvent& event);
	
	
public:

	Club(int tables_amount, const Time& start_time, const Time& end_time, int rate)
		: tables_amount(tables_amount), start_time(start_time), end_time(end_time), rate(rate) {
		
		tables = std::vector<Table>(tables_amount);
	}

	void processEvent(ClientEvent* event); 
	std::vector<Table> getTables();
};


#endif