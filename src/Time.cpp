#include "Time.h"

Time::Time(int hours_, int minutes_): hours(hours_), minutes(minutes_) {
        
    if (hours_ < 0 || minutes_ < 0 || hours_ > 23 || minutes_ > 59) {
        
        throw std::invalid_argument("invalid value");
    }
};

Time::Time(const std::string& time_string) {

    auto tokens = splitString(time_string, ":");
    int hours_ = std::stoi(tokens[0]);
    int minutes_ = std::stoi(tokens[1]);
   
    if (hours_ < 0 || minutes_ < 0 || hours_ > 23 || minutes_ > 59) {
        
        throw std::invalid_argument("invalid value");
    }

    hours = hours_;
    minutes = minutes_;
    
}

int Time::getHours() const {
    return hours;
}

int Time::getMinutes() const {
    return minutes;
}

Time Time::operator- (const Time& other) {

    int t1 = this->hours * 60 + this->minutes;
    int t2 = other.hours * 60 + other.minutes;

    int diff = std::abs(t1 - t2);

    return Time(diff / 60, diff % 60);

}

bool Time::operator<(const Time& other) const
{   
   
    return ((this->hours * 60 + this->minutes) < (other.hours * 60 + other.minutes));
}

bool Time::operator>(const Time& other) const
{
    return ((this->hours * 60 + this->minutes) > (other.hours * 60 + other.minutes));;
}

std::string Time::toString() const {

    return std::format("{:02}:{:02}", hours, minutes); 

}
