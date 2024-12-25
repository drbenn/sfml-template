#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    // create the window
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Dan's CMake SFML Project");
    window.setFramerateLimit(144);

    // Load a font
    sf::Font font;
    if (!font.openFromFile("../assets/fonts/excluded.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1; // Exit if the font fails to load
    }

    // Create text object
    sf::Text text(font);                                    // Set the font
    text.setString("Billy's Hammer");                       // Set the text string
    text.setCharacterSize(96);                              // Set the size of the text
    text.setFillColor(sf::Color::Blue);                     // Set the text color
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);   // set the text style
    text.setPosition({100.f,100.f});                        // Set the position on the window


    // Load the sound buffer
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../assets/sounds/billy9.mp3")) // Adjust path to your sound file
    {
        std::cerr << "Failed to load sound!" << std::endl;
        return -1;
    }

    // Create a sound object
    sf::Sound sound(buffer);

    // Record the start time
    auto startTime = std::chrono::steady_clock::now();
    bool soundPlayed = false;

    // Load a texture
    sf::Texture grassTexture("../assets/textures/texture grass 3.png");
    // Enable repeating for the texture
    grassTexture.setRepeated(true);
    grassTexture.setSmooth(true);
    sf::Sprite grassSprite(grassTexture);
    grassSprite.setColor(sf::Color(0, 200, 100, 205));

    // Define the size of the area to cover (half the screen)
    sf::FloatRect screenBounds = window.getView().getViewport();
    sf::Vector2u windowSize = window.getSize();

    // Set the texture rectangle to cover half the screen
    // (In this example, half the screen width and full height)
    grassSprite.setTextureRect(sf::IntRect(
        {0, 0},                                                                             // vector position
        {static_cast<int>(window.getSize().x / 2), static_cast<int>(window.getSize().y)     // vector size
    }));

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

        // Calculate elapsed time
        auto elapsedTime = std::chrono::steady_clock::now() - startTime;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count() >= 1)
        {
            // Play the sound after 3 seconds
            if (sound.getStatus() != sf::Sound::Status::Playing && !soundPlayed)
            {
                sound.play();
                soundPlayed = true;
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
        window.clear(sf::Color::Black);

        // draw everything here
        window.draw(grassSprite);
        window.draw(text);

        // end the current frame
        window.display();
    }
}
