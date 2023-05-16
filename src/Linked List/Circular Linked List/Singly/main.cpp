#include <iostream>
#include <string>
#include <random>
#include "./SinglyCircularLinkedList.hpp"

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
    SinglyCircularLinkedList<int> list0({10,9,8,7,6,5,4,3,2,1,0});
    std::cout<<"list0:\n";
    list0.print_list();
    std::cout<<"sorted:\n";
    list0.sort();
    list0.print_list();



}