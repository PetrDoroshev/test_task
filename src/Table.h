#include "Time.h"

class Table {

private:

	int total_minutes_occupied = 0;
	bool occupied = false;
	Time time_occupancy_start;

public:
	
	Table() {};
	Time getTimeOccupied() const;
	int getIncome(int rate) const;
	void Occupy(Time time);
	void Release(Time time);
};