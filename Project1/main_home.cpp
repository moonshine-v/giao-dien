#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>  
#include "User.h" 

using namespace sf;

// Function to create text
Text createText(Font& font, const std::string& str, int size, Color color) {
    Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    return text;
}

int main() {
    // Create the window in full screen mode
    RenderWindow window(VideoMode::getDesktopMode(), "Poker Game", Style::Fullscreen);
    User user; // Create a User object

    // Load font
    Font font;
    if (!font.loadFromFile("Tajawal-Light.ttf")) {
        std::cout << "Error loading font\n";
        return -1;
    }

    // Load background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("poker.jpg")) {
        std::cout << "Error loading background image\n";
        return -1;
    }
    Sprite background(backgroundTexture);
    background.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    // Load background music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("music.ogg")) {
        std::cout << "Error loading background music\n";
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    // Create title and buttons
    Text title = createText(font, "Poker Game", 90, Color::Yellow);
	title.move(0, 100); 
    title.setPosition(window.getSize().x / 2 - 200, 100); // Center the title
    Text playButton = createText(font, "Play", 50, Color::White);
    playButton.setPosition(window.getSize().x / 2 - 50, 400); // Center the Play button
    Text optionsButton = createText(font, "Options", 50, Color::White);
    optionsButton.setPosition(window.getSize().x / 2 - 70, 500); // Center the Options button
    Text exitButton = createText(font, "Exit", 50, Color::White);
    exitButton.setPosition(window.getSize().x / 2 - 50, 600); // Center the Exit button

    user.setPosition(window.getSize().x / 2 - 100, 400); // Position for the user name input
    user.setEnteringName(false); // Start with the name input disabled

    enum GameState { MENU, NAME_INPUT };
    GameState gameState = MENU; // Initial state

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameState == MENU) {
                // Check for button clicks
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        gameState = NAME_INPUT; // Transition to name input screen
                        user.setEnteringName(true); // Enable name input
                    }
                    else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        window.close(); // Close window if exit button is clicked
                    }
                }

                // Check for hover effects
                if (playButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
                    playButton.setFillColor(Color::Green);
                }
                else {
                    playButton.setFillColor(Color::White);
                }

                if (exitButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
                    exitButton.setFillColor(Color::Red);
                }
                else {
                    exitButton.setFillColor(Color::White);
                }

            }
            else if (gameState == NAME_INPUT) {
                // Capture text input for name when enteringName is true
                if (event.type == sf::Event::TextEntered) {
                    user.handleTextEntered(event);
                }
            }
        }

        window.clear();
        window.draw(background);

        if (gameState == MENU) {
            // Draw menu items
            window.draw(title);
            window.draw(playButton);
            window.draw(optionsButton);
            window.draw(exitButton);
        }
        else if (gameState == NAME_INPUT) {
            // Draw user name input
            user.draw(window);
        }

        window.display();
    }

    // Retrieve the user name after exiting the loop
    std::cout << "User name: " << user.getUserName() << std::endl;
    return 0;
}
