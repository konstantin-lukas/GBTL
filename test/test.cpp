#include <iostream>
#include "linked_list.h"
#include <memory>
int main() {
    gbstl::LinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    gbstl::LinkedList<int> list2 = std::move(list1);
    list2.append(4);
    list2.append(5);
    std::cout << "Length: " << list2.length() << ", Size: " << sizeof list2 << std::endl;
    for (int value : list2) {
        printf("---%d\n", value);
    }
}