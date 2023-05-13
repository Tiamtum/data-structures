#include <iostream>
#include "SinglyLinkedList.hpp"

int main() 
{
    // SinglyLinkedList<int> list(3.14);
    // list.add_to_start(345);
    // for(size_t i = 1 ; i<11; i++)
    // {
    //     list.add_to_end(2*i);
    //     list.add_to_start(-2*i);
    // }

    // list.insert(999,0);
    // list.insert(999,list.length()-1);
    // list.insert(999,list.length()/2);


    // std::cout<<"List length = " << list.length() << "\n";
    // // list.print_values();
    // // list.print_list();

    // SinglyLinkedList<int> list2(list);
    // std::cout<<"List2 length = " << list2.length() << "\n";
    // list2.print_list();

    // SinglyLinkedList<int> list3(0);
    // for(size_t i = 0 ; i<list2.length()-1; i++)
    // {
    //     list3.add_to_end(i+1);
    // }
    // list3.print_list();
    // std::cout<<"List3 length = " << list3.length() << "\n";

    // list3 = list2;
    // list3.print_list();
    
    SinglyLinkedList<int> list1(1);
    list1.add_to_end(2);
    list1.add_to_end(3);
    list1.add_to_end(4);
    list1.add_to_end(5);
    list1.add_to_end(6);

    SinglyLinkedList<int> list2(0);
    list2.add_to_end(-1);
    list2.add_to_end(-2);
    std::cout<<"=List1=\n";
    list1.print_list();
    std::cout<<"=List2=\n";
    list2.print_list();
    std::cout<<"list1=list2\n";
    list1=list2;
    list1.print_list();



}