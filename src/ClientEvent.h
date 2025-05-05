#ifndef CLIENT_EVENT_H
#define CLIENT_EVENT_H

#include "Event.h"

class ClientEvent: public Event {

private:

    std::string client_name;
    std::optional<int> table_num;

public:

    ClientEvent(Time time_, eventType type_, std::string client_name_, std::optional<int> table_num_ = {})
                                                        : Event(time_, type_), client_name(client_name_), table_num(table_num_) {};

    ClientEvent(const std::string& event_string);                                                   
    
    std::string getClientName() const;
    std::optional<int> getTableNum() const;
    std::string toString() const override;

};

#endif