#ifndef TABLE_H
#define TABLE_H

#include "Time.h"

class Table {

private:

	int total_minutes_occupied = 0;
	bool is_occupied = false;
	Time time_occupancy_start;

public:
	
	Table() {};
	
	Time getTimeOccupied() const;
	int getIncome(int rate) const;
	bool isOccpied() const;
	void Occupy(Time time);
	void Release(Time time);
};


#endif