#include "Club.h"

void Club::processEvent(std::unique_ptr<Event> event) {

    events_queue.push(event);

    switch (event->getType()) {

        case eventType::CLIENT_ARRIVED:
            break;
        case eventType::CLIENT_TAKE_TABLE:
            break;
        case eventType::CLIENT_AWAITS:
            break;
        case eventType::CLIENT_LEFT_IN:
            break;
    }
}

void Club::clientArrive (const ClientEvent& event) {

    if (clients_names[event.getClientName()].inClub()) {
        return;
    }

    if (event.getTime() < start_time) {
        return;
    }

    clients_names[event.getClientName()].setInClub(true);

}

void Club::clientTakeTable (const ClientEvent& event) {

    if (!clients_names[event.getClientName()].inClub()) {

    }

    
}

void Club::clientsAwaits (const ClientEvent& event) {

}

void Club::clientLeft (const ClientEvent& event) {

}