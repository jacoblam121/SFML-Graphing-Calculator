#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/String.hpp>
#include "../includes/graph/graph.h"
#include "../includes/graph/graph_info.h"
#include <string>

using namespace std;
class System
{
public:
    //default ctor
    System() : _info(nullptr), input("")
    {
    }
    //ctor taking graph_info
    System(Graph_Info *info_input) : _info(info_input), input("")
    {
        //set axes
        x_axis = sf::RectangleShape(sf::Vector2f(1, _info->windowsize.y));
        y_axis = sf::RectangleShape(sf::Vector2f(_info->windowsize.x, 1));

        x_axis.setPosition(sf::Vector2f(_info->origin.x, 0));
        y_axis.setPosition(sf::Vector2f(0, _info->origin.y));

        x_axis.setFillColor(sf::Color::Black);
        y_axis.setFillColor(sf::Color::Black);

        //load font and sf::text object for inputting equation
        font.loadFromFile("arial.ttf");
        inputtext.setFont(font);
        inputtext.setCharacterSize(25);
        inputtext.setFillColor(sf::Color::Black);
        inputtext.setPosition(_info->windowsize.x - 220, 18);

        //make new graph
        _graph = new Graph(_info, input);
    }
    //destructor
    ~System()
    {
        delete _graph;
    }
    //function to handle input
    void handleinput(sf::Event &event)
    { 
        //unicode 8 is backspace, if backspace is pressed, pop back the input string
        if (event.text.unicode == 8)
        {
            if (!inputstring.empty())
            {
                inputstring.pop_back();
                inputtext.setString(inputstring);
            }
        }
        //unicode 8 is tab, if tab is pressed, input the graph
        else if (event.text.unicode == 9)
        {
            inputgraph();
        }
        //else add string to inputstring
        else
        {
            inputstring += event.text.unicode;
            inputtext.setString(inputstring);
        }
    }
    //function to send input to graph, also passed to other classes
    void inputgraph()
    {
        input = inputstring;
        savehistory(inputstring);
        inputstring.clear();
        inputtext.setString(inputstring);
        _graph = new Graph(_info, input);
    }
    //pan left function
    void panleft()
    {
        _info->origin += sf::Vector2f(10, 0);
        _info->offset += sf::Vector2f(10, 0);
        x_axis.setPosition(_info->origin.x, 0);
        y_axis.setPosition(0, _info->origin.y);

        _graph->update();
    }
    //pan right function
    void panright()
    {
        _info->origin += sf::Vector2f(-10, 0);
        _info->offset -= sf::Vector2f(10, 0);
        x_axis.setPosition(_info->origin.x, 0);
        y_axis.setPosition(0, _info->origin.y);

        _graph->update();
    }
    //zoom out function
    void zoomout()
    {
        sf::Vector2f zoomlevel(.8, -.8);
        _info->domain -= zoomlevel;
        _graph->update();
    }
    //zoom in function
    void zoomin()
    {
        if (_info->domain.y <= 1)
        {
            cout << "zoom limit reached" << endl;
            return;
        }
        sf::Vector2f zoomlevel(-.8, .8);
        _info->domain -= zoomlevel;
        _graph->update();
    }
    //function to save history to file
    void savehistory(string equation)
    {
        ofstream writefile;
        writefile.open("history.txt", ios::app);
        if (equation != "")
        {
            writefile << equation << endl;
        }
        writefile.close();
    }
    //function to clear history (called when delete is pressed in sidebar)
    void clearhistory()
    {
        ofstream writefile;
        //trunc to clear file
        writefile.open("history.txt", ios::trunc);
        writefile.close();
    }
    //draw function of system
    sf::Text draw(sf::RenderWindow &window)
    {
        window.clear(sf::Color::White);
        window.draw(x_axis);
        window.draw(y_axis);
        _graph->draw(window);
        return inputtext;
    }

private:
    string input;
    Graph_Info *_info;
    Graph *_graph;
    sf::RectangleShape x_axis;
    sf::RectangleShape y_axis;
    sf::RectangleShape rect;
    sf::Font font;
    sf::Text inputtext;
    string inputstring;
    sf::RectangleShape inputbox;
    sf::String sfstring;
};

#endif // SYSTEM_H
