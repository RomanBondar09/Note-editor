#include "Rest.h"
#include <iostream>

Rest::Rest()
{}

void Rest::print()
{
    for (size_t i = duration; i > 0; i >>= 1)
        std::cout << "_";
}

int Rest::type()
{
    return REST;
}
