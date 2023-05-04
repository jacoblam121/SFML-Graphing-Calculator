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
#include "coord_translation.h"
#include <iostream>

class Plot
{
public:
    //default ctor
    Plot()
    {
    }
    //ctor that  takes in info from graph, calls tokenize
    Plot(Graph_Info *info_input) : _info(info_input)
    {
        tokenize();
    }
    //set info
    vector<sf::Vector2f> set_info(Graph_Info *info_input)
    {
        info_input = _info;
        tokenize();
    }
    // calls shunting yard and rpn to calculate points, 
    //then gets the actual screen coordinates from coord translation
    vector<sf::Vector2f> operator()()
    {
        ShuntingYard *sy = new ShuntingYard(_infix);
        _postfix = sy->postfix();
        RPN rpn(_postfix);

        //get domain and range correct
        float range_x = _info->domain.y - _info->domain.x;
        float x_start = _info->domain.x - (_info->offset.x * range_x / _info->graphpanel);
        float x_end = _info->domain.y - (_info->offset.x * range_x / _info->graphpanel);

        //push points into vector using rpn to evalute the y values
        for (float x = x_start; x <= x_end; x += (x_end - x_start) / _info->points)
        {
            float y = rpn(x);
            sf::Vector2f point(x, y);
            _points.push_back(point);
        }

        // get points from coord translation

        Coord_Translation translate(_info);
        _points = translate(_points);

        return _points;
    }

    //calls tokenize to get infix
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
};

#endif