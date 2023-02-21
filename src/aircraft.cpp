#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "aircraft.hpp"

using namespace std;

vector<const fixed_model_data_t> model_data = 
   {{ 120, 320, 0.60, 1.6, 4, 0.25 }, // Alpha
    { 100, 100, 0.20, 1.5, 5, 0.10 }, // Bravo
    { 160, 220, 0.80, 2.2, 3, 0.05 }, // Charlie
    {  90, 120, 0.62, 0.8, 2, 0.22 }, // Delta
    {  30, 150, 0.30, 5.8, 2, 0.61 }, // Echo
   };
   
// Range concerns are even higher when you're off the ground.
const float safety_margin = 10.0;   

// TODO: use a true logging mechanism like easylogging to provide more granular control
bool debug = false;

aircraft::aircraft(model aircraft_model) : aircraft_model(aircraft_model)
{
    model_specs = &model_data.at(static_cast<int>(aircraft_model));
    current_battery_cap = model_specs->battery_cap_kWh;
};

// This is only to be used for unit testing.  
void aircraft::reset() 
{ 
    status = aircraft_status::idle;
    odometer = 0;
    current_battery_cap = model_specs->battery_cap_kWh;
    disable_faults();
    num_faults = 0;
}

ret_code aircraft::fly(uint32_t distance)
{
    ret_code rc;
    if (distance <= get_available_range()) {
        if (debug)
            cout << "Flying " << distance << " miles" << endl;
        current_battery_cap -= distance * model_specs->energy_use_at_cruise;
        odometer += distance;
        if (get_battery_level() <= safety_margin) {
            status = aircraft_status::needs_charge;
            rc = ret_code::NEEDS_CHARGE;
        } else {
            rc = ret_code::OK;
        }

        if (simulate_faults) {
            // TODO: Check this probablility algorithm
            bool fault_occurs = (rand()%100) < 100*model_specs->fault_probability*distance/model_specs->cruise_speed_mph;
            if (fault_occurs) {
                if (debug)
                    cout << "FAULT occurred! " << endl;
                num_faults++;
                rc = ret_code::FAULT_OCCURRED;
            }
        }
    } else {
        if (debug)
            cout << "Requested distance exceeds planes available range" << endl;
        rc =  ret_code::EXCEEDS_CAPACITY;
    }
    return rc;
}

float aircraft::recharge() 
{
    float time_to_charge = (model_specs->battery_cap_kWh - current_battery_cap) *
                            model_specs->time_to_charge_hours/model_specs->battery_cap_kWh;
    current_battery_cap = model_specs->battery_cap_kWh;
    return time_to_charge;
}
