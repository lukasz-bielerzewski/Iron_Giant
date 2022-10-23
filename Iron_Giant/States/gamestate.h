#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "States/state.h"
#include "GUI/pausemenu.h"
#include "Map/tilemap.h"

//forward declarations
class State;
class PauseMenu;
class TileMap;

class GameState : public State
{
private:
    sf::Font font;
    PauseMenu *pmenu;

    Player *player;

    TileMap *tileMap;

    //fucntions
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayer();
    void initTileMap();

public:
    //constructors/destructors
    GameState(StateData *state_data);
    virtual ~GameState();

    //functions
    void updateInput(const float &dt);
    void updatePlayerInput(const float &dt);
    void updatePauseMenuButtons();
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // GAMESTATE_H
