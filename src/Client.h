#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <optional>

class Client {

private:
	
	bool in_club = false;
	std::optional<int> table_num;

public:

	bool inClub() const { return in_club; }
	std::optional<int> getTableNum() const { return table_num; }

	void setTableNum(int table_num) { this->table_num = table_num; }
	void setInClub(bool in_club) { this->in_club = in_club;  }

};

#endif