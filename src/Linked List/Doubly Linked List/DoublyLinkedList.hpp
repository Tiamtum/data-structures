#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Node.hpp"


template<typename T>
class DoublyLinkedList
{
    public:
    DoublyLinkedList() = delete; //handle empty case at some point
    explicit DoublyLinkedList(T value) noexcept;
    explicit DoublyLinkedList(std::initializer_list<T> values) noexcept;      
    DoublyLinkedList(const DoublyLinkedList& list) noexcept;            //copy constructor (initialize a previously uninitialized list from some other list's data. )
    DoublyLinkedList& operator=(const DoublyLinkedList& list) noexcept; //copy assignment (replace the data of a previously initialized list with some other list's data. )
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;                 //move constructor
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;      //move assignment
    ~DoublyLinkedList();                                                //destructor

    void add_to_end(T value);
    void add_to_start(T value);
    void insert(T value, size_t index);
    void delete_end();
    void delete_start();
    void delete_at(size_t index);

    void replace_value(size_t index,T value);
    void swap_values(size_t index1, size_t index2);
    void sort() requires std::is_arithmetic<T>::value;
    T access(size_t index) const;
    void print_list() const; 
    void print_values() const;
    T first_value() const;
    T last_value() const;
    size_t length() const;

    private:
    Node<T> * walk_list_to_end(Node<T> * current) const;
    Node<T> * walk_list_between_indices(Node<T> * current, size_t& start, size_t end) const;
    size_t m_listLength = 0;
    Node<T> * m_head;
};


#endif 
