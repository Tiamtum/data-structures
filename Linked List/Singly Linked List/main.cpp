#include <iostream>
#include "SinglyLinkedList.hpp"

int main() 
{
    SinglyLinkedList<int> list(0);
    list.add_to_start(345);
    for(size_t i = 1 ; i<11; i++)
    {
        list.add_to_end(2*i);
        list.add_to_start(-2*i);
    }

    list.insert(999,0);
    list.insert(999,list.length()-1);
    list.insert(999,list.length()/2);


    std::cout<<"List length = " << list.length() << "\n";
    list.print_values();

    // size_t oldListLength = list.length();
    // for(size_t i = 0; i<oldListLength-2; i++)
    // {
    //     list.delete_at(1);
    // }
    // std::cout<<"List length = " << list.length() << "\n";
    // list.print_values();

    SinglyLinkedList<int> list2(list);
    std::cout<<"List2 length = " << list2.length() << "\n";
    list2.print_values();

}