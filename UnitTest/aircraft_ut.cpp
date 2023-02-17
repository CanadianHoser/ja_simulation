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
    DOUBLES_EQUAL(100.0, plane.get_battery_level(), 0);
}

TEST(aircraft, rechargeRestoresBatteryToMaxCapacity)
{
    aircraft plane(model::Alpha);
    plane.fly(100);
    plane.recharge();
    DOUBLES_EQUAL(100.0, plane.get_battery_level(), 0);
}
TEST_GROUP(fly_plane)
{
    std::unique_ptr<aircraft> my_plane = std::unique_ptr<aircraft>(new aircraft(model::Alpha));
    void setup() override
    {
    }

    void teardown() override
    {
        my_plane->recharge();
    }
};

TEST(fly_plane, flightCausesBatteryToDeplete)
{
    my_plane->fly(100);
    CHECK_FALSE(model_data.at(static_cast<int>(model::Alpha)).battery_cap_kWh == my_plane->get_battery_level());
}

TEST(fly_plane, flightRequestBeyondRangeCausesError)
{
    ret_code rc = my_plane->fly(100000);
    LONGS_EQUAL(ret_code::EXCEEDS_CAPACITY, rc);
}

TEST(fly_plane, canCalculateCurrentRangeForAircraft)
{
    LONGS_EQUAL(200, my_plane->get_available_range());
}
