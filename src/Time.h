#include <stdexcept>

class Time {

private:
    int hours;
    int minutes;

public:

    Time() {};
    Time(int hours_, int minutes_): hours(hours_), minutes(minutes_) {
        
        if (hours_ < 0 || minutes_ < 0 || hours_ > 23 || minutes_ > 59) {
            
            throw std::invalid_argument("invalid value");
        }
    }

    int getHours() const;
    int getMinutes() const;
    Time operator- (const Time& other);
    bool operator< (const Time& other) const;
    bool operator> (const Time& other) const;
};






