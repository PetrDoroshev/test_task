#include "Event.h"

class ErrorEvent: public Event {

private:

    std::string error_name;

public:

    ErrorEvent(Time time_, std::string error_name_)
                                : Event(time_, eventType::ERROR), error_name(error_name_) {};

    std::string getErrorName() const { return error_name; };
    std::string toString() const override { 
        return std::format("{} {} {}", getTime().toString(), static_cast<int>(getType()), error_name); 
    }
};