#ifndef rpn_h
#define rpn_h

#include "../../includes/token/token.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"

#include <iostream>

class RPN
{
public:
    template <typename T>
    class Iterator
    {
    public:
        friend class RPN; // give access to list to access _ptr
        Iterator()
        {
            _ptr = NULL;
        } // default ctor
        Iterator(node<T> *p)
        {
            _ptr = p;
        } // Point Iterator to where
        //...                        //  p is pointing to
        operator bool() // casting operator: true if _ptr not NULL
                        //       this turned out to be a pain!
        {
            if (_ptr != nullptr)
            {
                return true;
            }
            return false;
        }
        T &operator*() // dereference operator
        {
            assert(_ptr);
            return _ptr->_item;
        }
        T *operator->() // member access operator
        {
            assert(_ptr);
            return &_ptr->_item;
        }

        bool is_null() // true if _ptr is NULL
        {
            if (_ptr == nullptr)
            {
                return true;
            }
            return false;
        }

        friend bool operator!=(const Iterator &left,
                               const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left,
                               const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++() // member operator: ++it; or ++it = new_value
        {
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it,
                                   int unused) // friend operator: it++
        {
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };
    //default ctor
    RPN()
    {
    }
    //ctor that takes in postfix queue of tokens
    RPN(Queue<Token *> postfix) : _postfix(postfix), rpndouble(0)
    {
    }
    //main rpn function that takes in a double and returns a double
    double rpn(double val)
    {
        // cout << "rpn func begin" << endl;
        Stack<Token *> stack;

        Queue<Token *>::Iterator it;
        for (it = _postfix.begin(); it != _postfix.end(); it++)
        {
            int type = (*it)->type();
            // cout << "type " << type << endl;

            switch (type)
            {
            case 0:
                break;
            case 1:
                stack.push(*it);
                break;
            case 2:
                // if(stack.size() < 2)
                // {
                //     throw runtime_error("Error: less than 2 operands");
                // }
                //if variable push in a token with the double value being passed in
                if (static_cast<Operator *>(*it)->getprecval() == 3) // 3 for variable
                {
                    Token *func = new Token(Integer(val));
                    stack.push(func);
                    break;
                }
                //if trig evaluate the trig function
                else if (static_cast<Operator *>(*it)->getprecval() == 4)
                {
                    Token *arg = stack.pop();
                    Token *op = (*it);
                    stack.push(op->trigeval(arg));
                    break;
                }
                //if log evaluate the function
                else if (static_cast<Operator *>(*it)->getprecval() == 5)
                {
                    Token *arg = stack.pop();
                    Token *op = (*it);
                    stack.push(op->logsqrteval(arg));
                    break;
                }
                //if absval evaluate the function
                else if (static_cast<Operator *>(*it)->getprecval() == 6)
                {
                    Token *arg = stack.pop();
                    Token *op = (*it);
                    stack.push(op->abseval(arg));
                    break;
                }
                //else evaluate as normal
                else
                {
                    Token *arg2 = stack.pop();
                    Token *arg1 = stack.pop();
                    Token *op = (*it);
                    stack.push(op->eval(arg1, arg2));
                    break;
                }
            }
        }

        Token *ans = stack.pop();
        rpndouble = stod(ans->token());
        // cout << "rpn func end" << endl;
        return rpndouble;
    }
    //retuuens the double value of the rpn function
    double operator()(double val)
    {
        return rpn(val);
    }
    //sets the postfix queue of tokens
    Queue<Token *> set_input(Queue<Token *> input)
    {
        _postfix = input;
        return _postfix;
    }
    //prints the double value of the rpn function
    virtual void print()
    {
        cout << rpndouble << endl;
    }

private:
    Queue<Token *> _postfix;
    double rpndouble;
};

#endif