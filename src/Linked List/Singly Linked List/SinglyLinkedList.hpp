#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "Node.hpp"

template <typename T>
class SinglyLinkedList
{
    public:
    SinglyLinkedList() = delete; //handle empty case at some point
    explicit SinglyLinkedList(T value) noexcept;
    explicit SinglyLinkedList(std::initializer_list<T> values) noexcept;      
    SinglyLinkedList(const SinglyLinkedList& list) noexcept;            //copy constructor (initialize a previously uninitialized list from some other list's data. )
    SinglyLinkedList& operator=(const SinglyLinkedList& list) noexcept; //copy assignment (replace the data of a previously initialized list with some other list's data. )
    SinglyLinkedList(SinglyLinkedList&& list) noexcept;                 //move constructor
    SinglyLinkedList& operator=(SinglyLinkedList&& list) noexcept;      //move assignment
    ~SinglyLinkedList();                                                //destructor

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
}
//Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{   
    // std::cout<<"===destructor called===\n";
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
            // std::cout<<"to be deleted: " << temp->value << ", " << temp->next << "\n";
            current = current->next;
            delete temp;
        }
        // std::cout<<"to be deleted: " << current->value << ", " << current->next << "\n";

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
        delete m_head;
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
        delete m_head;
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
void SinglyLinkedList<T>::replace_value(size_t index, T value)
{
    if(index<0 || index>=m_listLength)
    {
        std::cout<<"Out of bounds index for replace_value().\n";
        exit(EXIT_FAILURE);
    }
    size_t i = 0 ;
    Node<T> * current = m_head;
    current = walk_list_between_indices(current,i,index);
    current->value = value;
}

template<typename T>
void SinglyLinkedList<T>::swap_values(size_t index1, size_t index2)
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
    current = walk_list_to_end();
    return current->value;
}

template<typename T>
size_t SinglyLinkedList<T>::length() const{
    return m_listLength;
}

#endif 