#include "Table.h"
#include "Client.h"
#include <vector>
#include <queue>
#include <unordered_map>

class Club {

public:

private:
	
	int tables_amount;
	Time start_time;
	Time end_time;
	int rate;

	std::queue<Client> clients_queue;
	std::queue<std::string> events_queue;
	std::vector<Table> tables;
	std::unordered_map<std::string, Client> clients_names;
	
public:

	Club(int tables_amount, const Time& start_time, const Time& end_time, int rate)
		: tables_amount(tables_amount), start_time(start_time), end_time(end_time), rate(rate) {
		
		tables = std::vector<Table>(tables_amount);
	}

	void processEvent(const std::string& event_string) {

		


	}


};