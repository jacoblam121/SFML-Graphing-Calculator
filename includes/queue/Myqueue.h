#ifndef myqueue_h
#define myqueue_h

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
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator()
        {
            _ptr = NULL;
        }                  //default ctor
        Iterator(node<T>* p)
        {
            _ptr = p;
        }        //Point Iterator to where
        //...                        //  p is pointing to
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
 
    private:
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const;
    
    friend ostream& operator << (ostream& outs, const Queue& printMe)
    {
        node<T>* walker = printMe._front;

        outs << "Queue:Head->";

        while(walker != nullptr)
        {
            outs << *walker;
            walker = walker->_next;
        }
        outs << "|||";

        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};
template <typename T>
Queue<T>::Queue()
{
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}
template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe)
{
    _size = copyMe._size;
    _front = _copy_list(copyMe._front);
    _rear = _copy_list(_front, copyMe._front);
    // _rear = _copy_list(copyMe._rear);
}
template <typename T>
Queue<T>::~Queue()
{
    // cout << "destructor fired" << endl;
    _clear_list(_front);
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_front);
    _size = RHS._size;
    _front = _copy_list(RHS._front);
    _rear = _copy_list(_front, RHS._front);
    // _rear = _copy_list(RHS._rear);

    return *this;
}
template <typename T>
bool Queue<T>::empty()
{
    if (_front == nullptr)
    {
        return true;
    }
    return false;
}
template <typename T>
T Queue<T>::front()
{
    return _front->_item;
}
template <typename T>
T Queue<T>::back()
{

    // _rear = _last_node(_front);
    return _rear->_item;
}
template <typename T>
void Queue<T>::push(T item)
{
    _size++;
    
    node<T>* temp = new node<T>(item);
    
    if(_front == nullptr)
    {
        _rear = temp;
        _rear->_next = nullptr;
        _front = _rear;
    }
    else
    {
        _rear->_next = temp;
        temp->_next = nullptr;
        _rear = temp;
    }

}
template <typename T>
T Queue<T>::pop()
{
    _size--;
    T popped = _front->_item;
    assert(_front != nullptr);
    // node<T>* ptr = _front;
    // _front = _front->_next;
    // cout << popped << endl;
    // delete ptr;
    _delete_node(_front, _front);
    if(_front == nullptr)
    {
        _rear == nullptr;
    }
    return popped;
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}           //Iterator to the head node
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return nullptr;
}              //Iterator to NULL
template <typename T>
void Queue<T>::print_pointers()
{
    // Queue<T*> *ptr;

    Queue<T>::Iterator it;
    for(it = _front; it != nullptr; it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
template <typename T>
int Queue<T>::size() const
{
    // int size = 0;
    // node<T>* walker = _front;

    // while(walker != nullptr)
    // {
    //     walker = walker->_next;
    //     size++;
    // }
    // return size;
    return _size;
}

#endif