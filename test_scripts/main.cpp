#include <iostream>
#include "linked_list.h"
#include "vector.h"
int main() {
    gbtl::linked_list<int> list1{1,2,3};
    auto list2 = std::move(list1);
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);
    gbtl::vector<float, 3> vec3d{};
    std::cout << list2 << std::endl;
}