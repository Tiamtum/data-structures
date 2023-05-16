#include <iostream>
#include <string>
#include <random>
#include "SinglyLinkedList.hpp"


int main() 
{
    SinglyLinkedList<int> list({1,2,3,4,5});


    list.print_values();
    list.swap_values(0,4);
    std::cout<<"swapped\n";
    list.print_values();
    list.swap_values(4,0);
    std::cout<<"swapped\n";
    list.print_values();

}