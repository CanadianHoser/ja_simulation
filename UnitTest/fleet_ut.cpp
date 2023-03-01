#include <stdio.h>
#include <iostream>
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
        // TODO: need to clear out the respective queues in the fleet object
        my_fleet->clear_request_queue();
    }

    void add_airplane(model aircraft_model)
    {
        shared_ptr<aircraft> plane = unique_ptr<aircraft>(new aircraft(aircraft_model));
        my_fleet->add_aircraft(plane);
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
    add_airplane(model::Alpha);
    my_fleet->add_flight_request_to_queue(unique_ptr<flight_req>(new flight_req(2,100)));
    my_fleet->dispatch_aircraft();
    LONGS_EQUAL(0, my_fleet->get_request_queue_size());
}

TEST(fleet, canMatchAircraftToFlightRequest)
{
    add_airplane(model::Alpha);
    shared_ptr<aircraft> dispatched_plane = nullptr;
    shared_ptr<flight_req> request = unique_ptr<flight_req>(new flight_req(2,100));
    dispatched_plane = my_fleet->match_aircraft_to_request(request);
    CHECK_TRUE(dispatched_plane->get_available_range()>=100);
}

TEST(fleet, matchAircraftToFlightRequestReturnsNullIfCannotMatch)
{
    add_airplane(model::Bravo);
    shared_ptr<aircraft> dispatched_plane = nullptr;
    shared_ptr<flight_req> request = unique_ptr<flight_req>(new flight_req(2,100));
    dispatched_plane = my_fleet->match_aircraft_to_request(request);
    CHECK_TRUE(dispatched_plane == nullptr);
}

TEST(fleet, matchedAircraftIsRemovedFromAvailableQueue) 
{
    add_airplane(model::Alpha);
    shared_ptr<aircraft> dispatched_plane = nullptr;
    shared_ptr<flight_req> request = unique_ptr<flight_req>(new flight_req(2,100));
    dispatched_plane = my_fleet->match_aircraft_to_request(request);
    LONGS_EQUAL(0, my_fleet->get_num_of_available_aircraft());
}

TEST(fleet, uponReturnAircraftWithSuitableRangeIsReturnedToAvailability) 
{
    add_airplane(model::Alpha);
    shared_ptr<aircraft> dispatched_plane = nullptr;
    shared_ptr<flight_req> request = unique_ptr<flight_req>(new flight_req(2,100));
    dispatched_plane = my_fleet->match_aircraft_to_request(request);
    LONGS_EQUAL(0, my_fleet->get_num_of_available_aircraft());
    my_fleet->return_aircraft_from_dispatch(dispatched_plane);
    LONGS_EQUAL(1, my_fleet->get_num_of_available_aircraft());
}

TEST(fleet, uponReturnAircraftWithInsufficientRangeIsAddedToChargeQueue) 
{
    add_airplane(model::Alpha);
    shared_ptr<aircraft> dispatched_plane = nullptr;
    shared_ptr<flight_req> request = unique_ptr<flight_req>(new flight_req(2,200));
    dispatched_plane = my_fleet->match_aircraft_to_request(request);
    dispatched_plane->disable_faults();
    (void) dispatched_plane->fly(request->distance_req());
    my_fleet->return_aircraft_from_dispatch(dispatched_plane);
    LONGS_EQUAL(0, my_fleet->get_num_of_available_aircraft());
    LONGS_EQUAL(1, my_fleet->get_num_of_aircraft_in_charge_queue());
}

TEST(fleet, uponReturnAircraftExperiencingFaultIsAddedToRepairQueue) 
{
    add_airplane(model::Echo);
    shared_ptr<aircraft> dispatched_plane = nullptr;
    do {
        shared_ptr<flight_req> request = unique_ptr<flight_req>(new flight_req(2,25));
        dispatched_plane = my_fleet->match_aircraft_to_request(request);
        (void) dispatched_plane->fly(request->distance_req());
        if (aircraft_status::needs_charge == dispatched_plane->get_craft_status())
        {
            std::cout << "Recharging plane" << std::endl;
            dispatched_plane->recharge();
            // dispatched_plane->complete_charge();
        }
        my_fleet->return_aircraft_from_dispatch(dispatched_plane);
    } while (dispatched_plane->get_craft_status() != aircraft_status::system_fault);
    LONGS_EQUAL(0, my_fleet->get_num_of_available_aircraft());
    LONGS_EQUAL(1, my_fleet->get_num_of_aircraft_undergoing_repair());
}

IGNORE_TEST(fleet, chargingAircraftDoesNotClearFault) {};
