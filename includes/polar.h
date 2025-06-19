#ifndef polar_h
#define polar_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../includes/graph/graph_info.h"

using namespace std;

class Polar
{
public:
    Polar()
    {
        _polar = true;
    }
    void switchpolar(bool ispolar)
    {
        // cout << "switching polar" << endl;
        _polar = ispolar;
        // cout << _polar << endl;
    }
    bool ispolar()
    {
        // cout << _polar << endl;
        return _polar;
    }

private:
    bool _polar;
    float _left;
    float _width;
    Graph_Info *_info;
    sf::Font font;
    sf::RectangleShape cartesianbutton;
    sf::RectangleShape polarbutton;
};

// class Polar
// {
// public:
//     Polar(bool isPolar = false) : _isPolar(isPolar) {}
//     bool ispolar() const { return _isPolar; }
//     void switchpolar(bool isPolar) { _isPolar = isPolar; }

// private:
//     bool _isPolar;
// };

#endif