#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include "Node.hpp"


template<typename T>
class DoublyLinkedList
{
    public:
    DoublyLinkedList() = delete; //handle empty case at some point
    explicit DoublyLinkedList(T value) noexcept;    //TODO
    explicit DoublyLinkedList(std::initializer_list<T> values) noexcept;    //TODO  
    DoublyLinkedList(const DoublyLinkedList& list) noexcept;    //TODO            
    DoublyLinkedList& operator=(const DoublyLinkedList& list) noexcept; //TODO 
    DoublyLinkedList(DoublyLinkedList&& list) noexcept; //TODO                 
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;  //TODO      
    ~DoublyLinkedList();      

    bool operator==(const DoublyLinkedList& other) noexcept; //TODO
                                          

    void add_to_end(T value);   //TODO
    void add_to_start(T value); //TODO
    void insert(T value, size_t index); //TODO
    void delete_end();  //TODO
    void delete_start();    //TODO
    void delete_at(size_t index);   //TODO

    void replace_value(size_t index,T value);   //TODO
    void swap_values(size_t index1, size_t index2); //TODO
    void sort() requires std::is_arithmetic<T>::value;  //TODO
    T access(size_t index) const;   //TODO
    void print_list() const;    //TODO 
    void print_values() const;  //TODO
    T first_value() const;  //TODO
    T last_value() const;   //TODO
    size_t length() const;  //TODO

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<U>& other);


    private:
    Node<T> * walk_list_to_end(Node<T> * current) const;
    Node<T> * walk_list_between_indices(Node<T> * current, size_t& start, size_t end) const;
    size_t m_listLength = 0;
    Node<T> * m_head;
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& other)
{
    Node<T> * current = other.m_head;
    while(current->next)
    {
        os<<"Location: " << current << ", Value: " << current->value <<", Previous: " << current->previous <<", Next: " << current->next << "\n";
        current = current->next;
    }
    os<<"Location: " << current << ", Value: " << current->value <<", Previous: " << current->previous <<", Next: " << current->next << "\n";
    return os;
}

#endif 
