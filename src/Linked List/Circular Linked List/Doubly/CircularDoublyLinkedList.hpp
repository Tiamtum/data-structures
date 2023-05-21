#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H

#include <iostream>
#include <iomanip>
#include "Node.hpp"

template<typename T>
class CircularDoublyLinkedList
{
    public:
    CircularDoublyLinkedList() noexcept; //handle empty case at some point
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
    T access_from_start(int index) const;
    T access_from_end(int index) const;  
    Node<T> * get_address(size_t index) const;
    Node<T> * get_next_address(size_t index) const;
    Node<T> * get_previous_address(size_t index) const;
    void print_values() const;  
    T first_value() const;  
    T last_value() const;   
    size_t length() const;  
    bool isEmpty() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const CircularDoublyLinkedList<U>& other); 

    private:
    Node<T> * walk_list_to_end(Node<T> * current) const;    
    Node<T> * walk_list_fowards_between_indices(Node<T> * current, size_t& start, size_t end) const;  
    Node<T> * walk_list_to_start(Node<T> * current) const;    
    Node<T> * walk_list_backwards_between_indices(Node<T> * current, int& start, int end) const;  

    size_t m_listLength = 0;
    Node<T> * m_head;
    Node<T> * m_tail;
};

template<typename T>
Node<T> * CircularDoublyLinkedList<T>::walk_list_to_end(Node<T> * current) const
{
    while(current->next != m_head)
    {
        current = current->next;
    }
    return current;
}

template<typename T>
Node<T> * CircularDoublyLinkedList<T>::walk_list_fowards_between_indices(Node<T> * current, size_t& start, size_t end) const
{
    while(start<end)
    {
        current=current->next;
        start++;
    }
    return current;
}

template<typename T>
Node<T> * CircularDoublyLinkedList<T>::walk_list_to_start(Node<T> * current) const
{
    while(current->previous != m_head)
    {
        current = current->previous;
    }
    return current;
}
template<typename T>
Node<T> * CircularDoublyLinkedList<T>::walk_list_backwards_between_indices(Node<T> * current, int& start, int end) const
{
    while(start>end)
    {
        current=current->previous;
        start--;
    }
    return current;
}

