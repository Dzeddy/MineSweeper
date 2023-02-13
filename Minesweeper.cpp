/*
 * Global Functions
A proper implementation will also include the following functions in global scope (not in a class). Except for
main(), these functions should be prototyped in the minesweeper.h header file:
int launch()
This method is invoked directly by main() and is responsible for the game’s launch. It should be possible to
directly invoke this function after including the submitted source and header files in the test suite.
void restart()
Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
The new state should be a default game state (25x16 with 50 randomly placed mines).
void render()
Draws the all UI elements according to the current gameState and debug mode.
void toggleDebugMode()
Flips the debug mode on/off. (Debug mode should initially be off/false.)
bool getDebugMode()
Returns the true if debug mode is active, and false otherwise.
 *
 */
#include "Minesweeper.h"
#include "Toolbox.h"
#include <iostream>
int main(){return launch();}
int launch(){
    Toolbox& toolbox = Toolbox::getInstance();
    render();
    return 0;
}

void restart(){
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState();
}
void render() {
    Toolbox &toolbox = Toolbox::getInstance();
    while (toolbox.window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePosition;
        //get tile position, tiles are 32x32
        sf::Vector2i tilePosition;
        sf::Vector2i tileIndex;
        while (toolbox.window.pollEvent(event)) {
            mousePosition = sf::Mouse::getPosition(toolbox.window);
            if (event.type == sf::Event::Closed) {
                toolbox.window.close();
            }
            if (mousePosition.x >= 500 && mousePosition.x <= 500 + 64 && mousePosition.y >= toolbox.dimensions.y && mousePosition.y <= toolbox.dimensions.y + 64 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                toggleDebugMode();
                mousePosition = sf::Vector2i(0, 0);
            }
            if (mousePosition.x >= 300 && mousePosition.x <= 300 + 64 && mousePosition.y >= toolbox.dimensions.y && mousePosition.y <= toolbox.dimensions.y + 64 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                restart();
                toolbox.newGameButton->onClick();
                mousePosition = sf::Vector2i(0, 0);
            }
            if (mousePosition.x >= 564 && mousePosition.x <= 564 + 64 && mousePosition.y >= toolbox.dimensions.y && mousePosition.y <= toolbox.dimensions.y + 64 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePosition = sf::Vector2i(0, 0);
                toolbox.testButton1->onClick();
            }
            if (mousePosition.x >= 628 && mousePosition.x <= 628 + 64 && mousePosition.y >= toolbox.dimensions.y && mousePosition.y <= toolbox.dimensions.y + 64 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePosition = sf::Vector2i(0, 0);
                toolbox.testButton2->onClick();
            }
            toolbox.processEvent(event);
        }
        toolbox.window.clear();
        toolbox.window.draw(sf::Sprite(toolbox.gameBoardSprite.getTexture()));
        toolbox.window.draw(*toolbox.sprites["debug.png"], sf::Transform().translate(500, toolbox.dimensions.y));
        toolbox.window.draw(*toolbox.sprites["test_1.png"], sf::Transform().translate(564, toolbox.dimensions.y));
        toolbox.window.draw(*toolbox.sprites["test_2.png"], sf::Transform().translate(628, toolbox.dimensions.y));
        //draw face_happy unless toolbox gamestate playstatus is lost or won
        if (toolbox.gameState->getPlayStatus() == GameState::PlayStatus::LOSS) {
            toolbox.window.draw(*toolbox.sprites["face_lose.png"], sf::Transform().translate(300, toolbox.dimensions.y));
        } else if (toolbox.gameState->getPlayStatus() == GameState::PlayStatus::WIN) {
            toolbox.window.draw(*toolbox.sprites["face_win.png"], sf::Transform().translate(300, toolbox.dimensions.y));
        } else {
            toolbox.window.draw(*toolbox.sprites["face_happy.png"], sf::Transform().translate(300, toolbox.dimensions.y));
        }
        //draw mines left
        //first digit: either 0 or 10 depending on if minesleft is positive or negative
        //second digit: minesleft % 10
        //third digit: minesleft / 10
        std::string digitString = "digit_";
        toolbox.window.draw(toolbox.minesLeft >= 0 && toolbox.minesLeft < 100 ? *toolbox.sprites["digit_0"] : *toolbox.sprites["digit_10"],sf::Transform().translate(0, toolbox.dimensions.y));
        if(toolbox.minesLeft > 100) {
            digitString += (*toolbox.minesLeftText)[0];
            toolbox.window.draw(*toolbox.sprites[digitString], sf::Transform().translate(0, toolbox.dimensions.y));
        }
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[1];
        toolbox.window.draw(*toolbox.sprites[digitString], sf::Transform().translate(21, toolbox.dimensions.y));
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[2];
        toolbox.window.draw(*toolbox.sprites[digitString], sf::Transform().translate(42, toolbox.dimensions.y));
        toolbox.window.display();
    }
    //delete toolbox singleton
}
void toggleDebugMode(){
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.debugButton->onClick();
}