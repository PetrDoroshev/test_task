#include "Event.h"

class ErrorEvent: Event {

private:

    std::string error_name;

public:

    ErrorEvent(Time time_, eventType type_, std::string error_name_)
                                : Event(time_, type_), error_name(error_name_) {};

    std::string getErrorName() const { return error_name; };
    std::string toString() const override { //return std::format("{} {} {}", getTime().toString(), getType(), error_name); 
        return " ";    
    }
};