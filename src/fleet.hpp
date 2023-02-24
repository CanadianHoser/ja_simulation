#ifndef __FLEET_HPP__
#define __FLEET_HPP__
#include <stdint.h>
#include <vector>
#include <deque>
#include <list>
#include "aircraft.hpp"

// Details about a request for a flight
enum class request_state {PENDING, DISPATCHED, IN_FLIGHT, COMPLETED};
class flight_req {
    private:
        unsigned int num_passengers;
        uint32_t distance;
    // TODO: Need to handle both one-way and round trip flights.  This impacts overall aircraft model stats.
    public:
        flight_req(int num_passengers, uint32_t distance) : num_passengers(num_passengers), distance(distance) {};        
        unsigned int passenger_cnt() {return num_passengers;};
        uint32_t distance_req() {return distance;};
        request_state state = request_state::PENDING;
};

class fleet {
    private:
        uint32_t num_of_aircraft = 0;
        // TODO: semaphore handling for available chargers
        // uint32_t num_of_chargers = 0;
        std::vector<std::shared_ptr<aircraft>> airplanes;   // Entire fleet
        std::list<std::shared_ptr<aircraft>> available_airplanes;  // Available for flight
        std::deque<std::shared_ptr<aircraft>> charge_queue; // Battery depleted
        std::deque<std::shared_ptr<aircraft>> repair_queue; // Experienced fault
        std::deque<std::shared_ptr<flight_req>> request_queue;  // Requests for flights
    public:
        fleet();
        uint32_t get_num_of_aircraft() { return num_of_aircraft;};
        uint32_t get_num_of_available_aircraft() { return available_airplanes.size();};
        void add_aircraft(std::shared_ptr<aircraft> new_plane);
        void add_flight_request_to_queue(std::unique_ptr<flight_req> request);
        void dispatch_aircraft();
        uint32_t get_request_queue_size() {return request_queue.size();};
        std::shared_ptr<aircraft> match_aircraft_to_request(std::shared_ptr<flight_req> request);
        void clear_request_queue();
};
#endif /* __FLEET_HPP__ */
