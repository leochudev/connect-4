#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include "Stack.h"

template<typename T>
class Node
{
    public:
        Node(T v)
        {
            value = v;
            previous = 0;
        }
        ~Node()
        {
            delete previous;
        }
        Node<T>* previous;
        T value;
    protected:
    private:
};

template<typename T>
class LinkedListStack : public Stack<T>
{
    public:
        ~LinkedListStack()
        {
            delete last;
        }
        void push(T value)
        {
            Node<T>* node = new Node<T>(value);
            node->previous = last;
            last = node;
            ++Stack<T>::count;
        }
        T pop()
        {
            Node<T>* node = last;
            last = last->previous;
            node->previous = 0;
            T value = node->value;
            delete node;
            --Stack<T>::count;
            return value;
        }

        T top()
        {
            return last->value;
        }
    protected:
    private:
        Node<T>* last;
};

#endif // LINKEDLISTSTACK_H
