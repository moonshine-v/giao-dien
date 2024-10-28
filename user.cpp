#include "User.h"
#include <iostream> 
User::User() : enteringName(false), userName("") {
    if (!font.loadFromFile("Tajawal-Light.ttf")) {
        // Handle error
        std::cerr << "Error loading font\n";
    }
    userNameText.setFont(font);
    userNameText.setCharacterSize(50);
    userNameText.setFillColor(sf::Color::White);
    userNameText.setString("_"); // Initial placeholder
}

void User::setPosition(float x, float y) {
    userNameText.setPosition(x, y);
}

void User::setEnteringName(bool entering) {
    enteringName = entering;
    if (entering) {
        userNameText.setString("_"); // Show placeholder when entering name
    }
}

void User::handleTextEntered(sf::Event& event) {
    if (enteringName) {
        if (event.text.unicode == '\b') { // Handle backspace
            if (!userName.empty()) {
                userName.pop_back();
            }
        }
        else if (event.text.unicode < 128 && event.text.unicode != '\b') { // Handle regular characters
            userName += static_cast<char>(event.text.unicode);
        }
        userNameText.setString(userName + "_"); // Add cursor placeholder
    }
}

void User::draw(sf::RenderWindow& window) {
    window.draw(userNameText);
}

std::string User::getUserName() const {
    return userName;
}
