//
// Created by Dylan on 12/1/2022.
/*
 * Button Class
This class will be used to implement each button widget. Widgets are responsible for rending themselves,
originating interaction (e.g., clicking), and conveying state to the user. It will have these public methods:
public Button(sf::Vector2f _position, std::function<void(void)> _onClick)
Constructs a new object at the specified _position which invokes the _onClick callback when clicked.
public sf::Vector2f getPosition()
Returns the position of the button.
public sf::Sprite* getSprite()
Returns the current sprite of the button.
public void setSprite(sf::Sprite* _sprite)
Sets this button’s visualization to the specified _sprite.
public void onClick()
Invokes the button’s callback method (usually called when clicked).
 */
//

#ifndef PROJECT4V2_BUTTON_H
#define PROJECT4V2_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
private:
    sf::Vector2f position;
    sf::Sprite* sprite;
    std::function<void(void)> clickFunction;
};


#endif //PROJECT4V2_BUTTON_H
