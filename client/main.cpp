
#include <SFML/Graphics.hpp>
#include <NutsEngine.h>
#include <stdio.h>

int main()
{
    runEngine();

    sf::RenderWindow window;
    window.create((sf::VideoMode){800, 600, 32}, "Title");
    window.setFramerateLimit(0);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}