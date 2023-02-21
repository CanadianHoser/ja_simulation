#ifndef __FLEET_HPP__
#define __FLEET_HPP__
#include <stdint.h>
#include <vector>
#include <deque>
#include "aircraft.hpp"

class flight_req {
    private:
        unsigned int num_passengers;
        uint32_t distance;
    public:
        flight_req(int num_passengers, uint32_t distance) : num_passengers(num_passengers), distance(distance) {};        
        unsigned int passenger_cnt() {return num_passengers;};
        uint32_t distance_req() {return distance;};
};
class fleet {
    private:
        uint32_t num_of_aircraft = 0;
        // uint32_t num_of_chargers = 0;
        std::vector<std::shared_ptr<aircraft>> airplanes;
        std::vector<std::shared_ptr<aircraft>> available_airplanes;
        std::deque<std::shared_ptr<aircraft>> charge_queue;
        std::deque<std::shared_ptr<aircraft>> repair_queue;
        std::deque<std::shared_ptr<flight_req>> request_queue;
    public:
        fleet();
        uint32_t get_num_of_aircraft() { return num_of_aircraft;};
        void add_aircraft(std::shared_ptr<aircraft> new_plane);
        void add_flight_request_to_queue(std::unique_ptr<flight_req> request);
        void dispatch_aircraft();
        uint32_t get_request_queue_size() {return request_queue.size();};
};
#endif /* __FLEET_HPP__ */
