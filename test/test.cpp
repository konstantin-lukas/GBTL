#include <iostream>
#include "linked_list.h"
int main() {
    gbstl::LinkedList<int> list;
    list.push(6);
    list.push(3);
    list.push(81);
    list.push(8511);
    list.print();
    list[1] = 52;
    list.print();
    list.getElementAt(3) = 1;
    list.print();
    std::cout << list[1] << std::endl;
}