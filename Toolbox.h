//
// Created by Dylan on 12/1/2022.
//

#ifndef PROJECT4V2_TOOLBOX_H
#define PROJECT4V2_TOOLBOX_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Tile.h"
#include "GameState.h"
#include <map>
/*
 * Toolbox Class
A toolbox class is often used to contain variables that would otherwise be accessed throughout an application;
it is a mechanism to avoid truly global variables. The Toolbox class will be a singleton (class with only one
instance) and will contain at least the following attributes and methods:
public sf::RenderWindow window; // SFML application window
public GameState* gameState; // Primary game state representation
public Button* debugButton; // Reveals mines in debug mode
public Button* newGameButton; // Resets / starts new game
public Button* testButton1; // Loads test board #1
public Button* testButton2; // Loads test board #2
public static Toolbox& getInstance()
Returns a reference to the singular Toolbox instance.
private ToolBox()
Default constructor; should be accessible only from within the class itself. This method initializes the buttons,
window, game board, and any other elements necessary to play the game.
 */
class Toolbox {
public:
    std::map<std::string, sf::Sprite*> sprites;
    static Toolbox& getInstance();
    sf::RenderWindow window;
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    void testSpriteonWindow(sf::Sprite sprite);
    sf::RenderTexture gameBoardSprite;
    std::function<void(void)> debugMode();
    void processEvent(sf::Event event);
    sf::Vector2i dimensions;
    sf::Sprite getSprite(std::string spritekey);
    int minesLeft;
    std::string *minesLeftText;
    bool isDebug = false;
    void redraw();
    std::function<void(void)> TestButton1();
    std::function<void(void)> TestButton2();
    std::function<void(void)> NewGameButton();
    bool checkIfWon();
private:
    ~Toolbox();
    Toolbox();
    friend class GameState;
    friend class Tile;
};


#endif //PROJECT4V2_TOOLBOX_H
