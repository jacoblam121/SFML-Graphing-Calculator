#ifndef plot_h
#define plot_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "graph_info.h"
#include "graph.h"
#include "../../includes/token/token.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/queue/Myqueue.h"
// #include "../../includes/sidebar.h"
#include "../../includes/polar.h"
#include "coord_translation.h"
#include <iostream>

class Plot
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
    // default ctor
    Plot()
    {
    }
    // ctor that  takes in info from graph, calls tokenize
    Plot(Graph_Info *info_input, Polar polar_input = Polar()) : _info(info_input), polar(polar_input)
    {
        tokenize();
    }
    // set info
    vector<sf::Vector2f> set_info(Graph_Info *info_input)
    {
        info_input = _info;
        tokenize();
    }
    // calls shunting yard and rpn to calculate points,
    // then gets the actual screen coordinates from coord translation
    vector<sf::Vector2f> operator()()
    {
        Queue<Token *>::Iterator it;
        for (it = _infix.begin(); it != _infix.end(); it++)
        {
            // cout << "entered iterator" << endl;
            if((*it)->type() == 2)
            {
                string opstring = (*it)->getvalue();
                if(opstring == "theta")
                {
                    polar.switchpolar(true);
                }
                else
                {
                    polar.switchpolar(false);
                }
            }
        }

        ShuntingYard *sy = new ShuntingYard(_infix);
        _postfix = sy->postfix();
        RPN rpn(_postfix);

        // get domain and range correct
        float range_x = _info->domain.y - _info->domain.x;
        float x_start = _info->domain.x - (_info->offset.x * range_x / _info->graphpanel);
        float x_end = _info->domain.y - (_info->offset.x * range_x / _info->graphpanel);

        // if(polar.ispolar())
        // {
        //     x_end *= 2;
        // }


        // push points into vector using rpn to evalute the y values
        for (float x = x_start; x <= x_end; x += (x_end - x_start) / _info->points)
        {
            if (polar.ispolar())
            {
                // cout << "ispolar" << endl;
                float r = rpn(x);
                float theta = x;
                float x_polar = r * cos(theta);
                float y_polar = r * sin(theta);

                sf::Vector2f point(x_polar, y_polar);
                _points.push_back(point);
            }
            else
            {
                // cout << "iscartesian" << endl;
                float y = rpn(x);
                sf::Vector2f point(x, y);
                _points.push_back(point);
            }
        }

        // get points from coord translation

        Coord_Translation translate(_info);
        _points = translate(_points);

        return _points;
    }

    // calls tokenize to get infix
    void tokenize()
    {
        string equation = _info->equation;
        _infix = Tokenize::tokenizeinput(equation);
    }

private:
    Graph_Info *_info;
    Queue<Token *> _infix;
    Queue<Token *> _postfix;
    vector<sf::Vector2f> _points;
    Polar polar;
};

#endif