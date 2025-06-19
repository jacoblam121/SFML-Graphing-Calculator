#ifndef graph_info_h
#define graph_info_h

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

struct Graph_Info
{
    //main equation
    string equation;
    //windowsize +  graphpanel and sidebar
    sf::Vector2f windowsize = sf::Vector2f(1200, 960);
    float graphpanel = windowsize.x * 4 / 5;
    float sidebar = windowsize.x * 1 / 5;
    //defining graph attributes
    sf::Vector2f origin = sf::Vector2f(graphpanel / 2, windowsize.y / 2);
    sf::Vector2f scale = sf::Vector2f(1, 1); // x
    sf::Vector2f domain = sf::Vector2f(-5, 5);
    sf::Vector2f range = sf::Vector2f(-5, 5);
    sf::Vector2f offset = sf::Vector2f(0, 0);
    //number of points to draw
    int points = windowsize.x * 10;
};
#endif