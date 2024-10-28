#ifndef USER_H
#define USER_H

#include <SFML/Graphics.hpp>
#include <string>

class User {
public:
    User();

    void setPosition(float x, float y);
    void setEnteringName(bool entering);
    void handleTextEntered(sf::Event& event);
    void draw(sf::RenderWindow& window);
    std::string getUserName() const;

private:
    sf::Text userNameText;
    sf::Font font;
    std::string userName;
    bool enteringName;
};

#endif // USER_H
