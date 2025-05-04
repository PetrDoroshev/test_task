#include "Table.h"
#include <cmath>

Time Table::getTimeOccupied() const {

	return Time(total_minutes_occupied / 60, total_minutes_occupied % 60);
}

int Table::getIncome(int rate) const {

	int full_hours = static_cast<int>(ceil(total_minutes_occupied / 60.0));
	return full_hours * rate;
}

void Table::Occupy(Time time) {

	occupied = true;
	time_occupancy_start = time;
}

void Table::Release(Time time) {
	
	if (!occupied) {
		return;
	}

	occupied = false;
	Time time_spend = time - time_occupancy_start;
	
	total_minutes_occupied += (time_spend.getHours() * 60 + time_spend.getMinutes());
	
}
