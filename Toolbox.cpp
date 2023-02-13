//
// Created by Dylan on 12/1/2022.
//

#include "Toolbox.h"
/*class Toolbox {
public:
    static Toolbox& getInstance();
    sf::RenderWindow window;
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
private:
    Toolbox();
};*/
#include <iostream>
Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}
Toolbox::Toolbox(){
    std::string filenames[] = {
            "debug.png",
            "digits.png",
            "face_happy.png",
            "face_lose.png",
            "face_win.png",
            "flag.png",
            "mine.png",
            "number_1.png",
            "number_2.png",
            "number_3.png",
            "number_4.png",
            "number_5.png",
            "number_6.png",
            "number_7.png",
            "number_8.png",
            "test_1.png",
            "test_2.png",
            "Test_3.png",
            "tile_hidden.png",
            "tile_revealed.png"
    };
    //load sprites into map
    window.create(sf::VideoMode(800, 600), "Minesweeper - <Dylan Zhuang>");
    //allocate memory for sprites
    for (auto & filename : filenames) {
        sf::Texture *texture;
        texture = new sf::Texture();
        texture->loadFromFile("./images/" + filename);
        sprites[filename] = new sf::Sprite(*texture);
    }
    //sf::Sprite temporary = sf::Sprite(textures["tile_hidden.png"]);
    //testSpriteonWindow(temporary);
    for (int i = 0; i < 11; i++) {
        sf::Texture *texture;
        texture = new sf::Texture();
        texture->loadFromFile("./images/digits.png", sf::IntRect(i * 21, 0, 21, 32));
        sprites["digit_" + std::to_string(i)] = new sf::Sprite(*texture);
    }
    //create new tile sprite, numbered_0, numbered_1, etc.
    //create new tile sprite, flagged tile and mine tile. flagged tile is a hidden tile with a flag on it, mine tile is a revealed tile with a mine on it
    for(int i = 1; i < 9; i++)
    {
        //load revealed tile
        sf::RenderTexture texture;
        sf::Sprite sprite;
        sf::Texture *texture2;
        texture.create(32, 32);
        texture.draw(*sprites["tile_revealed.png"]);
        texture.draw(*sprites["number_" + std::to_string(i) + ".png"]);
        //NOTE: graphics are traditionally done differently in 2D and 3D, resulting in the Image from a Texture being upside down; make sure to flip it horizontally before returning it!
        texture.display();
        texture2 = new sf::Texture(texture.getTexture());
        texture2->loadFromImage(texture.getTexture().copyToImage());
        sprites["numbered_" + std::to_string(i)] = new sf::Sprite(*texture2);
    }
    //create flagged tile
    sf::RenderTexture texture;
    texture.create(32, 32);
    texture.draw(*sprites["tile_hidden.png"]);
    texture.draw(*sprites["flag.png"]);
    texture.display();
    sf::Texture temp;
    temp.loadFromImage(texture.getTexture().copyToImage());
    sf::Texture *allocatedTexture = new sf::Texture(temp);
    sprites["tile_flagged"] = new sf::Sprite(*allocatedTexture);
    //create mine tile
    sf::RenderTexture texture2;
    texture2.create(32, 32);
    texture2.draw(*sprites["tile_hidden.png"]);
    texture2.draw(*sprites["mine.png"]);
    texture2.display();
    sf::Texture temp2;
    temp2.loadFromImage(texture2.getTexture().copyToImage());
    sf::Texture *allocatedTexture2 = new sf::Texture(temp2);
    sprites["tile_mine"] = new sf::Sprite(*allocatedTexture2);
    gameState = new GameState();
    //draw all tiles from gamestate vector<vector<Tile>> to window
    //create gameboardsprite with size of gameboard dimensions * 32
    gameBoardSprite.create(gameState->dimensions.x * 32, gameState->dimensions.y * 32);
    //draw all tiles to gameboardsprite
    debugButton = new Button(sf::Vector2f(0, gameState->dimensions.y * 32),debugMode());
    debugButton->setSprite(sprites["debug.png"]);
    testButton1 = new Button(sf::Vector2f(32, gameState->dimensions.y * 32), TestButton1());
    testButton1->setSprite(sprites["test_1.png"]);
    testButton2 = new Button(sf::Vector2f(64, gameState->dimensions.y * 32), TestButton2());
    testButton2->setSprite(sprites["test_2.png"]);
    newGameButton = new Button(sf::Vector2f(96, gameState->dimensions.y * 32), NewGameButton());
    //draw debug button to window
    //testSpriteonWindow(*debugButton->getSprite());
    for(int i = 0; i < gameState->dimensions.x; i++)
    {
        for(int j = 0; j < gameState->dimensions.y; j++)
        {
            //draw tile to gameboardsprite
            gameBoardSprite.draw(*sprites["tile_hidden.png"], sf::Transform().translate(i * 32, j * 32));
        }
    }
    dimensions = sf::Vector2i(gameState->dimensions.x * 32, gameState->dimensions.y * 32);
    gameBoardSprite.display();
    minesLeft = gameState->mineCount - gameState->flagCount;
    //allocate string of legnth 3 to mineslefttext
    //free memory
    std::string minesLeftTemp = std::to_string(minesLeft);
    while(minesLeftTemp.length() < 3){
        minesLeftTemp = "0" + minesLeftTemp;
    }
    minesLeftText = new std::string(minesLeftTemp);
    *minesLeftText = minesLeftTemp;
}

