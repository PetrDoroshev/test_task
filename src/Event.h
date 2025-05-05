#include <string>
#include <optional>

enum class eventType {

    CLIENT_ARRIVED        = 1,
    CLIENT_TAKE_TABLE     = 2,
    CLIENT_AWAITS         = 3,
    CLIENT_LEFT_IN        = 4,
    CLIENT_LEFT_OUT       = 11,
    CLIENT_TAKE_TABLE_OUT = 12,
    ERROR                 = 13
};

/*
class Event {

private:

    Time time;
    eventType type;

public:

    Event(Time time_, eventType type_): time(time_), type(type_) {};

    Time getTime() const { return time; };
    eventType getType() const { return type; };
    virtual std::string toString() const = 0;
};
*/