#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include "Node.hpp"
//REFACTOR: See what you did in SinglyCicularLinkedList.hpp

template <typename T>
class SinglyLinkedList
{
    public:
    SinglyLinkedList() = delete; //handle empty case at some point
    explicit SinglyLinkedList(T value) noexcept;
    explicit SinglyLinkedList(std::initializer_list<T> values) noexcept;      
    SinglyLinkedList(const SinglyLinkedList& other) noexcept;            //copy constructor (initialize a previously uninitialized list from some other list's data. )
    SinglyLinkedList& operator=(const SinglyLinkedList& other) noexcept; //copy assignment (replace the data of a previously initialized list with some other list's data. )
    SinglyLinkedList(SinglyLinkedList&& other) noexcept;                 //move constructor
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;      //move assignment
    ~SinglyLinkedList();                                                //destructor

    bool operator==(const SinglyLinkedList& other) noexcept;

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
    void print_values() const;
    T first_value() const;
    T last_value() const;
    size_t length() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<U>& other);

    private:
    Node<T> * walk_list_to_end(Node<T> * current) const;
    Node<T> * walk_list_between_indices(Node<T> * current, size_t& start, size_t end) const;
    size_t m_listLength = 0;
    Node<T> * m_head;
};

template<typename T>
Node<T> * SinglyLinkedList<T>::walk_list_to_end(Node<T> * current) const
{
    while(current->next)
    {
        current = current->next;
    }
    return current;
}
template<typename T>
Node<T> * SinglyLinkedList<T>::walk_list_between_indices(Node<T> * current, size_t& start, size_t end) const
{
    while(start<end)
    {
        current=current->next;
        start++;
    }
    return current;
}


//Constructor - Single value
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T value) noexcept
{
    m_head = new Node<T>;
    m_head->value = value;
    m_head->next = nullptr;
    m_listLength++;
}
//Constructor - Initializer list of values
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> values) noexcept
{
    for(auto& value: values)
    {
        if(m_listLength==0)
        {
            m_head = new Node<T>;
            m_head->value = value;
            m_head->next = nullptr;
            m_listLength++;
        }                
        else
        {
            add_to_end(value);
        }
    }
}
//Copy Constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other) noexcept 
:m_listLength(other.m_listLength)
{
    Node<T> * originalCurrent = other.m_head;
    
    m_head = new Node<T>;
    m_head->value = originalCurrent->value;
    m_head->next = nullptr;

    originalCurrent = originalCurrent->next;
    
    while(originalCurrent->next)
    {
        add_to_end(originalCurrent->value);
        originalCurrent=originalCurrent->next;
    }
    add_to_end(originalCurrent->value);
}
//Copy assignment operator
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& list) noexcept
{
    if(this == &list) //assigning to itself 
    {
        return *this;
    }

    Node<T> * thisList = this->m_head;
    const Node<T> * otherList = list.m_head;

    if(this->length() == list.length()) //lists are equal in length, no new allocations required just replace the values
    {
        while(thisList->next)
        {
            thisList->value = otherList->value;
            thisList = thisList->next;
            otherList = otherList->next;
        }

        thisList->value = otherList->value;
        return *this;
    }
    else if(this->length() < list.length()) //list is smaller than what we want to assign, replace values and allocate nodes
    {
        while(thisList->next) //walk smaller list to it's end, replace values
        {
            thisList->value = otherList->value;
            otherList = otherList->next;
            thisList = thisList->next;
        }

        thisList->value = otherList->value;
        otherList = otherList->next;
        while(otherList->next)
        {
            add_to_end(otherList->value);
            otherList = otherList->next;
        }
        add_to_end(otherList->value);
        return *this;
    }
    else if(this->length() > list.length()) //list is greater than what we want to assign, replace values and deallocate nodes
    {
        while(otherList->next)                  //walk the smaller list and replace larger list values with its values
        {
            thisList->value = otherList->value;
            otherList = otherList->next;
            thisList = thisList->next;
        }

        thisList->value = otherList->value;
        Node<T> * leftOverNode = thisList->next;
        thisList->next = nullptr;
        
        while(leftOverNode->next)               //walk the remainder of the larger list and deallocate the leftover nodes
        {
            Node<T> * temp = leftOverNode;
            leftOverNode = leftOverNode->next;
            delete temp;
        }

        delete leftOverNode;
        return *this;
    }
    else
    {
        std::cout<<"Error in operator=\n";
        return *this=nullptr; //not sure about this
    }
}
//Move constructor
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& list) noexcept
 :m_head(list.m_head),m_listLength(list.m_listLength)   //'rewire' m_head to point to list.m_head location
{
    list.m_head= nullptr;
    list.m_listLength = 0;   
} 
//Move assignment operator               
template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& list) noexcept
{
    if(this == &list) //moving in to itself 
    {
        return *this;
    }
    
    //Delete current data to prepare to move to new data
    Node<T> * current = m_head;
    while(current->next)
    {
        Node<T> * temp = current;
        current=current->next;
        delete temp;
    } 
    delete current;
    
    m_head = list.m_head;
    m_listLength = list.m_listLength;
    list.m_head= nullptr;
    list.m_listLength = 0;  
    return *this;
}
//Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{   
    Node<T> * current = m_head;
    if(!current)    //if list is initialized by move constructor, the moved-from list's m_head points to nullptr and has to be dealt with on its own
    {
        delete current;
    }
    else
    {
        while(current->next)
        {
            Node<T> * temp = current;
            current = current->next;
            delete temp;
        }
        delete current;        
    }
}

