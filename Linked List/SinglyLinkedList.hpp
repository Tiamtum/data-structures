#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.hpp"

template <typename T>
class SinglyLinkedList
{
    public:
    SinglyLinkedList() = delete;
    SinglyLinkedList(T value);

    ~SinglyLinkedList();

    void add_to_end(T value);
    void add_to_start(T value);
    void insert(T value, size_t index);


    void print() const; 
    size_t length() const;

    private:
    size_t m_listLength=0;
    Node<T> * m_head;
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T value)
{
    m_head = new Node<T>;
    m_head->value = value;
    m_head->next = nullptr;
    m_listLength++;
}
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    // std::cout<<"SinglyLinkedList destructor called\n";
    Node<T> * current = m_head;
    while(current->next != nullptr)
    {
        Node<T> * temp = current;
        current = current->next;
        // std::cout<<"deleting node: value=" << temp->value << ", next: " << temp->next << "\n";
        delete temp;
    }
    // std::cout<<"deleting node: value=" << current->value << ", next: " << current->next << "\n";
    delete current;
    
}

template <typename T>
void SinglyLinkedList<T>::add_to_end(T value)
{
    if(m_head->next == nullptr)
    {
        Node<T> * tail = new Node<T>;
        m_head->next = tail;
        tail->value = value;
        tail->next = nullptr;
        m_listLength++;
    }
    else
    {
        Node<T> * current = m_head;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        Node<T> * newTail = new Node<T>;
        current->next = newTail;
        newTail->value = value;
        newTail->next = nullptr;
        m_listLength++;
    }
}

template <typename T>
void SinglyLinkedList<T>::add_to_start(T value)
{
    Node<T> * newHead = new Node<T>;
    newHead->value = value;
    newHead->next = m_head;
    m_head = newHead;
    m_listLength++;
}

template <typename T>
void SinglyLinkedList<T>::insert(T value, size_t index)
{
    if(index == 0)
    {
        this->add_to_start(value);
    }
    else if(index > 0 && index <= m_listLength-1)
    {
        Node<T> * newNode = new Node<T>;
        newNode->value = value;
        
        Node<T> * current = m_head;
        size_t i = 0 ;
        while(i<index)
        {
            if(i==index-1)
            {
                newNode->next = current->next; //link the new node to the current next node
                current->next = newNode; //link the current node to the new node
            }
            current = current->next;
            i++;
        }
    }
    else
    {
        std::cout<<"Out of bounds index for insert().\n";
        exit(EXIT_FAILURE);
    }
}

template<typename T>
void SinglyLinkedList<T>::print() const 
{
    Node<T> * current = m_head;
    while(current->next != nullptr)
    {
        std::cout<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
        current = current->next;
    }
    std::cout<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
}

template<typename T>
size_t SinglyLinkedList<T>::length() const{
    return m_listLength;
}



#endif 