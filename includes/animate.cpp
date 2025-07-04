// #include "animate.h"
// #include "constants.h"
// #include <iostream>
// using namespace std;
// #include "system.h"


// animate::animate():sidebar(WORK_PANEL, SIDE_BAR)

// {
//     cout<<"animate CTOR: TOP"<<endl;
//     window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
//     //VideoMode class has functions to detect screen size etc.
//     //RenderWindow constructor has a third argumnet to set style
//     //of the window: resize, fullscreen etc.

//     //System will be implemented to manage a vector of objects to be animated.
//     //  at that point, the constructor of the System class will take a vector
//     //  of objects created by the animate object.
//     //  animate will
//     system = System();
//     window.setFramerateLimit(120);

//     mouseIn = true;



//     cout<<"Geme CTOR. preparing to load the font."<<endl;
//     //--- FONT ----------
//     //font file must be in the "working directory:
//     //      debug folder
//     //Make sure working directory is where it should be and not
//     //  inside the app file:
//     //  Project->RUN->Working Folder
//     //
//     //font must be a member of the class.
//     //  Will not work with a local declaration
//     if (!font.loadFromFile("arial.ttf")){
//         cout<<"animate() CTOR: Font failed to load"<<endl;
//         cin.get();
//         exit(-1);
//     }

//     myTextLabel = sf::Text("Initial String for myTextLabel", font);
//     myTextLabel.setCharacterSize(20);
//     myTextLabel.setStyle(sf::Text::Bold);
//     myTextLabel.setFillColor(sf::Color::Green);
//     myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-5));







//     cout<<"animate instantiated successfully."<<endl;
// }

// void animate::Draw()
// {
//     //Look at the data and based on the data, draw shapes on window object.
//     system.Draw(window);
//     if (mouseIn){
//         window.draw(mousePoint);
//     }

//     sidebar.draw(window);

//     //- - - - - - - - - - - - - - - - - - -
//     //getPosition() gives you screen coords, getPosition(window) gives you window coords
//     //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
//     //- - - - - - - - - - - - - - - - - - -

//     //drawing Test: . . . . . . . . . . . .
//     //This is how you draw text:)
//     window.draw(myTextLabel);
//     //. . . . . . . . . . . . . . . . . . .
// }

// void animate::update(){
//     //cause changes to the data for the next frame
//     system.Step(command);
//     command = 0;
//     if (mouseIn){
//         //mousePoint red dot:
//         mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
//                                sf::Mouse::getPosition(window).y-5);

//         //mouse location text for sidebar:
//         sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);

//     }
// }
// void animate::render(){
//        window.clear();
//        Draw();
//        window.display();
// }



// void animate::processEvents()
// {
//    sf::Event event;
//    float mouseX, mouseY;
//    while (window.pollEvent(event))//or waitEvent
//        {
//        // check the type of the event...
//            switch (event.type)
//            {
//            // window closed
//            case sf::Event::Closed:
//                window.close();
//                break;

//            // key pressed
//            case sf::Event::KeyPressed:
//                switch(event.key.code){
//                 case sf::Keyboard::Left:
//                    sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
//                    command = 4;
//                    break;
//                case sf::Keyboard::Right:
//                    sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
//                    command = 6;
//                    break;
//                case sf::Keyboard::Escape:
//                    sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
//                    window.close();
//                 break;
//                }

//                break;
//            case sf::Event::MouseEntered:
//                mouseIn = true;
//                break;

//            case sf::Event::MouseLeft:
//                mouseIn = false;
//                break;

//            case sf::Event::MouseMoved:
//                 mouseX = event.mouseMove.x;
//                 mouseY = event.mouseMove.y;
//                 //Do something with it if you need to...
//                break;
//            case sf::Event::MouseButtonReleased:
//                    if (event.mouseButton.button == sf::Mouse::Right)
//                    {
//                        sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
//                                mouse_pos_string(window);

//                    }
//                    else{
//                        sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
//                                mouse_pos_string(window);
//                    }
//                    break;

//                default:
//                    break;
//            }
//        }
// }
// void animate::run()
// {
//    while (window.isOpen())
//    {
//        processEvents();
//        update();
//        render(); //clear/draw/display
//    }
//    cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
// }

// string mouse_pos_string(sf::RenderWindow& window){
//     return "(" +
//             to_string(sf::Mouse::getPosition(window).x) +
//             ", " +
//             to_string(sf::Mouse::getPosition(window).y) +
//             ")";
// }
