#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
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

// Dispatch all available aircraft for requested flights, record the flight and number of passengers
void fleet::dispatch_aircraft()
{
    shared_ptr<aircraft> dispatched_aircraft; 
    deque<shared_ptr<flight_req>>::iterator req_iter;
    deque<shared_ptr<aircraft>>::iterator airplane_iter;
    
    for (req_iter = request_queue.begin(); req_iter != request_queue.end(); ++req_iter)
    {
        if ((*req_iter)->state == request_state::PENDING) {
            cout << "Dispatching aircraft for " << (*req_iter)->distance_req() << " miles" << endl;
            request_queue.erase(req_iter);
        }
    }
}
