#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H

#include <iostream>
#include <iomanip>
#include "Node.hpp"

template<typename T>
class CircularDoublyLinkedList
{
    public:
    CircularDoublyLinkedList() = delete; //handle empty case at some point
    explicit CircularDoublyLinkedList(T value) noexcept;    
    explicit CircularDoublyLinkedList(std::initializer_list<T> values) noexcept;     
    CircularDoublyLinkedList(const CircularDoublyLinkedList& other) noexcept;                
    CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList& other) noexcept;  
    CircularDoublyLinkedList(CircularDoublyLinkedList&& other) noexcept;                
    CircularDoublyLinkedList& operator=(CircularDoublyLinkedList&& other) noexcept;        
    ~CircularDoublyLinkedList();    

    bool operator==(const CircularDoublyLinkedList& other) noexcept; 
                                          
    void add_to_end(T value);   
    void add_to_start(T value);  
    void insert(T value, size_t index); 
    void delete_end();  
    void delete_start();    
    void delete_at(size_t index);   

    void replace_value(size_t index,T value); 
    void swap_values(size_t index1, size_t index2); 
    void sort() requires std::is_arithmetic<T>::value;  
    T access_from_start(size_t index) const;
    T access_from_end(size_t index) const;  
    Node<T> * get_address(size_t index) const;
    Node<T> * get_next_address(size_t index) const;
    Node<T> * get_previous_address(size_t index) const;
    void print_values() const;  
    T first_value() const;  
    T last_value() const;   
    size_t length() const;  

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const CircularDoublyLinkedList<U>& other); 

    private:
    Node<T> * walk_list_to_end(Node<T> * current) const;    
    Node<T> * walk_list_fowards_between_indices(Node<T> * current, size_t& start, size_t end) const;  
    Node<T> * walk_list_to_start(Node<T> * current) const;    
    Node<T> * walk_list_backwards_between_indices(Node<T> * current, size_t& start, size_t end) const;  

    size_t m_listLength = 0;
    Node<T> * m_head;
    Node<T> * m_tail;
};

#endif