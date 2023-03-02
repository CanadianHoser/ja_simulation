#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "fleet.hpp"

using namespace std; 

fleet::fleet() {};
void fleet::add_aircraft(shared_ptr<aircraft> new_plane) 
{ 
    airplanes.push_back(new_plane);
    available_airplanes.push_back(new_plane);
    num_of_aircraft++;
}

void fleet::add_flight_request_to_queue(unique_ptr<flight_req> request)
{
    request_queue.push_back(move(request));
}

// Current algorithm: find first available match
// TODO: find aircraft with smallest passenger capacity which fits the request
std::shared_ptr<aircraft> fleet::match_aircraft_to_request(std::shared_ptr<flight_req> request)
{
    list<shared_ptr<aircraft>>::iterator aircraft_iter;
    std::shared_ptr<aircraft> dispatched_plane = {nullptr};
    for (aircraft_iter = available_airplanes.begin(); aircraft_iter != available_airplanes.end(); ++aircraft_iter)
    {
        if ((*aircraft_iter)->get_available_range() >= request->distance_req() &&
            (*aircraft_iter)->get_maximum_passengers() >= request->passenger_cnt())
        {
            request->state = request_state::DISPATCHED;
            dispatched_plane = *aircraft_iter;
            available_airplanes.erase(aircraft_iter);
            break;
        }
    }
    return dispatched_plane;
}

// Dispatch all available aircraft for requested flights, record the flight and number of passengers
void fleet::dispatch_aircraft()
{
    shared_ptr<aircraft> dispatched_aircraft = nullptr; 
    deque<shared_ptr<flight_req>>::iterator req_iter;
    deque<shared_ptr<aircraft>>::iterator airplane_iter;
    
    if (request_queue.size() == 0) {
	    cout << "No requests to dispatch" << endl;
	    return;
    }

    for (req_iter = request_queue.begin(); req_iter != request_queue.end(); )
    {
        if ((*req_iter)->state == request_state::PENDING) {
            dispatched_aircraft = match_aircraft_to_request(*req_iter);
            if (dispatched_aircraft) {
                cout << "Dispatching aircraft for " << (*req_iter)->distance_req() << " miles" << endl;
                request_queue.erase(req_iter);
            } else {
		req_iter++;
	    }
        } else {
  	    req_iter++;
        }
    }
}

void fleet::return_aircraft_from_dispatch(std::shared_ptr<aircraft> dispatched_aircraft)
{
    // Check status of aircraft
    if (dispatched_aircraft->get_craft_status() == aircraft_status::idle) {
        // cout << "Putting plane back into availability queue" << endl;
        available_airplanes.emplace_back(dispatched_aircraft);
    } else if (dispatched_aircraft->get_craft_status() == aircraft_status::needs_charge) {
        // cout << "Putting plane into charge queue" << endl;
        charge_queue.emplace_back(dispatched_aircraft);
    } else if (dispatched_aircraft->get_craft_status() == aircraft_status::system_fault) {
        // cout << "Putting plane into repair queue" << endl;
        repair_queue.emplace_back(dispatched_aircraft);
    }
}

void fleet::clear_request_queue() {
    request_queue.clear();
}
