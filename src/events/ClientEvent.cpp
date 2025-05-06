#include "ClientEvent.h"

ClientEvent::ClientEvent(const std::string& event_string) {

    auto tokens = splitString(event_string, " ");
    

    try {
        time = Time(tokens[0]);
    }
    catch (std::invalid_argument& ex) {
        throw;
    }

    int event_id = std::stoi(tokens[1]);

    if (!(event_id >= 1 && event_id <= 4) && !(event_id >= 11 && event_id <= 13)) {
        throw std::invalid_argument("invalid event id");
    }

    type = static_cast<eventType>(event_id);
    
    client_name = tokens[2];

    if (tokens.size() > 3) {
        
        table_num = std::stoi(tokens[3]);
    }
}

std::string ClientEvent::getClientName() const { return client_name; }

std::optional<int>  ClientEvent::getTableNum() const { return table_num; }

std::string ClientEvent::toString() const { 

    auto event_string = std::format("{} {} {}", time.toString(), static_cast<int>(type), client_name);

    if (table_num.has_value()) {

        event_string.append(std::format(" {}", table_num.value()));
    }

    return event_string;

}