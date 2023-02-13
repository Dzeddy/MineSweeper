//
// Created by Dylan on 12/1/2022.
//
/*
 * The GameState object should contain the Tile objects that represent the locations in the game and play status.
public enum PlayStatus { WIN, LOSS, PLAYING }
Tracks the play status of the game, which is reflected in the behavior of the user interface and visualizations.
public GameState(sf::Vector2i _dimensions = Vector2i(25, 16), int _numberOfMines = 50)
Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.
public GameState(const char* filepath)
Constructs a game state based on the size, mine placement, and mine number specified at filepath.
public int getFlagCount()
Current count of the number of flags placed on the screen.
public int getMineCount()
Current count of the number of mines actually on the board.
public Tile* getTile(int x, int y)
Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds.
public PlayStatus getPlayStatus()
Returns the play status of the game.
public void setPlayStatus(PlayStatus _status)
Sets the play status of the game.
 */
#ifndef PROJECT4V2_GAMESTATE_H
#define PROJECT4V2_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "Tile.h"

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
private:
    std::vector<std::vector<Tile>> Board;
    friend class Toolbox;
    sf::Vector2i dimensions;
    int numberOfMines;
    int flagCount;
    int mineCount;
    PlayStatus playStatus;
};


#endif //PROJECT4V2_GAMESTATE_H
