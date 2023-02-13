//
// Created by Dylan on 12/1/2022.
//
#include <iostream>
#include "fstream"
#include "GameState.h"
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    std::vector<std::vector<Tile>> board(dimensions.y, std::vector<Tile>(dimensions.x, Tile(sf::Vector2f(0, 0))));
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            board[i][j] = Tile(sf::Vector2f(j, i));
        }
    }
    flagCount = 0;
    mineCount = 0;
    playStatus = PLAYING;
    numberOfMines = _numberOfMines;
    for (int i = 0; i < numberOfMines; i++) {
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;
        if (board[y][x].isMine) {
            i--;
        } else {
            board[y][x].isMine = true;
        }
    }
    Board = board;
    //setting neighbors
    /* 0 1 2
     * 3 tile 4
     * 5 6 7
     */
    for (int i = 0; i < dimensions.y; i++)
    {
        for (int j = 0; j < dimensions.x; j++)
        {
            std::array<Tile*, 8> neighbors{};
            //default to nullptr, the board is accessed through board[y][x]
            for (int k = 0; k < 8; k++)
            {
                neighbors[k] = nullptr;
            }
            //as long as the tile is not on the top edge or the left edge, set the 0th neighbor
            if (i != 0 && j != 0)
            {
                neighbors[0] = &Board[i - 1][j - 1];
            }
            //as long as the tile is not on the left edge, set the 1st neighbor
            if (i != 0)
            {
                neighbors[1] = &Board[i-1][j];
            }
            //as long as the tile is not on the right edge or the top edge, set the 2nd neighbor
            if (i != 0 && j != dimensions.x - 1)
            {
                neighbors[2] = &Board[i-1][j+1];
            }
            //as long as the tile is not on the left edge, set the 3rd neighbor
            if (j != 0)
            {
                neighbors[3] = &Board[i][j-1];
            }
            //as long as the tile is not on the right edge, set the 4th neighbor
            if (j != dimensions.x - 1)
            {
                neighbors[4] = &Board[i][j+1];
            }
            //as long as the tile is not on the bottom edge or the left edge, set the 5th neighbor
            if (i != dimensions.y - 1 && j != 0)
            {
                neighbors[5] = &Board[i+1][j-1];
            }
            //as long as the tile is not on the bottom edge, set the 6th neighbor
            if (i != dimensions.y - 1)
            {
                neighbors[6] = &Board[i+1][j];
            }
            //as long as the tile is not on the bottom edge or the right edge, set the 7th neighbor
            if (i != dimensions.y - 1 && j != dimensions.x - 1)
            {
                neighbors[7] = &Board[i+1][j+1];
            }
            Board[i][j].setNeighbors(neighbors);
        }
    }
    //set numbers based on neighbors
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            if (!Board[i][j].isMine) {
                for (int k = 0; k < 8; k++) {
                    if (Board[i][j].neighbors[k] != nullptr) {
                        if (Board[i][j].neighbors[k]->isMine) {
                            Board[i][j].number++;
                        }
                    }
                }
            }
        }
    }
    mineCount = numberOfMines;
}
GameState::GameState(const char* filepath){
    std::ifstream file(filepath);
    //the file is formatted as follows:
    /*
     * 100110101
     * 110101010
     * 101010101
     */
    //where 1 is a mine and 0 is not a mine
    std::vector<std::vector<int>> boardtemp;
    std::string line;
    while (std::getline(file, line))
    {
        if(line != "") {
            std::vector<int> row;
            for (int i = 0; i < line.length(); i++) {

                row.push_back(line[i] - '0');
            }
            boardtemp.push_back(row);
        }
    }
    dimensions = sf::Vector2i(boardtemp[0].size(), boardtemp.size());
    std::vector<std::vector<Tile>> board(dimensions.y, std::vector<Tile>(dimensions.x, Tile(sf::Vector2f(0, 0))));
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            board[i][j] = Tile(sf::Vector2f(j, i));
        }
    }
    flagCount = 0;
    mineCount = 0;
    playStatus = PLAYING;
    numberOfMines = 0;
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            if (boardtemp[i][j] == 1)
            {
                board[i][j].isMine = true;
                numberOfMines += 1;
            }
        }
    }
    Board = board;
    for (int i = 0; i < dimensions.y; i++)
    {
        for (int j = 0; j < dimensions.x; j++)
        {
            std::array<Tile*, 8> neighbors{};
            //default to nullptr, the board is accessed through board[y][x]
            for (int k = 0; k < 8; k++)
            {
                neighbors[k] = nullptr;
            }
            //as long as the tile is not on the top edge or the left edge, set the 0th neighbor
            if (i != 0 && j != 0)
            {
                neighbors[0] = &Board[i - 1][j - 1];
            }
            //as long as the tile is not on the left edge, set the 1st neighbor
            if (i != 0)
            {
                neighbors[1] = &Board[i-1][j];
            }
            //as long as the tile is not on the right edge or the top edge, set the 2nd neighbor
            if (i != 0 && j != dimensions.x - 1)
            {
                neighbors[2] = &Board[i-1][j+1];
            }
            //as long as the tile is not on the left edge, set the 3rd neighbor
            if (j != 0)
            {
                neighbors[3] = &Board[i][j-1];
            }
            //as long as the tile is not on the right edge, set the 4th neighbor
            if (j != dimensions.x - 1)
            {
                neighbors[4] = &Board[i][j+1];
            }
            //as long as the tile is not on the bottom edge or the left edge, set the 5th neighbor
            if (i != dimensions.y - 1 && j != 0)
            {
                neighbors[5] = &Board[i+1][j-1];
            }
            //as long as the tile is not on the bottom edge, set the 6th neighbor
            if (i != dimensions.y - 1)
            {
                neighbors[6] = &Board[i+1][j];
            }
            //as long as the tile is not on the bottom edge or the right edge, set the 7th neighbor
            if (i != dimensions.y - 1 && j != dimensions.x - 1)
            {
                neighbors[7] = &Board[i+1][j+1];
            }
            Board[i][j].setNeighbors(neighbors);
        }
    }
    //set numbers based on neighbors
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            if (!Board[i][j].isMine) {
                for (int k = 0; k < 8; k++) {
                    if (Board[i][j].neighbors[k] != nullptr) {
                        if (Board[i][j].neighbors[k]->isMine) {
                            Board[i][j].number++;
                        }
                    }
                }
            }
        }
    }
    mineCount = numberOfMines;
}
/*
 *     enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
 */
Tile* GameState::getTile(int x, int y) {
    return &Board[y][x];
}
int GameState::getFlagCount() {
    return flagCount;
}
int GameState::getMineCount() {
    return mineCount;
}
GameState::PlayStatus GameState::getPlayStatus() {
    return playStatus;
}
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    playStatus = _status;
}