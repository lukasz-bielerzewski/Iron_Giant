#include "Source_Files/pch.h"
#include "gamestate.h"

//initializing functions
void GameState::initKeybinds()
{
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if(ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while(ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void GameState::initFonts()
{
    if(!this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf"))
    {
        throw("ERROR::MAIN_MENU_STATE::COUL_NOT_LOAD_FONT");
    }
}

void GameState::initTextures()
{
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player_sheet.png"))
    {
        throw("ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE");
    }
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayer()
{
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tilesheet1.png");
}

//contructors/destructors
GameState::GameState(StateData *state_data)
    : State(state_data)
{
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayer();
    this->initTileMap();
}

GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->tileMap;
}

//update functions
void GameState::updateInput(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if(!this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unpauseState();
        }
    }
}

void GameState::updatePlayerInput(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        this->player->move(-1.f, 0.f, dt);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(1.f, 0.f, dt);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, dt);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, dt);
    }
}

void GameState::updatePauseMenuButtons()
{
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
}

void GameState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateKeytime(dt);
    this->updateInput(dt);

    if(!this->paused)
    {
        this->updatePlayerInput(dt);

        this->player->update(dt);
    }
    else
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

//render functions
void GameState::render(sf::RenderTarget *target)
{
    if(!target)
    {
        target = this->window;
    }

    //this->map.render(*target);

    this->player->render(*target);

    if(this->paused)
    {
        this->pmenu->render(*target);
    }
}