template<typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList() noexcept
{
    m_head = new Node<T>;
    m_listLength=0;
}
//Constructor - Single value
template <typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(T value) noexcept
{
    m_head = new Node<T>;
    m_tail = m_head;
    m_head->value = value;
    m_head->next = m_head;
    m_head->previous = m_head;
    m_listLength++;
}
//Constructor - Initializer list
template<typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(std::initializer_list<T> values) noexcept
{
    for(const auto& value: values)
    {
        if(m_listLength==0)
        {
            m_head = new Node<T>;
            m_tail = m_head;
            m_head->value = value;
            m_head->next = m_head;
            m_head->previous = m_head;
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
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(const CircularDoublyLinkedList& other) noexcept
:m_listLength(other.m_listLength)
{
    if(other.isEmpty())
    {
        m_head = new Node<T>;
    }
    else
    {
        Node<T> * originalCurrent = other.m_head;
        
        m_head = new Node<T>;
        m_head->value = originalCurrent->value;
        m_head->next = m_head;
        m_head->previous = m_head;

        originalCurrent = originalCurrent->next;
        
        while(originalCurrent->next != other.m_head)
        {
            add_to_end(originalCurrent->value);
            originalCurrent=originalCurrent->next;
        }
        add_to_end(originalCurrent->value);
    }
}          
//Copy Assignment Operator
template<typename T>
CircularDoublyLinkedList<T>& CircularDoublyLinkedList<T>::operator=(const CircularDoublyLinkedList& other) noexcept
{
    if(this == &other || (this->isEmpty() && other.isEmpty()))
    {
        return *this;
    }

    Node<T> * thisList = this->m_head;
    const Node<T> * otherList = other.m_head;

    if(this->length() == other.length()) //lists are equal in length, no new allocations required just replace the values
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
    else if(this->length() < other.length()) //list is smaller than what we want to assign, replace values and allocate nodes
    {
        if(this->isEmpty())
        {
            while(otherList->next != other.m_head)
            {
                this->add_to_end(otherList->value);
                otherList = otherList->next;
            }
            this->add_to_end(otherList->value);
            return *this;
        }
        
        while(thisList->next != m_head) //walk smaller list to it's end, replace values
        {
            thisList->value = otherList->value;
            otherList = otherList->next;
            thisList = thisList->next;
        }

        thisList->value = otherList->value;
        otherList = otherList->next;
        while(otherList->next != other.m_head)
        {
            add_to_end(otherList->value);
            otherList = otherList->next;
        }
        add_to_end(otherList->value);
        return *this;
    }
    else //(this->length() > list.length()) //list is greater than what we want to assign, replace values and deallocate nodes
    {
        if(other.isEmpty())
        {
            for(size_t i=0; i<m_listLength; i++)
            {
                this->delete_end();
            }
            m_listLength = 0;
            return *this;
        }
        while(otherList->next != other.m_head)                  //walk the smaller list and replace larger list values with its values
        {
            thisList->value = otherList->value;
            otherList = otherList->next;
            thisList = thisList->next;
        }

        thisList->value = otherList->value;
        Node<T> * leftOverNode = thisList->next;
        thisList->next = m_head;
        
        while(leftOverNode->next != m_head)               //walk the remainder of the larger list and deallocate the leftover nodes
        {
            Node<T> * temp = leftOverNode;
            leftOverNode = leftOverNode->next;
            delete temp;
        }

        delete leftOverNode;
        return *this;
    }
} 
//Move Constructor
template<typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(CircularDoublyLinkedList&& other) noexcept
:m_head(other.m_head),m_tail(other.m_tail),m_listLength(other.m_listLength)
{
    other.m_head= nullptr;
    other.m_tail= nullptr;
    other.m_listLength = 0;   
}
//Move Assignment Operator
template<typename T>
CircularDoublyLinkedList<T>& CircularDoublyLinkedList<T>::operator=(CircularDoublyLinkedList&& other) noexcept
{
   if(this == &other) //moving in to itself 
    {
        return *this;
    }
    
    //Delete current data to prepare to move to new data
    Node<T> * current = m_head;
    while(current->next != m_head)
    {
        Node<T> * temp = current;
        current=current->next;
        delete temp;
    } 
    delete current;
    
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_listLength = other.m_listLength;
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_listLength = 0;  
    return *this;
}
//Destructor
template <typename T>
CircularDoublyLinkedList<T>::~CircularDoublyLinkedList()
{   
    if(isEmpty())
    {
        delete m_head;
    }
    else
    {
        Node<T> * current = m_head;
        if(!current)    //if list is initialized by move constructor, the moved-from list's m_head points to nullptr and has to be dealt with on its own
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
}

template<typename T>
bool CircularDoublyLinkedList<T>::operator==(const CircularDoublyLinkedList& other) noexcept
{
    if(isEmpty() && other.isEmpty())
    {
        return true;
    }
    Node<T> * current = m_head;
    Node<T> * otherCurrent = other.m_head;
    while(current->next != m_head)
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
template<typename T>
void CircularDoublyLinkedList<T>::add_to_end(T value)
{
    if(isEmpty())
    {
        m_tail = m_head;
        m_head->value = value;
        m_head->next = m_head;
        m_head->previous = m_head;
        m_listLength++;
    }
    else if(m_head->next == m_head)
    {
        m_tail = new Node<T>;
        m_head->next = m_tail;
        m_head->previous = m_tail;

        m_tail->value = value;
        m_tail->next = m_head;
        m_tail->previous = m_head;
        
        m_listLength++;
    }
    else
    {
        Node<T> * newTail = new Node<T>;
        newTail->value = value;
        newTail->next = m_head;
        newTail->previous = m_tail;
        m_tail->next = newTail;
        m_tail = newTail;
        m_head->previous = newTail;
        m_listLength++;        
    }    
}

template<typename T>
void CircularDoublyLinkedList<T>::add_to_start(T value)
{
    if(!isEmpty())
    {      
        if(m_head->next == m_head)
        {
            Node<T> * newHead = new Node<T>;
            newHead->value = value;
            newHead->next = m_head;
            newHead->previous = m_head;
            m_head->next = newHead;
            m_head->previous = newHead;
            m_tail = m_head;
            m_head = newHead;
            m_listLength++;
        }
        else
        {
            Node<T> * newHead = new Node<T>;
            newHead->value = value;
            newHead->next = m_head;
            newHead->previous = m_tail;
            m_head->previous = newHead;
            m_tail->next = newHead;
            m_head = newHead;
            m_listLength++;
        }
    }
    else
    {
        m_tail = m_head;
        m_head->value = value;
        m_head->next = m_head;
        m_head->previous = m_head;
        m_listLength++;        
    }
}

template<typename T>
void CircularDoublyLinkedList<T>::insert(T value, size_t index)
{
    if(isEmpty())
    {
        m_head->value = value;
        m_head->next = m_head;
        m_head->previous = m_head;
        m_listLength++;
    }
    else if(index == 0)
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
                current->next->previous = newNode;
                newNode->next = current->next;
                current->next = newNode;
                newNode->previous = current;
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
void CircularDoublyLinkedList<T>::delete_end()
{
    if(m_listLength == 1)
    {
        // std::cout<<"delete_end() Error: List consists of a single node.\n";
        m_listLength = 0;
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
                m_tail = current;
                current->next = m_head;
                break;
            }
            i++;
            current = current->next;
        }
    }
}

template <typename T>
void CircularDoublyLinkedList<T>::delete_start()
{
    if(m_listLength == 1)
    {
        // std::cout<<"delete_start() Error: List consists of a single node.\n";
        m_listLength = 0;
    }
    else
    {
        Node<T> * temp = m_head;
        m_head = temp->next;
        m_head->previous=m_tail;
        m_tail->next = m_head;
        delete temp;
        m_listLength--;
    }
}

template <typename T>
void CircularDoublyLinkedList<T>::delete_at(size_t index)
{   
    if(m_listLength == 1)
    {
        // std::cout<<"delete_at() Error: List consists of a single node.\n";
        m_listLength = 0;
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
                temp->next->previous = current;
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
void CircularDoublyLinkedList<T>::replace_value(size_t index,T value)
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
        current = walk_list_fowards_between_indices(current,i,index);
        current->value = value;
    }
}

template<typename T>
void CircularDoublyLinkedList<T>::swap_values(size_t index1, size_t index2)
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

        current = walk_list_fowards_between_indices(current,i,index1);

        Node<T> * index1Node = current;
        T value1 = current->value;

        current = walk_list_fowards_between_indices(current,i,index2);

        index1Node->value = current->value;
        current->value = value1;
    }
}

template<typename T>
void CircularDoublyLinkedList<T>::sort() requires std::is_arithmetic<T>::value
{
    //Insertion sort
    size_t i = 2;
    while(i < m_listLength+1)
    {
        size_t j = i-1;
        while(j>0 && access_from_start(j-1)>access_from_start(j))
        {
            swap_values(j-1,j);
            j--;
        }
        i++;
    }
} 

template<typename T>
T CircularDoublyLinkedList<T>::access_from_start(int index) const
{
    if(isEmpty())
    {
        std::cout<<"access() Error - Trying to access an empty list.\n";
    }
    Node<T> * current = m_head;
    size_t i = 0;
    auto adjustIndex = [](int ind, int len){
        if(ind>=0)
        {
            return ind % len;
        }
        else
        {
            return ((ind % len)+len);
        }
    };
    index = adjustIndex(index,m_listLength);    
    current = walk_list_fowards_between_indices(current,i,index);
    return current->value;
}

template<typename T>
T CircularDoublyLinkedList<T>::access_from_end(int index) const
{
    if(isEmpty())
    {
        std::cout<<"access() Error - Trying to access an empty list.\n";
    }  
    Node<T> * current = m_tail;
    int i = m_listLength-1;
    auto adjustIndex = [](int ind, int len){
        if(ind>=0)
        {
            return ind % len;
        }
        else
        {
            return ((ind % len)+len);
        }
    };
    index = adjustIndex(index,m_listLength);    
    current = walk_list_backwards_between_indices(current,i,index);
    return current->value;
}

template<typename T>
Node<T> * CircularDoublyLinkedList<T>::get_address(size_t index) const
{
    if(index<0 || index>=m_listLength)
    {
        std::cout<<"Out of bounds index for get_address().\n" 
                <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                <<"get_address() was given indices: index="<<index<<"\n";
    }   
    Node<T> * current = m_head;
    size_t i = 0;
    current = walk_list_fowards_between_indices(current,i,index);
    return current;
}

template<typename T>
Node<T> * CircularDoublyLinkedList<T>::get_next_address(size_t index) const
{
    if(index<0 || index>=m_listLength)
    {
        std::cout<<"Out of bounds index for get_next_address().\n" 
                <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                <<"get_next_address() was given indices: index="<<index<<"\n";
    }       
    Node<T> * current = m_head;
    size_t i = 0;
    current = walk_list_fowards_between_indices(current,i,index);
    return current->next;
}

template<typename T>
Node<T> * CircularDoublyLinkedList<T>::get_previous_address(size_t index) const
{
    if(index<0 || index>=m_listLength)
    {
        std::cout<<"Out of bounds index for get_previous_address().\n" 
                <<"Minimum allowed index = 0, Maximum allowed index = "<<m_listLength-1<<".\n"
                <<"get_previous_address() was given indices: index="<<index<<"\n";
    }     
    Node<T> * current = m_tail;
    size_t i = m_listLength-1;
    current = walk_list_backwards_between_indices(current,i,index);
    return current->previous;
}

template<typename T>
void CircularDoublyLinkedList<T>::print_values() const
{
    for(size_t i = 0; i < length(); i++)
    {
        std::cout<<"["<<i<<"] = " << access_from_start(i) << "\n";
    }
}  

template<typename T>
T CircularDoublyLinkedList<T>::first_value() const
{
    if(isEmpty())
    {
        std::cout<<"first_value() Error - Trying to return value from empty list.\n";
    }
    return m_head->value;
}  

template<typename T>
T CircularDoublyLinkedList<T>::last_value() const
{
    if(isEmpty())
    {
        std::cout<<"last_value() Error - Trying to return value from empty list.\n";
    }
    return m_tail->value;
}

template<typename T>
size_t CircularDoublyLinkedList<T>::length() const
{
    return m_listLength;
}

template<typename T>
bool CircularDoublyLinkedList<T>::isEmpty() const
{
    return m_listLength == 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CircularDoublyLinkedList<T>& other)
{
    Node<T> * current = other.m_head;
    while(current->next != other.m_head)
    {
        if(!(current->previous))
        {
            os<<"Previous: " << current->previous << std::setw(24) << " Location: " << current << " Next: " << current->next << " Value: " << current->value <<"\n";             
        }
        else
        {
            os<<"Previous: " << current->previous << " Location: " << current << " Next: " << current->next << " Value: " << current->value <<"\n"; 
        }
        current = current->next;
    }
        os<<"Previous: " << current->previous << " Location: " << current << " Next: " << current->next  << " Value: " << current->value <<"\n"; 
    return os;
}


#endif