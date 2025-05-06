#ifndef CLUB_H
#define CLUB_H

#include "Table.h"
#include "Client.h"
#include "Utils.h"
#include "events/ClientEvent.h"
#include "events/ErrorEvent.h"
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <iostream>

class Club {

public:

private:
	
	unsigned int tables_amount;
	Time start_time;
	Time end_time;
	unsigned int rate;

	std::queue<std::string> clients_queue;
	std::list<std::unique_ptr<Event>> events_list;
	std::vector<Table> tables;
	std::unordered_map<std::string, Client> clients_names;

	void clientArrive (const ClientEvent& event);
	void clientTakeTable (const ClientEvent& event);
	void clientsAwaits (const ClientEvent& event);
	void clientLeft (const ClientEvent& event);
	
	
public:

	Club(unsigned int tables_amount, const Time& start_time, const Time& end_time, unsigned int rate);

	void processEvent(ClientEvent* event); 
	void closeClub();

	std::vector<Table> getTables();
	int getRate();
	void printEvents();
};


#endif