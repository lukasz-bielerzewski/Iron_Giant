#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "States/state.h"
#include "GUI/pausemenu.h"
#include "Map/tilemap.h"
#include "GUI/playergui.h"
#include "Entities/enemy.h"
#include "Resource_Files/gui.h"

//forward declarations
class State;
class PauseMenu;
class TileMap;
class Player;
class Enemy;
class PlayerGUI;
class Gui;

class GameState : public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu *pmenu;

    Player *player;
    PlayerGUI *playerGUI;

    Enemy *enemy;

    TileMap *tileMap;

    float mx;
    float my;
    bool damaged;
    bool damaging;

    gui::Button *endButton;
    sf::Text endText;

    //fucntions
    void initDefferedRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayer();
    void initPlayerGUI();
    void initEnemy();
    void initTileMap();
    void initGui();

public:
    //constructors/destructors
    GameState(StateData *state_data);
    virtual ~GameState();

    //functions
    void updateView(const float &dt);
    void updateInput(const float &dt);
    void updatePlayerInput(const float &dt);
    void updateEnemyMovement(const float &dt);
    void updateEntitiesCollisions();
    void updatePlayerGUI(const float &dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float &dt);
    void updateGui();
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // GAMESTATE_H