template<typename T>
bool SinglyLinkedList<T>::operator==(const SinglyLinkedList& other) noexcept
{
    Node<T> * current = m_head;
    Node<T> * otherCurrent = other.m_head;
    while(current->next)
    {
        if(current->value == otherCurrent->value)
        {
            current=current->next;
            otherCurrent=otherCurrent->next;
        }
        else
        {
            return false;
        }
    }
    return true;
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
        current = walk_list_to_end(current);
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
        add_to_start(value);
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
        std::cout<<"Out of bounds index for insert().\n" 
            <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
            <<"insert() was given index: index="<<index<<"\n";
    }
}

template <typename T>
void SinglyLinkedList<T>::delete_end()
{
    if(m_listLength == 1)
    {
        std::cout<<"delete_end() Error: List consists of a single node.\n";
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
        std::cout<<"delete_start() Error: List consists of a single node.\n";
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
        std::cout<<"delete_at() Error: List consists of a single node.\n";
    }
    else if(index == 0)
    {
        delete_start();
    }
    else if(index == m_listLength-1)
    {
        delete_end();
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
        std::cout<<"Out of bounds index for delete_at().\n" 
                 <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                 <<"delete_at() was given index: index="<<index<<"\n";      
    }
}

template<typename T>
void SinglyLinkedList<T>::replace_value(size_t index, T value)
{
    if(index<0 || index>=m_listLength)
    {
        std::cout<<"Out of bounds index for replace_value().\n" 
                 <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                 <<"replace_value() was given index: index="<<index<<"\n";
    }
    else
    {
        size_t i = 0 ;
        Node<T> * current = m_head;
        current = walk_list_between_indices(current,i,index);
        current->value = value;
    }
}

template<typename T>
void SinglyLinkedList<T>::swap_values(size_t index1, size_t index2)
{
    if(index1<0 || index2<0 || index1>=m_listLength || index2>=m_listLength)
    {
        std::cout<<"Out of bounds index for swap_values().\n" 
                 <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                 <<"swap_values() was given indices: index1="<<index1<<", index2="<<index2<<"\n";
    }
    else
    {
        if(index1>index2)
        {
            std::swap(index1,index2); //why not just do this for the values?
        }

        Node<T> * current = m_head;
        size_t i = 0;

        current = walk_list_between_indices(current,i,index1);

        Node<T> * index1Node = current;
        T value1 = current->value;

        current = walk_list_between_indices(current,i,index2);

        index1Node->value = current->value;
        current->value = value1;
    }
}

template<typename T>
void SinglyLinkedList<T>::sort() requires std::is_arithmetic<T>::value
{
    //Insertion sort
    size_t i = 2;
    while(i < m_listLength+1)
    {
        size_t j = i-1;
        while(j>0 && access(j-1)>access(j))
        {
            swap_values(j-1,j);
            j--;
        }
        i++;
    }

}

template<typename T>
T SinglyLinkedList<T>::access(size_t index) const
{
    Node<T> * current = m_head;
    size_t i = 0;
    current = walk_list_between_indices(current,i,index);
    return current->value;
}

template<typename T>
void SinglyLinkedList<T>::print_values() const
{
    for(size_t i = 0; i < length(); i++)
    {
        std::cout<<"["<<i<<"] = " << access(i) << "\n";
    }
}

template<typename T>
T SinglyLinkedList<T>::first_value() const
{
    return m_head->value;
}

template<typename T>
T SinglyLinkedList<T>::last_value() const
{
    Node<T> * current = m_head;
    current = walk_list_to_end(current);
    return current->value;
}

template<typename T>
size_t SinglyLinkedList<T>::length() const{
    return m_listLength;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& other)
{
    Node<T> * current = other.m_head;
    while(current->next)
    {
        os<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
        current = current->next;
    }
    os<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
    return os;
}

#endif 