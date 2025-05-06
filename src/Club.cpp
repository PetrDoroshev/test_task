#include "Club.h"

std::vector<Table> Club::getTables() {
    return tables;
}

void Club::processEvent(ClientEvent* event) {

    events_queue.push(std::unique_ptr<Event>(event));

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

        events_queue.push(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "YouShallNotPass")));
        return;
    }

    if (event.getTime() < start_time) {

        events_queue.push(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "NotOpenYet")));
        return;
    }

    clients_names[event.getClientName()].setInClub(true);

}

void Club::clientTakeTable (const ClientEvent& event) {

    auto client = clients_names[event.getClientName()];

    if (!client.inClub()) {
        
        events_queue.push(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "ClientUnknown")));
        return;
    }

    auto client_table_num = client.getTableNum();

    if (tables[event.getTableNum().value() - 1].isOccpied()) {

        events_queue.push(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "PlaceIsBusy")));
        return;
    }

    client.setTableNum(event.getTableNum().value() - 1);
    tables[event.getTableNum().value() - 1].Occupy(event.getTime());
    
    if (client_table_num.has_value()) {
        tables[client_table_num.value() - 1].Release(event.getTime());
    }
    
}

void Club::clientsAwaits (const ClientEvent& event) {

    for (auto& table: tables) {
        
        if (!table.isOccpied()) {

            events_queue.push(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "ICanWaitNoLonger!")));
            return;
        }
    }

    if (clients_queue.size() > tables_amount) {

        clients_names[event.getClientName()].setInClub(false);
        events_queue.push(std::unique_ptr<Event>(new ClientEvent(event.getTime(), eventType::CLIENT_LEFT_OUT, event.getClientName())));
        return;
    }

    clients_queue.push(event.getClientName());
}

void Club::clientLeft (const ClientEvent& event) {

    auto client = clients_names[event.getClientName()];
    
    if (!client.inClub()) {

        events_queue.push(std::unique_ptr<Event>(new ErrorEvent(event.getTime(), "ClientUnknown")));
        return;
    }

    tables[client.getTableNum().value() - 1].Release(event.getTime());
    client.setInClub(false);
    
    if (!clients_queue.empty()) {

        auto new_client = clients_names[clients_queue.front()];
        tables[client.getTableNum().value() - 1].Occupy(event.getTime());
        client.setTableNum(client.getTableNum().value() - 1);

        events_queue.push(std::unique_ptr<Event>(new ClientEvent(event.getTime(), eventType::CLIENT_TAKE_TABLE_OUT, event.getClientName())));
    }

}