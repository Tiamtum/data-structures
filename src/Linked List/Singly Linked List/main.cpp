#include <iostream>
#include <string>
#include <random>
#include "SinglyLinkedList.hpp"

int randInt(int from, int to)
{    
    std::random_device dev; //seed for the random number engine
    std::mt19937 gen(dev()); //mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<std::mt19937::result_type> dist(from,to);               
    return dist(gen);
}
float randFloat(int from, int to)
{
    std::random_device dev;  
    std::mt19937 gen(dev()); 
    std::uniform_real_distribution<> dist(static_cast<float>(from), static_cast<float>(to));
    return dist(gen);
}

int main() 
{
    SinglyLinkedList<std::string> list;
    std::cout<<list.length()<<"\n";
    list.insert("a",2345345);
    list.insert("b",0);
    list.insert("c",1);
    list.delete_end();
    list.delete_end();
    list.delete_end();
    list.add_to_end("hello");

    // list.add_to_start("b");
    // list.add_to_start("c");
    // list.add_to_start("d");
    // list.add_to_start("e");
    std::cout<<list;
    std::cout<<list.length()<<"\n";




}