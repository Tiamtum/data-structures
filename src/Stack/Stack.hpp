#ifndef STACK_HPP
#define STACK_HPP

#include <memory>
#include "../Linked List/Singly Linked List/SinglyLinkedList.hpp"

template<typename T>
class Stack{

    public:
    Stack(T value) noexcept;
    Stack(std::initializer_list<T> values) noexcept;
    Stack(const Stack& other) noexcept;
    Stack(Stack&& other) noexcept;

    Stack& operator=(const Stack& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;
    bool operator==(const Stack& other) noexcept;
    template<typename U> 
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& other);

    void push(T value);
    void pop();
    T peek() const;
    bool isEmpty() const;
    size_t size() const;

    private:
    std::unique_ptr<SinglyLinkedList<T>> m_stack; //unique_ptr 'owns' a singly linked list object
    size_t m_stackSize = 0;
};

template<typename T>
Stack<T>::Stack(T value) noexcept
{
    std::cout<<"Constructor Called: value="<<value<<"\n";

    m_stack = std::make_unique<SinglyLinkedList<T>>(value); 
    m_stackSize++;
}

template<typename T>
Stack<T>::Stack(std::initializer_list<T> values) noexcept
{
    m_stack = std::make_unique<SinglyLinkedList<T>>(values);
    m_stackSize = values.size();
}
template<typename T>
Stack<T>::Stack(const Stack& other) noexcept
{
    m_stack = std::make_unique<SinglyLinkedList<T>>(*(other.m_stack.get()));
    m_stackSize = other.m_stackSize;
}
template<typename T>
Stack<T>::Stack(Stack&& other) noexcept
{
    m_stack = std::move(other.m_stack);
    m_stackSize = other.m_stackSize;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }
    *(m_stack.get()) = *(other.m_stack.get()); //anyway to do this without accessing the raw pointers?
    m_stackSize = other.m_stackSize;
    return *this;
} 
template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept 
{
    if(this == &other)
    {
        return *this;
    }
    m_stack = std::move(other.m_stack);
    m_stackSize = other.m_stackSize;
    return *this;
} 
template<typename T>
bool Stack<T>::operator==(const Stack& other) noexcept
{
    return *(m_stack.get()) == *(other.m_stack.get());
} 

template<typename T> 
std::ostream& operator<<(std::ostream& os, const Stack<T>& other) 
{
    std::cout<<"=TOP=\n";
    for(size_t i = 0 ; i<other.m_stackSize; i++)
    {
        os << other.m_stack->access(i) << "\n";
    }
    std::cout<<"=BOTTOM=\n";
    return os;
}

template<typename T>
void Stack<T>::push(T value)
{
    m_stack->add_to_start(value);
    m_stackSize++;
}
template<typename T>
void Stack<T>::pop()
{
    m_stack->delete_start();
    m_stackSize--;
}
template<typename T>
T Stack<T>::peek() const
{
    return m_stack->first_value();
}
template<typename T>
bool Stack<T>::isEmpty() const
{
    return m_stackSize == 0;
} 
template<typename T>
size_t Stack<T>::size() const
{
    return m_stackSize;
}

#endif 