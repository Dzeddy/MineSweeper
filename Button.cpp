//
// Created by Dylan on 12/1/2022.
//

#include "Button.h"

#include <utility>
/*
 * class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
private:
    sf::Vector2f position;
    sf::Sprite* sprite;
};
 */
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    this->position = _position;
    this->sprite = nullptr;
    this->clickFunction = std::move(_onClick);
}

sf::Vector2f Button::getPosition() {
    return this->position;
}

sf::Sprite* Button::getSprite() {
    return this->sprite;
}

void Button::setSprite(sf::Sprite* _sprite) {
    this->sprite = _sprite;
}

void Button::onClick() {
    this->clickFunction();
}