void Toolbox::testSpriteonWindow(sf::Sprite sprite) {
    //reset window isOpen
    sf::RenderWindow newWindow;
    newWindow.create(sf::VideoMode(800, 600), "Minesweeper");
    newWindow.draw(sprite);
    while(newWindow.isOpen())
    {
        sf::Event event;
        while(newWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                newWindow.close();
        }
        newWindow.clear();
        newWindow.draw(sprite);
        newWindow.display();
    }
}

std::function<void(void)> Toolbox::debugMode(){
    return [this]() {
        isDebug = !isDebug;
        //iterate through board and reveal all tiles
        for(int i = 0; i < gameState->dimensions.x; i++)
        {
            for(int j = 0; j < gameState->dimensions.y; j++)
            {
                Tile* tile = &gameState->Board[j][i];
                if (tile->isMine) {
                    if(isDebug) {
                        gameBoardSprite.draw(*sprites["tile_mine"], sf::Transform().translate(i * 32, j * 32));
                    }
                    //draw hidden tile
                    else {
                        gameBoardSprite.draw(*sprites["tile_hidden.png"], sf::Transform().translate(i * 32, j * 32));
                    }
                }
            }
        }
    };
}
void Toolbox::processEvent(sf::Event event) {
    sf::Vector2i mousePosition;
    //get tile position, tiles are 32x32
    sf::Vector2i tilePosition;
    sf::Vector2i tileIndex;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && gameState->playStatus == GameState::PLAYING) {
        mousePosition = sf::Mouse::getPosition(window);
        tilePosition = sf::Vector2i(mousePosition.x / 32, mousePosition.y / 32);
        tileIndex = sf::Vector2i(tilePosition.x, tilePosition.y);
        //get tile from gamestate
        //check if tileindex is in bounds
        if (tileIndex.x < gameState->dimensions.x && tileIndex.y < gameState->dimensions.y) {
            Tile *tile = &gameState->Board[tileIndex.y][tileIndex.x];
            //if tile is hidden, reveal it
            if (tile->getState() == Tile::HIDDEN) {
                //if tile is a mine, end game
                if (tile->isMine) {
                    //end game
                    //draw mine tile
                    tile->setState(Tile::EXPLODED);
                    tile->draw();
                    //set gamestate to lost
                    gameState->setPlayStatus(GameState::LOSS);
                } else {
                    //draw revealed if number = 0
                    if (tile->number == 0) {
                        tile->setState(Tile::REVEALED);
                        tile->draw();
                        tile->onClickLeft();
                        //revealneighbors
                        tile->revealNeighbors();
                    } else if (!tile->isMine) {
                        //draw numbered tile
                        tile->setState(Tile::REVEALED);
                        tile->draw();
                    }
                }

                //reset variables
                tile = nullptr;
            }
            //iterate through all tiles, revealing all tiles that are of "revealed" state
            for (int i = 0; i < gameState->dimensions.x; i++) {
                for (int j = 0; j < gameState->dimensions.y; j++) {
                    Tile *tile = &gameState->Board[j][i];
                    tile->draw();
                }
            }
            //if clicked on debug button, toggle debug mode (64x64 button size)
        }
        mousePosition = sf::Vector2i(0, 0);
        tilePosition = sf::Vector2i(0, 0);
        tileIndex = sf::Vector2i(0, 0);
        gameBoardSprite.display();
    }else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && gameState->playStatus == GameState::PLAYING){
        if (tileIndex.x < gameState->dimensions.x && tileIndex.y < gameState->dimensions.y) {
            mousePosition = sf::Mouse::getPosition(window);
            tilePosition = sf::Vector2i(mousePosition.x / 32, mousePosition.y / 32);
            tileIndex = sf::Vector2i(tilePosition.x, tilePosition.y);
            //get mouse position
            tilePosition *= 32;
            //get tile from gamestate
            Tile *tile = &gameState->Board[tileIndex.y][tileIndex.x];
            //if tile is hidden, reveal it
            if (tile->getState() == Tile::HIDDEN) {
                //draw flagged tile
                gameBoardSprite.draw(*sprites["tile_flagged"],
                                     sf::Transform().translate(tilePosition.x, tilePosition.y));
                gameState->flagCount++;
                tile->onClickRight();
            } else if (tile->getState() == Tile::FLAGGED) {
                //draw hidden tile
                gameBoardSprite.draw(*sprites["tile_hidden.png"],
                                     sf::Transform().translate(tilePosition.x, tilePosition.y));
                gameState->flagCount--;
                tile->onClickRight();
            }
            //reset variables
            tile = nullptr;
            mousePosition = sf::Vector2i(0, 0);
            tilePosition = sf::Vector2i(0, 0);
            tileIndex = sf::Vector2i(0, 0);
            gameBoardSprite.display();
        }
    }
    minesLeft = gameState->mineCount - gameState->flagCount;
    //allocate string of legnth 3 to mineslefttext
    std::string minesLeftTemp = std::to_string(minesLeft);
    while(minesLeftTemp.length() < 3){
        minesLeftTemp = "0" + minesLeftTemp;
    }
    *minesLeftText = minesLeftTemp;
    //check if game is won
    if(checkIfWon()){
        gameState->setPlayStatus(GameState::WIN);
    }
}

