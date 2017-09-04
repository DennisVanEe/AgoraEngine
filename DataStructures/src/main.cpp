#include "FixedHashMap.hpp"
#include "Hash.hpp"
#include <string>
#include <MemAlloc/DefaultAllocator.hpp>

#include <iostream>


int main()
{
    using namespace agora;

    FixedHashMap<std::string, DefaultAlloc> alloc(g_defaultAllocator);
    alloc.prepare(29);

    alloc.insert(546, "a");
    alloc.insert(546 + 32, "b");
    alloc.insert(546 + 2 * 32, "c");
    alloc.insert(546 + 3 * 32, "d");
    alloc.insert(546 + 4 * 32, "e");

    alloc.remove(546 + 2 * 32);

    std::string* str = alloc.at(546 + 4 * 32);

    std::cout << *str;

    std::cin.get();
    std::cin.get();
    return 0;
}