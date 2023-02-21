#include <stdio.h>
#include "CppUTest/TestHarness.h"
#include "fleet.hpp"

using namespace std; 

TEST_GROUP(fleet)
{
    unique_ptr<fleet> my_fleet = unique_ptr<fleet>(new fleet());
    void setup() override
    {
    }

    void teardown() override
    {
    }
};

TEST(fleet, addPlaneIsAvailableForUse)
{
    shared_ptr<aircraft> plane = unique_ptr<aircraft>(new aircraft(model::Bravo));
    my_fleet->add_aircraft(plane);
    LONGS_EQUAL(1, my_fleet->get_num_of_aircraft());
}

TEST(fleet, dispatchAircraftIfAvailable)
{
    shared_ptr<aircraft> plane = unique_ptr<aircraft>(new aircraft(model::Bravo));
    my_fleet->add_aircraft(plane);
    my_fleet->add_flight_request_to_queue(unique_ptr<flight_req>(new flight_req(2,100)));
    my_fleet->dispatch_aircraft();
    LONGS_EQUAL(0, my_fleet->get_request_queue_size());
}
