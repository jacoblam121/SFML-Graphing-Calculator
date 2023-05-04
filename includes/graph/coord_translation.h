#ifndef coord_translation_h
#define coord_translation_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "graph_info.h"
#include "graph.h"
#include "plot.h"
#include "../../includes/token/token.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include <iostream>

using namespace std;

class Coord_Translation
{
public:
    //default ctor
    Coord_Translation()
    {
    }
    //ctor that takes in info from graph
    Coord_Translation(Graph_Info *info_input) : _info(info_input)
    {
    }
    //unused
    Coord_Translation(vector<sf::Vector2f> points)
    {

    }
    //sets info from graph_info
    vector<sf::Vector2f> set_info(Graph_Info *info_input)
    {
        info_input = _info;
    }
    //converts points calculated from plot to screen coordinates
    vector<sf::Vector2f> operator()(const vector<sf::Vector2f> &_points)
    {
        //get proper domain and range as well as scale
        float range_x = _info->domain.y - _info->domain.x;
        float range_y = _info->domain.y - _info->domain.x;
        float x_scale = _info->graphpanel / range_x;
        float y_scale = _info->windowsize.y / range_y;

        //iterate through vector of points and convert them to screen coordinates
        for (int i = 0; i < _points.size(); i++)
        {
            float x = _points[i].x;
            float y = _points[i].y;

            //calculation done using domain as well as scale and offset
            float screen_x = (x - _info->domain.x) * x_scale + _info->offset.x;
            float screen_y = (_info->domain.y - y) * y_scale + _info->offset.y;

            //push back screen point to vector
            sf::Vector2f screen_point(screen_x, screen_y);
            _translated_points.push_back(screen_point);
        }

        return _translated_points;
    }

private:
    Graph_Info *_info;
    Queue<Token *> _infix;
    Queue<Token *> _postfix;
    vector<Token *> _tokens;
    // vector<sf::Vector2f> _points;
    vector<sf::Vector2f> _translated_points;
};

#endif