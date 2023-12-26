// STACK implementation with Linked List
#include <stdio.h>
#include "./include/stack.hpp"

namespace octo_data
{
    template <typename T>
    StackNode<T> *newNode(T data)
    {
        StackNode<T> *node = new StackNode<T>();
        node->data = data;
        node->next = NULL;
        return node;
    }

    template <typename T>
    void push(StackNode<T> **top, T data)
    {
        StackNode<T> *newElem = newNode<T>(data);
        newElem->next = *top;
        *top = newElem;
    }

    template <typename T>
    T pop(StackNode<T> **top)
    {
        T data = (*top)->data;
        StackNode<T> *formerTopNext = (*top)->next;
        delete *top;
        *top = formerTopNext;
        return data;
    }

    template <typename T>
    bool isEmpty(StackNode<T> *top)
    {
        return top == NULL;
    }
}