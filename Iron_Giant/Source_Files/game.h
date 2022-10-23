#ifndef GAME_H
#define GAME_H

#include "States/gamestate.h"
#include "States/mainmenustate.h"

//forward declarations
class GameState;
class MainMenuState;

class Game
{
private:
    //variables
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    float gridSize;

    //initailization functions
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initStateData();
    void initStates();
    void initKeys();

public:
    //constructors/destructors
    Game();
    virtual ~Game();

    //functions

    //regular
    void endApplication();

    //updates
    void updateDt();
    void updateSFMLEvents();
    void update();

    //renders
    void render();

    //core
    void run();
};

#endif // GAME_H