sf::Sprite Toolbox::getSprite(std::string spritekey){
    return *sprites[spritekey];
}
void Toolbox::redraw(){
    for(int i = 0; i < gameState->dimensions.x; i++)
    {
        for(int j = 0; j < gameState->dimensions.y; j++)
        {
            //draw tile to gameboardsprite
            gameState->Board[j][i].draw();
        }
    }
}

std::function<void(void)> Toolbox::TestButton1() {
    return [this](){
        //clear board
        delete gameState;
        gameState = new GameState("./boards/testboard1.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        redraw();
    };
}

std::function<void(void)> Toolbox::TestButton2() {
    return [this](){
        //clear board
        delete gameState;
        gameState = new GameState("./boards/testboard2.brd");
        gameState->setPlayStatus(GameState::PlayStatus::PLAYING);
        redraw();
    };
}
Toolbox::~Toolbox() {
    delete gameState;
    delete minesLeftText;
    for(auto &sprite : sprites){
        delete sprite.second->getTexture();
        delete sprite.second;
    }
}
std::function<void(void)> Toolbox::NewGameButton() {
    return [this](){
        //clear board
        redraw();
    };
}

bool Toolbox::checkIfWon() {
int revealedTiles = 0;
    for(int i = 0; i < gameState->dimensions.x; i++)
    {
        for(int j = 0; j < gameState->dimensions.y; j++)
        {
            Tile *tile = &gameState->Board[j][i];
            if(tile->getState() == Tile::REVEALED){
                revealedTiles++;
            }
        }
    }
    if(revealedTiles == gameState->dimensions.x * gameState->dimensions.y - gameState->mineCount){
        return true;
    }
    return false;
}