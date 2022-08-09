#include <iostream>
#include "linked_list.h"
#include <memory>
int main() {
    gbstl::LinkedList<int> list1;
    int array[] = {4,5,6};

    list1.pushTail(array, 1, 2);
    list1.pushHead(array, 0, 2);

    /*list1.popHead();
    list1.popTail();
    list1.pushHead(52);
    list1.pushHead(51252);
    list1.popPos(0);
    list1.popTail();
    list1.popTail();*/
    gbstl::LinkedList<int> list2 = std::move(list1);
    for (int val : list2) {
        std::cout << val << std::endl;
    }
    printf("LEN: %d, HEAD: %d, TAIL: %d",list2.length(),list2.head(),list2.tail());
}