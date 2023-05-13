#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.hpp"
//Rule of three: If a class requires a user-defined destructor, a user-defined 
//copy constructor, or a user-defined copy assignment operator, it almost certainly
//requires all three. 

template <typename T>
class SinglyLinkedList
{
    public:
    SinglyLinkedList() = delete;   
    explicit SinglyLinkedList(T value) noexcept;      
    SinglyLinkedList(const SinglyLinkedList& list) noexcept;        //copy constructor (initialize a previously uninitialized list from some other list's data. )
    SinglyLinkedList& operator=(const SinglyLinkedList& list);      //copy assignment (replace the data of a previously initialized list with some other list's data. )
    SinglyLinkedList(SinglyLinkedList&& list) noexcept;             //move constructor
    SinglyLinkedList& operator=(SinglyLinkedList&& list) noexcept;  //move assignment
    ~SinglyLinkedList();                                            //destructor

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

//Constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T value) noexcept
{
    m_head = new Node<T>;
    m_head->value = value;
    m_head->next = nullptr;
    m_listLength++;
    std::cout<<"list created: " << m_head << "\n";
}
//Copy Constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& list) noexcept 
:m_listLength(list.m_listLength)
{
    m_head = new Node<T>;         //copying list.m_head directly wont work since when one list object falls out of scope, the other(s) copy(s)
                                  //will not be able to destruct properly. hence new nodes must be created for each old node so
                                  //they are in different memory locations

    const Node<T> * originalCurrent = list.m_head; //const so cant change data. 'Node<T> * const originalCurrent' would not allow to change pointer
    
    m_head->value = originalCurrent->value; 
    m_head->next = nullptr;

    originalCurrent = originalCurrent->next; //step one ahead in original

    Node<T> * temp=nullptr;
    Node<T> * current = m_head;

    while(originalCurrent->next)
    {
        Node<T> * tail = new Node<T>;
        if(!(m_head->next)) //first node case
        {
            m_head->next = tail;
            tail->next = nullptr;
        }
        if(temp) //temp is set such that it is a pointer to the previous iterations node
        {
            temp->next = tail;
            temp = tail;
            tail->value = originalCurrent->value;
            tail->next = nullptr;
            originalCurrent=originalCurrent->next;            
        }
        else //initial tail case (length = 2)
        {
        tail->value = originalCurrent->value;
        temp = tail;
        originalCurrent=originalCurrent->next;            
        }
    }
    Node<T> * end = new Node<T>;
    temp->next = end;
    end->next = nullptr;
    end->value = originalCurrent->value;
}
//Copy assignment operator
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& list)
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
        Node<T> * temp = nullptr;

        while(otherList->next) //walk larger list from where it left off, allocate new nodes and fill with values from it
        {
            if(!temp)
            {
                Node<T> * newTail = new Node<T>;    //create a new node
                temp = newTail;                     //point to it
                thisList->next = newTail;           //link where we left off to the start of the new nodes
                newTail->value = otherList->value;  //populate the new node
                newTail->next = nullptr;
                otherList = otherList->next;        //increment to next node in other list
            }
            else
            {
                Node<T> * newTail = new Node<T>;    //create a new node
                temp->next = newTail;               //link the previous iterations node to it
                temp = newTail;                     //set temp to poiint to the new node for next iteration
                newTail->value = otherList->value;  //populate node
                newTail->next = nullptr;
                otherList = otherList->next;        //increment to next node in other list
            }  
        }

        Node<T> * end = new Node<T>;                //create final node
        temp->next = end;                           //link node from final iteration to it
        end->value = otherList->value;              //populate node
        end->next = nullptr;
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
        exit(EXIT_FAILURE);
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

    // list.m_listLength = 0;
    // list.m_head = nullptr;
    // return *this;
}

//Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{   
    std::cout<<"===destructor called===\n";
    Node<T> * current = m_head;
    if(!current)    //if list is initialized by move constructor, the moved-from list's m_head points to nullptr and has to be dealt with on its own
    {
        std::cout<<"current=nullptr\n";
        delete current;
    }
    else
    {
        while(current->next)
        {
            Node<T> * temp = current;
            std::cout<<"to be deleted: " << temp->value << ", " << temp->next << "\n";
            current = current->next;
            delete temp;
        }
        std::cout<<"to be deleted: " << current->value << ", " << current->next << "\n";

        delete current;        
    }
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