#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node{
    T value;
    Node * next;
    Node * previous;
};

#endif