#include <iostream>
#include "linked_list.h"
int main() {
    gbtl::linked_list<int> list1;
    list1.push_back(4);
    list1.push_back(5);
    list1.push_back(6);
    std::cout << sizeof(list1) << std::endl;
}