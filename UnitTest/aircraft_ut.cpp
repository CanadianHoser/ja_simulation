#include <stdio.h>
#include "CppUTest/TestHarness.h"
#include "aircraft.hpp"

using namespace std;

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
    unique_ptr<aircraft> my_plane = unique_ptr<aircraft>(new aircraft(model::Alpha));
    void setup() override
    {
        my_plane->disable_faults();
    }

    void teardown() override
    {
        my_plane->reset();
    }
};

TEST(fly_plane, flightCausesBatteryToDeplete)
{
    my_plane->fly(100);
    DOUBLES_EQUAL(50.0, my_plane->get_battery_level(), 0);
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

TEST(fly_plane, planeNeedsChargeWhenBatteryDepleted)
{
    ret_code rc = my_plane->fly(200);
    LONGS_EQUAL(aircraft_status::needs_charge, my_plane->get_craft_status());
    LONGS_EQUAL(ret_code::NEEDS_CHARGE, rc);
}

TEST(fly_plane, odometerIncrementsDuringFlight)
{
    my_plane->fly(200);
    LONGS_EQUAL(200, my_plane->get_odometer());
}

TEST_GROUP(airplane_fault)
{
    unique_ptr<aircraft> my_plane = unique_ptr<aircraft>(new aircraft(model::Alpha));
    void setup() override
    {
    }

    void teardown() override
    {
        my_plane->reset();
    }
};

TEST(airplane_fault, faultsCanOccur)
{
    // Generate a large enough number of flights to approximate the the statistical faults
    for (int iteration = 0; iteration < 1000; iteration++) {
        my_plane->fly(120);
        my_plane->recharge();
    }
    // LONGS_EQUAL(2000, my_plane->get_num_of_faults());
    DOUBLES_EQUAL(0.25, my_plane->get_num_of_faults()/1000.0, 0.05);
}
