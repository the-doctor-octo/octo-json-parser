#pragma once
// STACK implementation with Linked List
#include <stdio.h>

namespace octo_data
{
    template <typename T>
    class StackNode
    {
    public:
        StackNode<T>(){};
        T data;
        StackNode<T> *next;
    };

    template <typename T>
    StackNode<T> *newNode(T data);

    template <typename T>
    void push(StackNode<T> **top, T data);

    template <typename T>
    T pop(StackNode<T> **top);

    template <typename T>
    bool isEmpty(StackNode<T> *top);
}