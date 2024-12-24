#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Dan's CMake SFML Project");
    window.setFramerateLimit(144);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the windows events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requsted" event will close the window/end program
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // The below window.clear/draw/display cycle is the heart of the engine and viewing movement
        
        /**
         * Modern graphics hardware and APIs are really made for repeated clear/draw/display cycles where 
         * everything is completely refreshed at each iteration of the main loop. Don't be scared to draw 
         * 1000 sprites 60 times per second. You're far below the millions of triangles that your computer 
         * can handle.
         */

        // clear the window with green color
        window.clear(sf::Color::Green);

        // draw everything here
        // window.draw(...);

        // end the current frame
        window.display();
    }
}
