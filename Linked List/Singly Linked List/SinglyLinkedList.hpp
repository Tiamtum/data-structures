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

    void delete_end();
    void delete_start();
    void delete_at(size_t index);

    T access(size_t index) const;
    void print_list() const; 
    void print_values() const;
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
    Node<T> * current = m_head;
    while(current->next)
    {
        Node<T> * temp = current;
        current = current->next;
        delete temp;
    }
    delete current;
}

template <typename T>
void SinglyLinkedList<T>::add_to_end(T value)
{
    if(!(m_head->next))
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
        while(current->next)
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
        m_listLength++;
    }
    else
    {
        std::cout<<"Out of bounds index for insert().\n";
        exit(EXIT_FAILURE);
    }
}

template <typename T>
void SinglyLinkedList<T>::delete_end()
{
    if(m_listLength == 1)
    {
        std::cout<<"Error: List consists of a single node.\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        Node<T> * current = m_head;
        size_t i = 0;
        while(current->next)
        {
            if(i == m_listLength-2)
            {
                delete(current->next);
                m_listLength--;
                current->next = nullptr;
                break;
            }
            i++;
            current = current->next;
        }
    }
}

template <typename T>
void SinglyLinkedList<T>::delete_start()
{
    if(m_listLength == 1)
    {
        std::cout<<"Error: List consists of a single node.\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        Node<T> * temp = m_head;
        m_head = temp->next;
        delete temp;
        m_listLength--;
    }
}
template <typename T>
void SinglyLinkedList<T>::delete_at(size_t index)
{   
    if(m_listLength == 1)
    {
        std::cout<<"Error: List consists of a single node.\n";
        exit(EXIT_FAILURE);
    }
    else if(index == 0)
    {
        this->delete_start();
    }
    else if(index == m_listLength-1)
    {
        this->delete_end();
    }
    else if(index > 0 && index < m_listLength-1)
    {
        Node<T> * current = m_head;
        size_t i = 0;
        while(current->next)
        {
            if(i == index-1)
            {
                Node<T> * temp = current->next;
                current->next = temp->next;
                delete temp;
                m_listLength--;
                break;
            }
            i++;
            current = current->next;
        }
    }
    else
    {
        std::cout<<"Out of bounds index for delete_at().\n";
        exit(EXIT_FAILURE);        
    }
}


template<typename T>
T SinglyLinkedList<T>::access(size_t index) const
{
    Node<T> * current = m_head;
    size_t i = 0;
    while(i<index)
    {
        current = current->next;
        i++;
    }
    return current->value;
}

template<typename T>
void SinglyLinkedList<T>::print_list() const 
{
    Node<T> * current = m_head;
    while(current->next)
    {
        std::cout<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
        current = current->next;
    }
    std::cout<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
}

template<typename T>
void SinglyLinkedList<T>::print_values() const
{
    for(size_t i = 0; i < this->length(); i++)
    {
        std::cout<<"["<<i<<"] = " << this->access(i) << "\n";
    }
}

template<typename T>
size_t SinglyLinkedList<T>::length() const{
    return m_listLength;
}

#endif 