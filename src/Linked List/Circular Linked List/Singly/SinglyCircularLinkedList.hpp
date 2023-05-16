#ifndef SINGLYCIRCULARLINKEDLIST_H
#define SINGLYCIRCULARLINKEDLIST_H

#include<iostream>
#include "Node.hpp"

template<typename T>
class SinglyCircularLinkedList
{
    public:
    SinglyCircularLinkedList() = delete; 
    explicit SinglyCircularLinkedList(T value) noexcept; 
    explicit SinglyCircularLinkedList(std::initializer_list<T> values) noexcept;
    SinglyCircularLinkedList(const SinglyCircularLinkedList& other) noexcept;           
    SinglyCircularLinkedList& operator=(const SinglyCircularLinkedList& other) noexcept; 
    SinglyCircularLinkedList(SinglyCircularLinkedList&& other) noexcept;                
    SinglyCircularLinkedList& operator=(SinglyCircularLinkedList&& other) noexcept;     
    ~SinglyCircularLinkedList();                             

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
    friend std::ostream& operator<<(std::ostream& os, const SinglyCircularLinkedList<U>& other);

    private:
    Node<T> * walk_list_to_end(Node<T> * current) const;
    Node<T> * walk_list_between_indices(Node<T> * current, size_t& start, size_t end) const;
    size_t m_listLength = 0;
    Node<T> * m_head;
};

template<typename T>
Node<T> * SinglyCircularLinkedList<T>::walk_list_to_end(Node<T> * current) const
{
    while(current->next != m_head)
    {
        current = current->next;
    }
    return current;
}

template<typename T>
Node<T> * SinglyCircularLinkedList<T>::walk_list_between_indices(Node<T> * current, size_t& start, size_t end) const
{
    while(start<end)
    {
        current=current->next;
        start++;
    }
    return current;
}
//Constructor - Single value
template<typename T>
SinglyCircularLinkedList<T>::SinglyCircularLinkedList(T value) noexcept
{
    m_head = new Node<T>;
    m_head->value = value;
    m_head->next = m_head;
    m_listLength++;
}
//Constructor - Initializer list of values
template<typename T>
SinglyCircularLinkedList<T>::SinglyCircularLinkedList(std::initializer_list<T> values) noexcept
{
    for(auto& value: values)
    {
        if(m_listLength == 0)
        {
            m_head = new Node<T>;
            m_head->value = value;
            m_head->next = m_head;
            m_listLength++;
        }
        else
        {
            add_to_end(value);
        }
    }
}
//Copy Constructor
template<typename T>
SinglyCircularLinkedList<T>::SinglyCircularLinkedList(const SinglyCircularLinkedList& other) noexcept 
:m_listLength(other.m_listLength)
{
    Node<T> * originalCurrent = other.m_head;
    
    m_head = new Node<T>;
    m_head->value = originalCurrent->value;
    m_head->next = m_head;

    originalCurrent = originalCurrent->next;

    while(originalCurrent->next != other.m_head)
    {
        add_to_end(originalCurrent->value);
        originalCurrent=originalCurrent->next;
    }
    add_to_end(originalCurrent->value);
}
//Copy assignment operator
template<typename T>
SinglyCircularLinkedList<T>& SinglyCircularLinkedList<T>::operator=(const SinglyCircularLinkedList& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }

    Node<T> * thisList = m_head;
    Node<T> * otherList = other.m_head;

    if(length() == other.length()) //lists are equal in length, no new allocations required just replace the values
    {
        while(thisList->next != m_head)
        {
            thisList->value = otherList->value;
            thisList = thisList->next;
            otherList = otherList->next;
        }
        thisList->value = otherList->value;
        return *this;
    }
    else if(length() < other.length()) //list is smaller than what we want to assign, replace values and allocate nodes
    {
        while(thisList->next != m_head) //walk smaller list to it's end, replace values
        {
            thisList->value = otherList->value;
            thisList = thisList->next;
            otherList = otherList->next;
        }
        thisList->value = otherList->value;
        otherList = otherList->next;

        while(otherList->next != other.m_head) //walk larger list from where it left off, allocate new nodes and fill values from it
        {
            add_to_end(otherList->value);
            otherList = otherList->next;
        }
        add_to_end(otherList->value);
        return *this;
    }
    else if(length() > other.length()) //list is greater than what we want to assign, replace values and deallocate nodes
    {
        while(otherList->next != other.m_head) //walk the smaller list and replace larger list values with it's values
        {
            thisList->value = otherList->value;
            otherList = otherList->next;
            thisList = thisList->next;
        }
        thisList->value = otherList->value;
        Node<T> * leftOverNode = thisList->next;
        while(leftOverNode->next != m_head) //possible refactor with delete functions?
        {
            Node<T> * temp = leftOverNode;
            leftOverNode = leftOverNode->next;
            delete temp;
        }
        thisList->next = m_head;
        delete leftOverNode;
        return *this;
    }
    else
    {
        std::cout<<"Error in operator=\n";
        exit(EXIT_FAILURE);
    }

}
//Move constructor
template<typename T>
SinglyCircularLinkedList<T>::SinglyCircularLinkedList(SinglyCircularLinkedList&& other) noexcept
:m_head(other.m_head),m_listLength(other.m_listLength)
{
    other.m_head = nullptr;
    other.m_listLength = 0;
}
//Move assignment operator
template<typename T>
SinglyCircularLinkedList<T>& SinglyCircularLinkedList<T>::operator=(SinglyCircularLinkedList&& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }
    Node<T> * current = m_head;
    while(current->next != m_head)
    {
        Node<T> * temp = current;
        current = current->next;
        delete temp;
    }
    delete current;

    m_head = other.m_head;
    m_listLength = other.m_listLength;
    other.m_head = nullptr;
    other.m_listLength = 0;
    return *this;
}

