#include <stdlib.h>
#include <string>
#include <vector>
#include "aircraft.hpp"

std::vector<const fixed_model_data_t> model_data = 
   {{ 120, 320, 0.60, 1.6, 4, 0.25 }, // Alpha
    { 100, 100, 0.20, 1.5, 5, 0.10 }, // Bravo
    { 160, 220, 0.80, 2.2, 3, 0.05 }, // Charlie
    {  90, 120, 0.62, 0.8, 2, 0.22 }, // Delta
    {  30, 150, 0.30, 5.8, 2, 0.61 }, // Echo
   };
   
aircraft::aircraft(model aircraft_model) : aircraft_model(aircraft_model)
{
    current_battery_cap = model_data.at(static_cast<int>(aircraft_model)).battery_cap_kWh;
};
