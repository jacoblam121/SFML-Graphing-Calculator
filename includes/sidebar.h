#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../includes/graph/graph_info.h"
#include "../includes/graph/graph.h"
#include "system.h"
#include "constants.h"

using namespace std;

class Sidebar
{
public:
    // default ctor
    Sidebar()
    {
    }
    // ctor that takes in graph info, load up font
    Sidebar(Graph_Info *info) : _info(info)
    {
        font.loadFromFile("arial.ttf");

        if (!font.loadFromFile("arial.ttf"))
        {
            throw runtime_error("arial.ttf not found");
        }

        _left = _info->graphpanel;
        _width = _info->sidebar;
    }
    // draw function that sets spacing (not really used)
    void draw(sf::RenderWindow &window)
    {
        const double VERTICAL_LINE_SPACING = 5.0;
        const double LEFT_MARGIN = 10.0;
    }
    // draws the inputtext from system
    void drawinputtext(sf::RenderWindow &window, sf::Text &inputtext)
    {
        window.draw(inputtext);
    }
    //function that draws the text for the history as well as sets up the boxes
    void inputhistory(sf::RenderWindow &window)
    {
        int maxlines = 9;
        // draw history from history.txt under graph button
        ifstream history("history.txt");
        vector<string> linespacing;

        string line;
        // read in history and push back lines to vector for spacing
        while(getline(history, line))
        {
            linespacing.push_back(line);

            if (linespacing.size() > maxlines)
            {
                linespacing.erase(linespacing.begin());
            }
        }
        //i to keep track of lines, then draw text boxes
        int i = 0;
        for (const string &line : linespacing)
        {
            //draw text shifted down by 40 each time
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);
            text.setString(line);
            text.setPosition(_info->graphpanel + 30, 180 + i * 40);
            window.draw(text);

            // set up rectangle for each line
            for (int j = 0; j < 10; j++)
            {
                sf::RectangleShape rect(sf::Vector2f(220, 30));
                rect.setPosition(_info->windowsize.x - 230, 180 + j * 40);
                rect.setOutlineThickness(0);
                rect.setOutlineColor(sf::Color::Black);
                rect.setFillColor(sf::Color::Transparent);
                historybuttons.push_back(rect);
            }
            i++;
        }
        history.close();
    }
    //unused
    string &operator[](int index)
    {
        return items[index];
    }
    //draws all text
    void drawtext(sf::RenderWindow &window)
    {
        font.loadFromFile("arial.ttf");
        //graph/clear button
        buttontext.setFont(font);
        buttontext.setCharacterSize(22);
        buttontext.setFillColor(sf::Color::Black);
        buttontext.setPosition(sf::Vector2f(_info->windowsize.x - 185, 80));
        buttontext.setString("Graph / Clear");
        //history header
        historytext.setFont(font);
        historytext.setCharacterSize(22);
        historytext.setFillColor(sf::Color::Black);
        historytext.setPosition(sf::Vector2f(_info->windowsize.x - 155, 140));
        historytext.setString("History");
        //controls header
        controls.setFont(font);
        controls.setCharacterSize(22);
        controls.setFillColor(sf::Color::Black);
        controls.setPosition(sf::Vector2f(_info->windowsize.x - 163, 560));
        controls.setString("Controls");
        //for legend
        c1.setFont(font);
        c1.setCharacterSize(16);
        c1.setFillColor(sf::Color::Black);
        c1.setPosition(sf::Vector2f(_info->windowsize.x - 200, 600));
        c1.setString("Zoom in: Enter");
        //for legend
        c2.setFont(font);
        c2.setCharacterSize(16);
        c2.setFillColor(sf::Color::Black);
        c2.setPosition(sf::Vector2f(_info->windowsize.x - 200, 630));
        c2.setString("Zoom out: Shift+Enter");
        //for legend
        c3.setFont(font);
        c3.setCharacterSize(16);
        c3.setFillColor(sf::Color::Black);
        c3.setPosition(sf::Vector2f(_info->windowsize.x - 200, 660));
        c3.setString("Pan: Arrow keys");
        //for legend
        c4.setFont(font);
        c4.setCharacterSize(16);
        c4.setFillColor(sf::Color::Black);
        c4.setPosition(sf::Vector2f(_info->windowsize.x - 200, 690));
        c4.setString("Graph/Clear: Tab");
        //for legend
        c5.setFont(font);
        c5.setCharacterSize(16);
        c5.setFillColor(sf::Color::Black);
        c5.setPosition(sf::Vector2f(_info->windowsize.x - 200, 720));
        c5.setString("Clear History: Delete");
        //for legend
        c6.setFont(font);
        c6.setCharacterSize(16);
        c6.setFillColor(sf::Color::Black);
        c6.setPosition(sf::Vector2f(_info->windowsize.x - 200, 750));
        c6.setString("Exit:Esc");

        //draw all the text
        window.draw(buttontext);
        window.draw(historytext);
        window.draw(controls);
        window.draw(c1);
        window.draw(c2);
        window.draw(c3);
        window.draw(c4);
        window.draw(c5);
        window.draw(c6);
    }
    //draws all shapes
    void drawshapes(sf::RenderWindow &window)
    {
        //blue outline
        rect.setFillColor(sf::Color(102, 179, 255));
        rect.setPosition(sf::Vector2f(_left, 0));
        rect.setSize(sf::Vector2f(_width, _info->windowsize.y));
        //input box
        inputbox.setSize(sf::Vector2f(220, 50));
        inputbox.setFillColor(sf::Color::White);
        inputbox.setPosition(sf::Vector2f(_info->windowsize.x - 230, 10));
        //graph/clear button
        graphbutton.setSize(sf::Vector2f(220, 50));
        graphbutton.setFillColor(sf::Color(255, 255, 90));
        graphbutton.setPosition(sf::Vector2f(_info->windowsize.x - 230, 70));
        //history box
        historybox.setSize(sf::Vector2f(220, 410));
        historybox.setFillColor(sf::Color(209, 213, 219));
        historybox.setPosition(sf::Vector2f(_info->windowsize.x - 230, 130));
        //menu box
        menu.setSize(sf::Vector2f(220, 240));
        menu.setFillColor(sf::Color(230, 204, 255));
        menu.setPosition(sf::Vector2f(_info->windowsize.x - 230, 550));
        //draws shapes
        window.draw(rect);
        window.draw(inputbox);
        window.draw(graphbutton);
        window.draw(historybox);
        window.draw(menu);
        //draws history buttons from vector
        for (const auto &rect : historybuttons)
        {
            window.draw(rect);
        }
    }
    //handles clicking on graph/clear button
    void handleclick(sf::Event &event, sf::RenderWindow &window, System *system)
    {

        sf::Vector2i pos = mousepos(window);
        sf::FloatRect graphbuttonbounds = graphbutton.getGlobalBounds();

        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (graphbuttonbounds.contains(static_cast<float>(pos.x), static_cast<float>(pos.y)))
            {
                if (system == nullptr)
                {
                    throw runtime_error("system is null");
                }
                cout << "graph button clicked" << endl;

                system->inputgraph();
            }
        }
    }
    //gets mouse position
    sf::Vector2i mousepos(sf::RenderWindow &window)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);

        return pos;
    }

private:
    sf::RectangleShape rect; // sidebar rectangle
    vector<string> items;    // strings to place on the sidebar
    sf::Font font;           // used to draw text
    sf::Text sb_text;        // used to draw strings on the window object
    Graph_Info *_info;       // pointer to graph info object
    sf::RectangleShape inputbox;
    sf::RectangleShape graphbutton;
    sf::RectangleShape historybox;
    sf::RectangleShape menu;
    sf::Text buttontext;
    sf::Text historytext;
    sf::Text controls;
    sf::Text c1;
    sf::Text c2;
    sf::Text c3;
    sf::Text c4;
    sf::Text c5;
    sf::Text c6;
    System *system;
    bool buttonclicked = false;
    vector<sf::RectangleShape> historybuttons;

    float _left;
    float _width;
};

#endif // SIDEBAR_H
