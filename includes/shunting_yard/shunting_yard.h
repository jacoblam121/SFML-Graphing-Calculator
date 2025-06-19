#ifndef shunting_yard_h
#define shunting_yard_h

#include "../../includes/token/token.h"
#include "../../includes/queue/Myqueue.h"
#include "../../includes/stack/Mystack.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

using namespace std;

class ShuntingYard
{
    public:

        template<typename T>
    class Iterator
    {
    public:
        friend class RPN;          //give access to list to access _ptr
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

    ShuntingYard()
    {

    }

    ShuntingYard(Queue<Token*> infix):_infix(infix)
    {
        
    }

    Queue<Token*> infix(Queue<Token*> infix)
    {
        _infix = infix;
        return _infix;
    }

    Queue<Token*> postfix()
    {
        return sy();
    }

    Queue<Token*> postfix(const Queue<Token*>& infix)
    {
        _postfix = infix;
        return sy();
    }

    Queue<Token*> sy()
    {
        // cout << "sy func begin" << endl;
        //_infix is infixqueue
        //_postfix is outputqueue
        Stack<Token*> stack;
        int o1prec = 0, o2prec = 0;

        Queue<Token*>::Iterator it;
        for(it = _infix.begin(); it != _infix.end(); it++)
        {
            int type = (*it)->type();

            // cout << "type: " << type << endl;
            // cout << "type " << type << endl;

            // Stack<Token*> stack2 = stack;

            Token* stacktop = nullptr;
            string item;
            int prec = 0;

            switch(type)
            {
                case Token::UNKNOWN:
                    break;
                case Token::INTEGER: //number
                {
                    // cout << "pushing integer into output queue" << endl;
                    _postfix.push(*it);
                    break;
                }
                case Token::OPERATOR: //op
                {
                    if(static_cast<Operator*>(*it)->getprecval() == 3)
                    {
                        // cout << "pushing function into queue" << endl;
                        _postfix.push(*it);
                    }
                    else if((!stack.empty()) && (stack.top()->type() != 3) && static_cast<Operator*>(stack.top())->getprecval() != 3)
                    {
                        // if(static_cast<Operator*>(*it)->getprecval() == 3)
                        // {
                        //     throw runtime_error("func found in operator if?");
                        // }
                        stacktop = stack.top();
                        string o1item = (*it)->token();
                        string o2item = stacktop->token();

                        o1prec = static_cast<Operator*>(*it)->get_prec(o1item);
                        // cout << "o1: " << o1item << " | prec: "<< o1prec << endl;
                    
                        o2prec = static_cast<Operator*>(stack.top())->get_prec(o2item);
                        // cout << "o2: " << o2item << " | prec: " << o2prec << endl;

                        if(stack.empty())
                        {
                            throw runtime_error("Error: stack empty from case 2");
                        }

                        while(static_cast<Operator*>(stack.top())->getprecval() > static_cast<Operator*>(*it)->getprecval())
                        // if(o2prec >= o1prec)
                        {
                            _postfix.push(stack.pop());

                            if(stack.empty())
                            {
                                break;
                            }
                        }
                        stack.push(*it);
                        int topofstack = static_cast<Operator*>(stack.top())->getprecval();
                        // cout << "prec of op pushed into stack: " << topofstack << endl;
                    }
                    else
                    {
                        stack.push(*it);
                        int topofstack = static_cast<Operator*>(stack.top())->getprecval();
                        // cout << "prec of op pushed into stack: " << topofstack << endl;
                    }

                    // cout << "end of case 2" << endl;

                    break;
                    
                    // cout << "hello" << endl;

                }
                case Token::LEFTPAREN: //leftparen
                {
                    // cout << "pushing leftparen into stack" << endl;
                    stack.push(*it);
                    break;
                }
                case Token::RIGHTPAREN: //rightparen
                {
                    // stacktop = stack.top();
                    // item = stacktop->token();
                    // prec = static_cast<Operator*>(stack.top())->get_prec(item);
                    // cout << "item: " << item << " | prec: " << prec << endl;

                    if(!stack.empty())
                    {
                        while(static_cast<Token*>(stack.top())->type() != 3)
                        {
                            if(stack.empty())
                            {
                                throw runtime_error("Error: stack empty from rightparen");
                            }

                            _postfix.push(stack.pop());

                            if(stack.empty())
                            {
                                break;
                            }
                        }   
                    }
                    // while((stack.top())->type() != 3)
                    // {
                    //     // if(stack.empty())
                    //     // {
                    //     //     throw runtime_error("Error: stack empty from rightparen");
                    //     // }

                    //     _postfix.push(stack.pop());

                    //     if(stack.empty())
                    //     {
                    //         break;
                    //     }
                    // }

                    // while(prec != 3)
                    // {
                    //     _postfix.push(stack.pop());
                    // }

                    // assert(static_cast<Operator*>(stack.top())->getprecval() == 3);

                    assert(stack.top()->type() == 3);

                    stack.pop();

                    if(static_cast<Operator*>(stack.top())->getprecval() == 3)
                    {
                        // cout << "pushing function into output queue" << endl;
                        _postfix.push(stack.pop());
                    }

                    break;
                }
            }
        }

        if(!stack.empty())
        {
            // cout << "stack not empty" << endl;
        }
        else
        {
            // cout << "stack empty" << endl;
        }

        while(!stack.empty())
        {
            //assert op on top of stack != '('
            if(static_cast<Token*>(stack.top())->type() == 3)
            {
                throw runtime_error("leftparen found - should be deleted");
            }
            _postfix.push(stack.pop());
        }

        // while(!_postfix.empty())
        // {
        //     cout << _postfix.pop()->token() << " ";
        // }
        // cout << endl;
        
        // cout << "sy func end" << endl;

        return _postfix;
    }

    private:

    Queue<Token*> _infix;
    Queue<Token*> _postfix;
};

#endif