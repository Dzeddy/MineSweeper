//
// Created by Dylan on 12/1/2022.
//

#include "Tile.h"
#include <iostream>
#include "Toolbox.h"
/*class Tile {
protected:
    void revealNeighbors();
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
private:
    friend class GameState;
    friend class Toolbox;
    sf::Vector2f location;
    State state;
};
};*/
Tile::Tile(sf::Vector2f position){
    location = position * 32.0f;
    this->setState(HIDDEN);
    isMine = false;
    std::cout << "Tile Created" << std::endl;
}

sf::Vector2f Tile::getLocation() {
    return location;
}

Tile::State Tile::getState() {
    //return current state from enum State
    return state;
}

void Tile::setState(State _state) {
    //set state to _state
    this->state = _state;
}

void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    //set neighbors to _neighbors
    this->neighbors = _neighbors;
}

std::array<Tile*, 8>& Tile::getNeighbors() {
    //return neighbors
    return neighbors;
}

void Tile::onClickLeft() {
    //if state is HIDDEN, set state to REVEALED
    if (this->getState() == HIDDEN){
        this->setState(REVEALED);
        this->revealNeighbors();
    }
    //if state is FLAGGED do nothing
    if (this->getState() == FLAGGED){
        return;
    }
    //if state is REVEALED, revealNeighbors()
    //if state is EXPLODED, do nothing
    if (this->getState() == EXPLODED){
        return;
    }
}

void Tile::onClickRight() {
    //if state is HIDDEN, set state to FLAGGED
    if (this->getState() == HIDDEN){
        this->setState(FLAGGED);
    }else if (this->getState() == FLAGGED){
        this->setState(HIDDEN);
    }
}
void Tile::revealNeighbors() {
    //iterate through neighbors
    for (int i = 0; i < 8; i++){
        //reveal each neighbor if it is hidden and number is 0
        if (neighbors[i] != nullptr){
            if (neighbors[i]->getState() == HIDDEN && neighbors[i]->number == 0 && !neighbors[i]->isMine){
                neighbors[i]->setState(REVEALED);
                neighbors[i]->revealNeighbors();
            }
            //reveal each neighbor if it is hidden and number is not 0
            if (neighbors[i]->getState() == HIDDEN && neighbors[i]->number != 0){
                neighbors[i]->setState(REVEALED);
            }
        }
    }
}
void Tile::draw(){
    if(this->getState() == HIDDEN){
        if(this->isMine && Toolbox::getInstance().isDebug){
            Toolbox::getInstance().gameBoardSprite.draw(*Toolbox::getInstance().sprites["tile_mine"],
                                                        sf::Transform().translate(location));
        }else{
            Toolbox::getInstance().gameBoardSprite.draw(*Toolbox::getInstance().sprites["tile_hidden.png"], sf::Transform().translate(location));
        }
    }else if(this->getState() == REVEALED) {
        //if number = 0
        if (this->number == 0){
            Toolbox::getInstance().gameBoardSprite.draw(*Toolbox::getInstance().sprites["tile_revealed.png"], sf::Transform().translate(location));
        }else{
            Toolbox::getInstance().gameBoardSprite.draw(*Toolbox::getInstance().sprites["numbered_" + std::to_string(this->number)],
                                                        sf::Transform().translate(location));
        }
    }else if(this->getState() == FLAGGED) {
        Toolbox::getInstance().gameBoardSprite.draw(*Toolbox::getInstance().sprites["tile_flagged"],
                                                    sf::Transform().translate(location));
    }else if(this->getState() == EXPLODED) {
        Toolbox::getInstance().gameBoardSprite.draw(*Toolbox::getInstance().sprites["tile_mine"],
                                                    sf::Transform().translate(location));
    }
}

Tile::~Tile() {
    std::cout << "Tile Destroyed" << std::endl;
}