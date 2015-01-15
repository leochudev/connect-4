#ifndef STACK_H
#define STACK_H


template<typename T>
class Stack
{
    public:
        Stack()
        {
            count = 0;
        }
        int size()
        {
            return count;
        }
        virtual void push(T value) = 0;
        virtual T pop() = 0;
        virtual T top() = 0;
    protected:
        int count;
    private:
};

#endif // STACK_H
