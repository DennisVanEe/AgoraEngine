#include "model_index_table.hpp"

#include <iostream>

int main()
{
    using namespace agora;

    ModelIndexTable table;

    table.initialize(16);

    table.insert(HASH("school_main_house"), 0);
    table.insert(HASH("powerplant_main_one"), 1);
    table.insert(HASH("powerplant_main_two"), 2);
    table.insert(HASH("apartment_house"), 3);
    table.insert(HASH("main_building_house"), 4);
    table.insert(HASH("formatin_system_and"), 5);
    table.insert(HASH("system in the great"), 6);
    table.insert(HASH("this is the wierdest"), 7);
    table.insert(HASH("quickest fast and great"), 8);

    uint32_t k = 5;
    bool r = table.get(HASH("fast and great"), &k);

    std::cout << k;
}