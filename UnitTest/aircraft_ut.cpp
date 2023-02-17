//
//  linked_lists_tests.cpp
//  HelloWorld
//
//  Created by Warren Hein on 3/10/21.
//

#include <stdio.h>
#include "CppUTest/TestHarness.h"
#include "aircraft.hpp"

TEST_GROUP(aircraft)
{
    void setup() override
    {
    }

    void teardown() override
    {
    }
};

TEST(aircraft, constructorAssignsModel)
{
    aircraft plane(model::Charlie);
    LONGS_EQUAL(160, plane.get_cruise_speed());
}

TEST(aircraft, planeIsIdleOnInit)
{
    aircraft plane(model::Alpha);
    LONGS_EQUAL(aircraft_status::idle, plane.get_craft_status());
}

TEST(aircraft, batteryIsFullyChargedOnInit)
{
    aircraft plane(model::Alpha);
    LONGS_EQUAL(model_data.at(static_cast<int>(model::Alpha)).battery_cap_kWh, plane.get_battery_level());
}
