#ifndef __AIRCRAFT_HPP__
#define __AIRCRAFT_HPP__
#include <stdint.h>
#include <vector>

enum class model {Alpha, Bravo, Charlie, Delta, Echo};
enum class aircraft_status {idle, in_flight, charging, needs_charge};

struct fixed_model_data_t {
        const uint32_t cruise_speed_mph;
        const uint32_t battery_cap_kWh;
        const float    time_to_charge_hours;
        const float    energy_use_at_cruise; // kWh / mile
        const uint32_t max_passengers;
        const float    fault_probablility;
};
extern std::vector<const fixed_model_data_t> model_data; 

class aircraft {
    private:
        model    aircraft_model;
        uint32_t current_battery_cap;
        aircraft_status status = aircraft_status::idle;
    public:
        aircraft(model aircraft_model);
        aircraft_status get_craft_status() {return status;};
        uint32_t get_cruise_speed() {return model_data.at(static_cast<int>(aircraft_model)).cruise_speed_mph;};
        uint32_t get_battery_level() {return current_battery_cap;};
};
#endif
