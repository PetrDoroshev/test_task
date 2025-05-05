#ifndef TIME_H
#define TIME_H

#include <stdexcept>
#include <format>
#include "Utils.h"

class Time {

private:

    int hours = 0;
    int minutes = 0;

public:

    Time() {};
    Time(int hours_, int minutes_);
    Time(const std::string& time_string);

    int getHours() const;
    int getMinutes() const;
    Time operator- (const Time& other);
    bool operator< (const Time& other) const;
    bool operator> (const Time& other) const;
    std::string toString() const;
};

#endif




