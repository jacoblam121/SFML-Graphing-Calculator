#ifndef graph_h
#define graph_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "graph_info.h"
#include "plot.h"
#include <vector>
#include <iostream>

using namespace std;

class Graph
{
public:
    //ctor to create graph, also checks if empty string to avoid creating graph
    Graph(Graph_Info *graph_info, string input) : _info(graph_info), _input(input)
    {

        _info->equation = _input;

        if (input != "")
        {
            Plot _plotter(_info);
            _points = _plotter();
        }
    }


    //update graph
    void update()
    {
        if (_info->equation != "")
        {
            Plot _plotter(_info);
            _points = _plotter();
        }
    }
    //draw wfunction of graph that draws points
    void draw(sf::RenderWindow &window)
    {
        if (_info->equation != "")
        {
            window.draw(x_axis);
            window.draw(y_axis);

            for (size_t i = 0; i < _points.size(); i++)
            {
                sf::CircleShape point;
                point.setRadius(3);
                point.setFillColor(sf::Color::Red);
                point.setPosition(_points[i]);
                window.draw(point);
            }
            window.draw(rect);
        }
    }
    //destructor
    ~Graph()
    {
        delete _info;
    }

private:
    Graph_Info *_info;
    string _input;
    Plot _plotter;
    vector<sf::Vector2f> _points;
    sf::RectangleShape x_axis;
    sf::RectangleShape y_axis;
    sf::RectangleShape rect;
};

#endif