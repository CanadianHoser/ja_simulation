#include <stdio.h>
#include "CppUTest/TestHarness.h"
#include "fleet.hpp"

TEST_GROUP(fleet)
{
    void setup() override
    {
    }

    void teardown() override
    {
    }
};

TEST(fleet, sanityTest)
{
    LONGS_EQUAL(1, 1);
}