//Destructor
template<typename T>
SinglyCircularLinkedList<T>::~SinglyCircularLinkedList()
{   
    Node<T> * current = m_head;
    if(!current)
    {
        delete current;
    }
    else
    {
        while(current->next != m_head)
        {
            Node<T> * temp = current;
            current = current->next;
            delete temp;
        }
        delete current;        
    }
}

template<typename T>
void SinglyCircularLinkedList<T>::add_to_end(T value)
{
    if(m_head->next == m_head)
    {
        Node<T> * tail = new Node<T>;
        m_head->next = tail;
        tail->value = value;
        tail->next = m_head;
        m_listLength++;
    }
    else
    {
        Node<T> * current = m_head;
        current = walk_list_to_end(current);
        Node<T> * newTail = new Node<T>;
        current->next = newTail;
        newTail->value = value;
        newTail->next = m_head;
        m_listLength++;
    }
}

template<typename T>
void SinglyCircularLinkedList<T>::add_to_start(T value)
{
    Node<T> * current = m_head;
    current = walk_list_to_end(current); //need to link last node to first, so walk to the end to grab a pointer to it
    Node<T> * newHead = new Node<T>;
    newHead->value = value;
    newHead->next = m_head;
    m_head = newHead;
    current->next = m_head;
    m_listLength++;
}

template<typename T>
void SinglyCircularLinkedList<T>::insert(T value, size_t index)
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
        size_t i = 0;
        while(i<index)
        {
            if(i == index-1)
            {
                newNode->next = current->next;
                current->next = newNode;
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
        exit(EXIT_FAILURE);        
    }
}//TODO

template<typename T>
void SinglyCircularLinkedList<T>::delete_end()
{
    if(m_listLength == 1)
    {
        std::cout<<"Error: List consists of a single node.\n";
        delete(m_head);
        exit(EXIT_FAILURE);        
    }
    else
    {
        Node<T> * current = m_head;
        size_t i = 0;
        while(current->next != m_head)
        {
            if(i == m_listLength-2)
            {
                delete(current->next);
                m_listLength--;
                current->next = m_head;
                break;
            }
            i++;
            current = current->next;
        }

    }
}//TODO

template<typename T>
void SinglyCircularLinkedList<T>::delete_start()
{
    if(m_listLength == 1)
    {
        std::cout<<"Error: List consists of a single node.\n";
        delete(m_head);
        exit(EXIT_FAILURE);      
    }
    else
    {
        Node<T> * current = m_head;
        current = walk_list_to_end(current);

        Node<T> * temp = m_head;
        m_head = temp->next;
        delete temp;
        m_listLength--;
        current->next = m_head;

    }
}//TODO

template<typename T>
void SinglyCircularLinkedList<T>::delete_at(size_t index)
{
    if(m_listLength == 1)
    {
        std::cout<<"Error: List consists of a single node.\n";
        delete m_head;
        exit(EXIT_FAILURE);
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
        while(current->next != m_head)
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
        exit(EXIT_FAILURE);        
    }    
}//TODO

template<typename T>
void SinglyCircularLinkedList<T>::replace_value(size_t index,T value)
{
    if(index<0 || index>=m_listLength)
    {
        std::cout<<"Out of bounds index for replace_value().\n";
        exit(EXIT_FAILURE);
    }
    size_t i = 0;
    Node<T> * current = m_head;
    current = walk_list_between_indices(current,i,index);
    current->value = value;
}

template<typename T>
void SinglyCircularLinkedList<T>::swap_values(size_t index1, size_t index2)
{
    if(index1<0 || index2<0 || index1>=m_listLength || index2>=m_listLength)
    {
        std::cout<<"Out of bounds index for swap_values().\n" 
                 <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                 <<"swap_values() was given indices: index1="<<index1<<", index2="<<index2<<"\n";
        exit(EXIT_FAILURE);
    }

    if(index1>index2)
    {
        std::swap(index1,index2);
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

template<typename T>
void SinglyCircularLinkedList<T>::sort() requires std::is_arithmetic<T>::value
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
T SinglyCircularLinkedList<T>::access(size_t index) const
{
    Node<T> * current = m_head;
    size_t i = 0;
    index = index % m_listLength; //mod length to leverage the circular nature of the list 
    current = walk_list_between_indices(current,i,index);
    return current->value;
}

template<typename T>
void SinglyCircularLinkedList<T>::print_values() const
{
    for(size_t i = 0; i < length(); i++)
    {
        std::cout<<"["<<i<<"] = " << access(i) << "\n";
    }    
}

template<typename T>
T SinglyCircularLinkedList<T>::first_value() const
{
    return m_head->value;   
}

template<typename T>
T SinglyCircularLinkedList<T>::last_value() const
{
    Node<T> * current = m_head;
    current = walk_list_to_end(current);
    return current->value;
}

template<typename T>
size_t SinglyCircularLinkedList<T>::length() const{
    return m_listLength;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const SinglyCircularLinkedList<T>& other)
{
    Node<T> * current = other.m_head;
    while(current->next != other.m_head)
    {
        os<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
        current = current->next;
    }
    os<<"Location: " << current << ", Value: " << current->value << ", Next: " << current->next << "\n";
    return os;
}

#endif

