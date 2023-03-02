#ifndef __AIRCRAFT_HPP__
#define __AIRCRAFT_HPP__
#include <stdint.h>
#include <vector>

enum class model {Alpha, Bravo, Charlie, Delta, Echo};
enum class aircraft_status {idle, in_flight, charging, needs_charge};
enum class ret_code {OK, EXCEEDS_CAPACITY, NEEDS_CHARGE, FAULT_OCCURRED};

struct fixed_model_data_t {
        const uint32_t cruise_speed_mph;
        const uint32_t battery_cap_kWh;
        const float    time_to_charge_hours;
        const float    energy_use_at_cruise; // kWh / mile
        const uint32_t max_passengers;
        const float    fault_probability;
};
extern std::vector<fixed_model_data_t> model_data; 

class aircraft {
    private:
        model    aircraft_model;
        fixed_model_data_t* model_specs;
        uint32_t current_battery_cap;
        uint64_t odometer = 0;
        aircraft_status status = aircraft_status::idle;
        bool simulate_faults = true;
        uint32_t num_faults = 0;
    public:
        aircraft(model aircraft_model);
        aircraft_status get_craft_status() {return status;};
        uint32_t get_cruise_speed() {return model_data.at(static_cast<int>(aircraft_model)).cruise_speed_mph;};
        float get_battery_level() {return 100*current_battery_cap/model_specs->battery_cap_kWh;};
        uint32_t get_available_range() {return current_battery_cap/model_specs->energy_use_at_cruise;}
        uint32_t get_maximum_passengers() {return model_specs->max_passengers;}
        uint64_t get_odometer() {return odometer;}
        uint64_t get_num_of_faults() {return num_faults;}
        ret_code fly(uint32_t distance);
        float recharge();

        // UT Support
        void reset();
        void disable_faults() {simulate_faults = false;};
};
#endif
