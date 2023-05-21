#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <memory>
#include "../Linked List/Doubly Linked List/DoublyLinkedList.hpp"

template<typename T>
class Queue{

    public:
    Queue() noexcept;
    Queue(T value) noexcept;
    Queue(std::initializer_list<T> values) noexcept;
    Queue(const Queue& other) noexcept;
    Queue(Queue&& other) noexcept;

    Queue& operator=(const Queue& other) noexcept;
    Queue& operator=(Queue&& other) noexcept;
    bool operator==(const Queue& other) noexcept;
    template<typename U> 
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& other);

    void enqueue(T value);
    void dequeue();
    T front() const;
    T back() const;
    bool isEmpty() const;
    size_t size() const;

    private:
    std::unique_ptr<DoublyLinkedList<T>> m_queue; //unique_ptr 'owns' a singly linked list object
    size_t m_queueSize = 0;
};

template<typename T>
Queue<T>::Queue() noexcept
{
    m_queue = std::make_unique<DoublyLinkedList<T>>();     
}

template<typename T>
Queue<T>::Queue(T value) noexcept
{
    std::cout<<"Constructor Called: value="<<value<<"\n";

    m_queue = std::make_unique<DoublyLinkedList<T>>(value); 
    m_queueSize++;
}

template<typename T>
Queue<T>::Queue(std::initializer_list<T> values) noexcept
{
    m_queue = std::make_unique<DoublyLinkedList<T>>(values);
    m_queueSize = values.size();
}
template<typename T>
Queue<T>::Queue(const Queue& other) noexcept
{
    m_queue = std::make_unique<DoublyLinkedList<T>>(*(other.m_queue.get()));
    m_queueSize = other.m_queueSize;
}
template<typename T>
Queue<T>::Queue(Queue&& other) noexcept
{
    m_queue = std::move(other.m_queue);
    m_queueSize = other.m_queueSize;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }
    *(m_queue.get()) = *(other.m_queue.get()); //anyway to do this without accessing the raw pointers?
    m_queueSize = other.m_queueSize;
    return *this;
} 
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept 
{
    if(this == &other)
    {
        return *this;
    }
    m_queue = std::move(other.m_queue);
    m_queueSize = other.m_queueSize;
    return *this;
} 
template<typename T>
bool Queue<T>::operator==(const Queue& other) noexcept
{
    return *(m_queue.get()) == *(other.m_queue.get());
} 

template<typename T> 
std::ostream& operator<<(std::ostream& os, const Queue<T>& other) 
{
    std::cout<<"=FONRT=\n";
    for(size_t i = 0 ; i<other.m_queueSize; i++)
    {
        os << other.m_queue->access_from_start(i) << "\n";
    }
    std::cout<<"=BACK=\n";
    return os;
}

template<typename T>
void Queue<T>::enqueue(T value)
{
    m_queue->add_to_end(value);
    m_queueSize++;
}
template<typename T>
void Queue<T>::dequeue()
{
    m_queue->delete_start();
    m_queueSize--;
}
template<typename T>
T Queue<T>::front() const
{
    return m_queue->first_value();
}
template<typename T>
T Queue<T>::back() const
{
    return m_queue->last_value();
}
template<typename T>
bool Queue<T>::isEmpty() const
{
    return m_queueSize == 0;
} 
template<typename T>
size_t Queue<T>::size() const
{
    return m_queueSize;
}

#endif 