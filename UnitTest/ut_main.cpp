#include "CppUTest/CommandLineTestRunner.h"
#include <random>

int main(int ac, char** av)
{
    srand(time(nullptr));
    return CommandLineTestRunner::RunAllTests(ac, av);
}
