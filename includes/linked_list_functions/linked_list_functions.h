#ifndef linked_list_functions_h
#define linked_list_functions_h

#include <iostream>
#include <cassert>
#include "../node/node.h"

//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head)
{
    for(node<ITEM_TYPE>* walker = head; walker != nullptr; walker = walker->_next)
    {
        cout <<  *walker;
    }
    cout << "|||";
}

// //recursive fun! :
// template <typename ITEM_TYPE>
// void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                            ITEM_TYPE key)
{
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr)
    {
        if(walker->_item == key)
        {
            return walker;
        }
        walker = walker->_next;
    }
    return nullptr;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                            ITEM_TYPE insert_this)
{
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);
    temp->_next = head;
    head = temp;

    return temp;
}

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE> *after_this,
                                ITEM_TYPE insert_this)
{
    if(head == nullptr)
    {
        // cout<<"inside head\n";
        return  _insert_head(head, insert_this);
    }

    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);
    
    temp->_next = after_this->_next;
    after_this->_next = temp;

    return temp;
}

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE>* before_this,
                                ITEM_TYPE insert_this)
{

    if(head == before_this)
    {
        return _insert_head(head, insert_this);
    }

    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);
    node<ITEM_TYPE>* walker = _previous_node(head, before_this);

    temp->_next = walker->_next;
    walker->_next = temp;

    // cout << temp->_item << endl;

    return temp;

    
    // temp->_next = after_this->_next;
    // after_this->_next = temp;
}

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                node<ITEM_TYPE>* prev_to_this)
{
    assert(head != nullptr);
    assert(prev_to_this != nullptr);

    node<ITEM_TYPE> *walker = head;

    if(head == prev_to_this)
    {
        return nullptr;
    }

    while(walker->_next != prev_to_this)
    {
        if(walker == nullptr)
        {
            assert(walker != nullptr);
        }
        walker = walker->_next;
    }
    return walker;
}

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                        node<ITEM_TYPE>* delete_this)
{
    node<ITEM_TYPE>* prev_node = _previous_node(head, delete_this);

    ITEM_TYPE hold;

    if(prev_node == nullptr)
    {
        assert(head != nullptr);
        node<ITEM_TYPE>* walker = prev_node;
        head = head->_next;
        delete walker;
    }
    else
    {
        node<ITEM_TYPE>* walker = prev_node->_next;
        prev_node->_next = walker->_next;

        hold = walker->_item;

        // cout << "item in prev node: " << prev_node->_item << endl
        delete walker;
    }
    return hold;
}

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head)
{
    if(head == nullptr)
    {
        return nullptr;
    }

    node<ITEM_TYPE>* newhead = nullptr;
    node<ITEM_TYPE>* walker = head;
    node<ITEM_TYPE>* walker2 = newhead;

    while(walker != nullptr)
    {
        walker2 = _insert_after(newhead, walker2, walker->_item);
        walker = walker->_next;
    }
    // cout<<"end list: ";
    // _print_list(newhead);
    return newhead;


    // node<ITEM_TYPE>* sizewalker = head;
    // int size = 0;
    // while(sizewalker != nullptr)
    // {
    //     sizewalker = sizewalker->_next;
    //     size++;
    // }
    // for(int i = 0; i < size; i++)
    // {
    //     node<ITEM_TYPE>* newNode = new node<ITEM_TYPE>();
    //     newNode->_item = 0;
    //     newNode->_next = nullptr;

    //     node<ITEM_TYPE>* walker = head;
        
    //     while(walker->_next != nullptr)
    //     {
    //         walker = walker->_next;
    //     }

    //     walker->_next = newNode;
    // }
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src)
{
    if(src == nullptr)
    {
        dest = nullptr;
        return nullptr;
    }

    dest = nullptr;
    node<T>* walker = src;
    node<T>* walker2 = dest;

    while(walker != nullptr)
    {
        walker2 = _insert_after(dest, walker2, walker->_item);
        walker = walker->_next;
    }

    //cout << walker2->_item << endl;

    return walker2;
    
    // node<T>* walker3 = dest;

    // while(walker3->_next != nullptr)
    // {
    //     walker3 = walker3->_next;
    // }
    
    // // cout << walker3->_item << endl;

    // return walker3;
    

    // cout<<"end list: ";
    // _print_list(newhead);
}


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head)
{
    // node<ITEM_TYPE>* walker = head;
    // while(walker != nullptr)
    // {
    //     delete[] walker;
    //     walker = walker -> _next;
    // }

    node<ITEM_TYPE>* walker = head;
    
    while(head != nullptr)
    {
        head = head->_next;
        delete[] walker;
        walker = head;
    }
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos)
{
    node<ITEM_TYPE>* walker = head;

    for(int i = 0; walker != nullptr; i++)
    {
        if(i == pos)
        {
            return walker->_item;
        }
        walker = walker->_next;
    }
    cout << "invalid index / item not found" << endl;

    assert(walker != nullptr);
}

// //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// //      Sorted List Routines. order: 0: ascending, order: other: descending
// //                              Assume a Sorted List
// //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                ITEM_TYPE item,
                                bool ascending=true)
{
    node<ITEM_TYPE>* ptr = _where_this_goes(head, item, ascending);

    if(ptr == nullptr)
    {
        // cout << "ptr == nullptr" << endl;
        _insert_head(head, item);
    }
    else
    {
        _insert_after(head, ptr, item);
    }

}

// //insert or add if a dup
// template <typename ITEM_TYPE>
// node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
//                                         ITEM_TYPE item,
//                                         bool ascending=true)
// {

// }

//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                ITEM_TYPE item,
                                bool ascending=true)
{
    if(head == nullptr)
    {
        return nullptr;
    }
    else if(ascending)
    {
        if(head->_item > item)
        {
            // cout << "front" << endl;
            return nullptr;
        }

        node<ITEM_TYPE>* walker = head;

        while(walker != nullptr)
        {
            if(walker->_next == nullptr)
            {
                // cout << walker->_item << endl;
                return walker;
            }
            else if(walker->_next->_item > item)
            {
                // cout << "walker->item: " << walker->_item << endl;
                return walker;
            }
            walker = walker->_next;
        }
    }
    else if(!ascending)
    {
        if(head->_item < item)
        {
            // cout << "front" << endl;
            return nullptr;
        }

        node<ITEM_TYPE>* walker = head;

        while(walker != nullptr)
        {
            if(walker->_next == nullptr)
            {
                // cout << "walker->item: " << walker->_item << endl;
                return walker;
            }
            if(walker->_next->_item < item)
            {
                // cout << walker->_item << endl;
                return walker;
            }
            walker = walker->_next;
        }
    }
    return nullptr;
}

//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head)
{
    node<ITEM_TYPE>* walker = head;

    while(walker->_next != nullptr)
    {
        walker = walker->_next;
    }

    // cout << walker->_item << endl;
    
    return walker;
} 

#endif