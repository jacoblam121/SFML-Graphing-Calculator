#ifndef mystack_h
#define mystack_h

#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <list>

#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator()
        {
            _ptr = NULL;
        }                //default ctor
        Iterator(node<T>* p)
        {
            _ptr =p;
        }          //Point Iterator to where
        operator bool()                                //casting operator: true if _ptr not NULL
                                                        //      this turned out to be a pain!
        {
            if(_ptr != nullptr)
            {
                return true;
            }
            return false;
        }
        T& operator *()                        //dereference operator
        {
            assert(_ptr);
            return _ptr->_item;
        }
        T* operator ->()                       //member access operator
        {
            assert(_ptr);
            return &_ptr->_item;
        }

        bool is_null()                                 //true if _ptr is NULL
        {
            if(_ptr == nullptr)
            {
                return true;
            }
            return false;
        }

        friend bool operator !=(const Iterator& left,
                                const Iterator& right) //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left,
                                const Iterator& right) //true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator& operator++()                         //member operator: ++it; or ++it = new_value
        {
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused)         //friend operator: it++
        {
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }
                                                //  p is pointing to

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();

    friend ostream& operator<<(ostream& outs, 
                                        const Stack& printMe)
    {
        node<T>* walker = printMe._top;

        outs << "Stack:Head->";

        while(walker != nullptr)
        {
            outs << *walker;
            walker = walker->_next;
        }
        outs << "|||";

        return outs;
    }

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const;

private:
    node<T>* _top;
    int _size;
};

template <typename T>
Stack<T>::Stack()
{
    _top = nullptr;
    _size = 0;
}
template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe)
{
    _size = copyMe._size;
    
    _top = _copy_list(copyMe._top);
}
template <typename T>
Stack<T>::~Stack()
{
    // cout << "destructor fired" << endl;
    _clear_list(_top);
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS)
{
    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_top);
    _size = RHS._size;
    _top = _copy_list(RHS._top);

    return *this;
}
template <typename T>
T Stack<T>::top()
{
    return _top->_item;
}
template <typename T>
bool Stack<T>::empty()
{
    if (_top == nullptr)
    {
        return true;
    }
    return false;
}
template <typename T>
void Stack<T>::push(T item)
{
    _insert_head(_top, item);
}
template <typename T>
T Stack<T>::pop()
{
    T popped;
    // assert(_top != nullptr);
    if(_top == nullptr)
    {
        throw runtime_error("Stack is empty");
    }
    node<T>* ptr = _top;
    // _top = _top->_next;
    popped = ptr->_item;
    // cout << popped << endl;
    _delete_node(_top, ptr);
    // delete ptr;
    return popped;
}
template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const              //Iterator to the head node
{
    return Iterator(_top);
}
template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const                //Iterator to NULL
{
    // node<T>* walker = _top;
    // while(walker != nullptr)
    // {
    //     walker = walker->_next;
    // }
    // return walker;
    return nullptr;
}
template <typename T>
int Stack<T>::size() const
{
    int size = 0;
    node<T>* walker = _top;

    while(walker != nullptr)
    {
        walker = walker->_next;
        size++;
    }
    return size;
}

#endif