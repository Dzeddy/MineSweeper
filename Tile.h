//
// Created by Dylan on 12/1/2022.
//

#ifndef PROJECT4V2_TILE_H
#define PROJECT4V2_TILE_H
#include <SFML/Graphics.hpp>
/*
 * Tile Class
This class implements the tile widgets that make up the board. The class can
be optionally subclassed to further encapsulate special traits. Each tile’s
neighbor configuration can vary (see Figure 1). When a tile is adjacent to the
edge of the board, the neighbor pointer should be a nullptr value.
public enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED }
Represents tile’s current UI state (visualization).
public Tile(sf::Vector2f position)
Constructs a new tile object at the designated _position.
public sf::Vector2f getLocation()
Returns the position of this tile.
public State getState()
Returns current state of this tile.
public std::array<Tile*, 8>& getNeighbors()
Returns pointer to array of Tile pointers (see Figure 2 for ordering).
public void setState(State _state)
Sets the state of this tile. Should trigger other behaviors related to the state change (including visualization).
public void setNeighbors(std::array<Tile*, 8> _neighbors)
Populates / replaces the neighboring tile container.
public void onClickLeft()
Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.
public void onClickRight()
Toggles this tile’s state between FLAGGED and HIDDEN.
public void draw()
Render this tile to the screen according to is state.
protected void revealNeighbors()
Based on State and mine content of the tile neighbors, set their state to REVEALED.
 */
#include <array>
class Tile {
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
    ~Tile();
private:
    //overloaded copy operator
    sf::Sprite *sprite;
    Tile();
    bool isMine;
    int number = 0;
    std::array<Tile*, 8> neighbors;
    friend class GameState;
    friend class Toolbox;
    sf::Vector2f location;
    State state;
};


#endif //PROJECT4V2_TILE_H
