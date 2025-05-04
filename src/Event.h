#include "Time.h"
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

class Event {

private:

    Time time;
    eventType type;
    std::string client_name;
    std::optional<int> table_num;

public:

    Event(Time time_, eventType type_, std::string client_name_, std::optional<int> table_num_= {}): 
                                            time(time_), type(type_), client_name(client_name_), table_num(table_num_) {};

    Time getTime() const { return time; };
    eventType getType() const { return type; };
    std::string getClientName() const { return client_name; }
    std::optional<int> getTableNum() const { return table_num; }

};