#include "Club.h"


std::vector<Table> Club::getTables() {
    return tables;
}

int Club::getRate() {
    return rate;
}

void Club::processEvent(ClientEvent* event) {

    if (!events_list.empty() && event->getTime() <= events_list.back()->getTime()) {

        throw std::invalid_argument("event time is less or equal than the time of the previous event");

    }

    if (event->getTableNum().has_value() && event->getTableNum() > tables_amount) {

        throw std::invalid_argument("table number is larger than tables amount");
    }

    events_list.push_back(std::unique_ptr<Event>(event));

    switch (event->getType()) {

        case eventType::CLIENT_ARRIVED:
            clientArrive(*event);
            break;
        case eventType::CLIENT_TAKE_TABLE:
            clientTakeTable(*event);
            break;
        case eventType::CLIENT_AWAITS:
            clientsAwaits(*event);
            break;
        case eventType::CLIENT_LEFT_IN:
            clientLeft(*event);
            break;
        default:
            break;
    }
}

void Club::clientArrive (const ClientEvent& event) {

    if (clients_names[event.getClientName()].inClub()) {

        events_list.push_back(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "YouShallNotPass")));
        return;
    }

    if (event.getTime() < start_time) {

        events_list.push_back(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "NotOpenYet")));
        return;
    }

    clients_names[event.getClientName()].setInClub(true);

}

void Club::clientTakeTable (const ClientEvent& event) {

    auto& client = clients_names[event.getClientName()];

    if (!client.inClub()) {
        
        events_list.push_back(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "ClientUnknown")));
        return;
    }

    auto client_table_num = client.getTableNum();

    if (tables[event.getTableNum().value() - 1].isOccpied()) {

        events_list.push_back(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "PlaceIsBusy")));
        return;
    }

    client.setTableNum(event.getTableNum().value());
    tables[event.getTableNum().value() - 1].Occupy(event.getTime());
    
    if (client_table_num.has_value()) {
        tables[client_table_num.value() - 1].Release(event.getTime());
    }
    
}

void Club::clientsAwaits (const ClientEvent& event) {

    for (auto& table: tables) {
        
        if (!table.isOccpied()) {

            events_list.push_back(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "ICanWaitNoLonger!")));
            return;
        }
    }

    if (clients_queue.size() > tables_amount) {

        clients_names[event.getClientName()].setInClub(false);
        events_list.push_back(std::unique_ptr<Event>(new ClientEvent(event.getTime(), eventType::CLIENT_LEFT_OUT, event.getClientName())));
        return;
    }

    clients_queue.push(event.getClientName());
}

void Club::clientLeft(const ClientEvent& event) {
    

    auto& client = clients_names[event.getClientName()];
    
    if (!client.inClub()) {

        events_list.push_back(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "ClientUnknown")));
        return;
    }

    tables[client.getTableNum().value() - 1].Release(event.getTime());
    client.setInClub(false);

    if (!clients_queue.empty()) {

        auto& new_client = clients_names[clients_queue.front()];
        tables[client.getTableNum().value() - 1].Occupy(event.getTime());
        new_client.setTableNum(client.getTableNum().value());

        events_list.push_back(std::unique_ptr<Event>(new ClientEvent(event.getTime(), eventType::CLIENT_TAKE_TABLE_OUT, clients_queue.front(),
        client.getTableNum().value())));

        clients_queue.pop();
    }
    

}

void Club::closeClub() {

    for (auto& table: tables) {

        table.Release(end_time);
    }
    
    std::vector<std::string> names;
    for (auto& pair: clients_names) {

        names.push_back(pair.first);
    }

    std::sort(names.begin(), names.end());
        
    for (auto& name: names) {

        if (clients_names[name].inClub()) {

            events_list.push_back(std::unique_ptr<Event>(new ClientEvent(end_time,
                                                                        eventType::CLIENT_LEFT_OUT, 
                                                                        name)));
        }
    }

}
