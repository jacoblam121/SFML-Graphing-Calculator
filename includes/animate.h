#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
#include "../includes/graph/graph.h"
#include "../includes/graph/graph_info.h"
#include <vector>

class animate
{
public:
    // ctor
    animate()
    {
        Graph_Info *_info = new Graph_Info();

        window.create(sf::VideoMode(_info->windowsize.x, _info->windowsize.y), "finalproj");
        sidebar = Sidebar(_info);
        window.setFramerateLimit(60);

        system = new System(_info);
    }
    // run function
    void run()
    {
        while (window.isOpen())
        {
            processevents();
            render();
        }
    }
    // get position of mouse for testing
    string mouse_pos_string(sf::RenderWindow &window)
    {
        return "(" +
               to_string(sf::Mouse::getPosition(window).x) +
               ", " +
               to_string(sf::Mouse::getPosition(window).y) +
               ")";
    }
    // processevents function
    void processevents()
    {
        sf::Event event;
        float mouseX, mouseY;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;
            // text entered, send to system to handle the input
            case sf::Event::TextEntered:
                system->handleinput(event);
                break;
            // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                // pan
                case sf::Keyboard::Left:
                    system->panleft();
                    break;
                case sf::Keyboard::Right:
                    system->panright();
                    break;
                //close window
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                //clear history
                case sf::Keyboard::Delete:
                    system->clearhistory();
                    break;
                //zoom in and out
                case sf::Keyboard::Enter:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    {
                        system->zoomout();
                    }
                    else
                    {
                        system->zoomin();
                    }
                    break;
                }
                break;
            //mouse button clicks, send to sidebar to handle (no mouse clicks in graph window)
            case sf::Event::MouseButtonReleased:
                sidebar.handleclick(event, window, system);
                break;
            default:
                break;
            }
        }
    }
    // render function
    void render()
    {
        Draw();
        window.display();
    }
    //main draw function
    void Draw()
    {
        inputtext = system->draw(window);
        sidebar.draw(window);
        sidebar.drawshapes(window);
        sidebar.drawinputtext(window, inputtext);
        sidebar.inputhistory(window);
        sidebar.drawtext(window);
    }
    //destructor
    ~animate()
    {
        delete system;
    }

private:
    sf::RenderWindow window;
    sf::CircleShape mousePoint; // The little red dot
    System *system;             // container for all the animated objects
    Graph *graph;
    bool mouseIn;    // mouse is in the screen
    Sidebar sidebar; // rectangular message sidebar
    sf::Text inputtext;
    sf::Text coords;
};

#endif // GAME_H
