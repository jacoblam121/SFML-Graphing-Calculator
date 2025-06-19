#ifndef coord_translation_h
#define coord_translation_h

#define M_PI 3.14159265358979323846

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "graph_info.h"
#include "graph.h"
#include "plot.h"
// #include "../../includes/sidebar.h"
#include "../../includes/token/token.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include <iostream>

using namespace std;

class Coord_Translation
{
public:
    // default ctor
    Coord_Translation()
    {
    }
    // ctor that takes in info from graph
    Coord_Translation(Graph_Info *info_input) : _info(info_input)
    {
    }
    // unused
    Coord_Translation(vector<sf::Vector2f> points)
    {
    }
    // sets info from graph_info
    vector<sf::Vector2f> set_info(Graph_Info *info_input)
    {
        info_input = _info;
    }
    // converts points calculated from plot to screen coordinates
    vector<sf::Vector2f> operator()(const vector<sf::Vector2f> &_points)
    {
        // vector<sf::Vector2f> polar_points = cartesianToPolar(_points);

        // get proper domain and range as well as scale
        // float range_x = _info->domain.y - _info->domain.x;
        // float range_y = _info->domain.y - _info->domain.x;
        // float x_scale = _info->graphpanel / range_x;
        // float y_scale = _info->windowsize.y / range_y;

        // // iterate through vector of points and convert them to screen coordinates
        // for (int i = 0; i < _points.size(); i++)
        // {
        //     float r = _points[i].x;
        //     float theta = _points[i].y * M_PI / 180.0;

        //     // convert polar coordinates to cartesian coordinates
        //     float x = r * cos(theta);
        //     float y = r * sin(theta);

        //     // calculation done using domain as well as scale and offset
        //     float screen_x = (x - _info->domain.x) * x_scale + _info->offset.x;
        //     float screen_y = (_info->domain.y - y) * y_scale + _info->offset.y;

        //     // push back screen point to vector
        //     sf::Vector2f screen_point(screen_x, screen_y);
        //     _translated_points.push_back(screen_point);
        // }

        float range_x = _info->domain.y - _info->domain.x;
        float range_y = _info->domain.y - _info->domain.x;
        float x_scale = _info->graphpanel / range_x;
        float y_scale = _info->windowsize.y / range_y;

        // comment
        // iterate through vector of points and convert them to screen coordinates
        for (int i = 0; i < _points.size(); i++)
        {
            float x = _points[i].x;
            float y = _points[i].y;

            // calculation done using domain as well as scale and offset
            float screen_x = (x - _info->domain.x) * x_scale + _info->offset.x;
            float screen_y = (_info->domain.y - y) * y_scale + _info->offset.y;

            // push back screen point to vector
            sf::Vector2f screen_point(screen_x, screen_y);
            _translated_points.push_back(screen_point);
        }
        return _translated_points;
    }

    vector<sf::Vector2f> cartesianToPolar(const vector<sf::Vector2f> &_points)
    {
        vector<sf::Vector2f> polar_points;

        for (const sf::Vector2f &point : _points)
        {
            // convert cartesian coordinates to polar coordinates
            float r = sqrt(point.x * point.x + point.y * point.y);
            float theta = atan2(point.y, point.x) * 180.0 / M_PI;

            // add polar point to vector
            sf::Vector2f polar_point(r, theta);
            polar_points.push_back(polar_point);
        }

        return polar_points;
    }

private:
    Graph_Info *_info;
    Queue<Token *> _infix;
    Queue<Token *> _postfix;
    vector<Token *> _tokens;
    // vector<sf::Vector2f> _points;
    vector<sf::Vector2f> _translated_points;
    // Sidebar sidebar;
};

#endif