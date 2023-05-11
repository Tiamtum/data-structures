#include <iostream>
#include "SinglyLinkedList.hpp"

int main() 
{
    SinglyLinkedList<int> list(0);
    for(size_t i = 1 ; i<11; i++)
    {
        list.add_to_end(2*i);
        list.add_to_start(-2*i);
    }

    list.insert(9999,0);
    list.insert(9999,list.length()-1);
    list.insert(9999,list.length()/2);



    

    list.print();
    std::cout<<"list.length= " << list.length() << "\n";

    


}