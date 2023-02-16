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

TEST(aircraft, checkTestHarness)
{
    CHECK_EQUAL(2, add_num(1,1));
}
