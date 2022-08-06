#include <iostream>
#include "linked_list.h"
#include <memory>
int main() {
    gbstl::LinkedList<int> list1;
    list1.pushTail(1);
    list1.pushTail(3);
    list1.pushTail(2);
    list1.popHead();
    list1.popTail();
    list1.pushHead(52);
    list1.pushHead(51252);
    gbstl::LinkedList<int> list2 = std::move(list1);
    std::cout << list2.head() << " : " << list2.tail() << std::endl;
    return 0;
    for (int val : list2) {
        std::cout << val << std::endl;
    }
}