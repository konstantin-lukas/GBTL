#include <iostream>
#include "linked_list.h"
#include <memory>
int main() {
    int array[] = {1,5,2,25,2,6,1,2};
    gbstl::LinkedList<int> list1(array,0,7);
    std::cout << list1.length() << std::endl;
    list1.pushPos(array, 6,0,7);
    std::cout << list1.length() << std::endl;
    for (int val : list1) {
        std::cout << val << std::endl;
    }
}