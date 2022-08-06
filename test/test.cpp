#include <iostream>
#include "linked_list.h"
#include <memory>
int main() {
    gbstl::LinkedList<int> list1;

    list1.append(1);
    list1.append(2);
    list1.append(3);
    gbstl::LinkedList<int> list2 = std::move(list1);
    gbstl::LinkedList<int> list3;
    list2.append(4);;
    list3 = std::move(list2);
    list3.append(5);
    list3[1] = list3[2];
    std::cout << "Length: " << list3.length() << ", Size: " << sizeof list3 << std::endl;
    for (int value : list3) {
        printf("---%d\n", value);
    }
}