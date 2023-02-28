#include "Source_Files/pch.h"
#include "gamestate.h"

//initializing functions
void GameState::initDefferedRender()
{
    this->renderTexture.create(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width),
                                    static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->view.setCenter(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
                                      static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f));
}

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

    if(!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
    {
        throw("ERROR::GAME_STATE::COULD_NOT_LOAD_ENEMY_TEXTURE");
    }
}

void GameState::initPauseMenu()
{
    const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

    this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

    this->pmenu->addButton("QUIT", gui::p2pY(74.074f, vm), gui::p2pX(18.22917f, vm), gui::p2pY(6.481f, vm), gui::calcCharSize(14, vm), "Quit");
}

void GameState::initPlayer()
{
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI()
{
    this->playerGUI = new PlayerGUI(this->player);
}

void GameState::initEnemy()
{
    this->mx = static_cast<float>((std::rand() % 3) - 1);
    this->my = static_cast<float>((std::rand() % 3) - 1);
    this->enemy = new Enemy(400, 400, this->textures["ENEMY_SHEET"], *this->player);
}

void GameState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 50, 50, "Resources/Images/Tiles/tilesheet3.png");
    this->tileMap->loadFromFile("text.igmp");
}

void GameState::initGui()
{
    const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

    this->endButton = new gui::Button(
                static_cast<float>(vm.width) / 2.f - gui::p2pX(18.22917f, vm) / 2.f, gui::p2pY(74.074f, vm), gui::p2pX(18.22917f, vm), gui::p2pY(6.481f, vm),
                &this->font, "End game", gui::calcCharSize(14, vm),
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));

    this->endText.setCharacterSize(gui::calcCharSize(200, vm));
    this->endText.setFont(this->font);
    this->endText.setString("END");
    this->endText.setPosition(static_cast<float>(vm.width) / 2.f - this->endText.getGlobalBounds().width / 2.f, gui::p2pY(30.f, vm));
}

//contructors/destructors
GameState::GameState(StateData *state_data)
    : State(state_data)
{
    this->initDefferedRender();
    this->initView();
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initGui();

    this->initPlayer();
    this->initPlayerGUI();
    this->initEnemy();
    this->initTileMap();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    this->damaged = false;
    this->damaging = false;
}

GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->playerGUI;
    delete this->enemy;
    delete this->tileMap;
    delete this->endButton;
}

//update functions
void GameState::updateView(const float &dt)
{
    this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

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

void GameState::updateEnemyMovement(const float &dt)
{
    this->enemy->move(mx, my, dt);

    if(this->enemy->collision || (this->mx == 0.f && this->my == 0.f))
    {
        this->mx = static_cast<float>((std::rand() % 3) - 1);
        this->my = static_cast<float>((std::rand() % 3) - 1);
        this->enemy->collision = false;
    }
}

void GameState::updateEntitiesCollisions()
{
    if(this->enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->damaged == false)
    {
        this->player->loseHp(2);
        this->damaged = true;
    }

    if(!this->enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()))
    {
        this->damaged = false;
    }

    if((this->player->attackHitboxLeft.getGlobalBounds().intersects(this->enemy->getGlobalBounds()) && this->player->attacking && this->damaging == false)
            || (this->player->attackHitboxRight.getGlobalBounds().intersects(this->enemy->getGlobalBounds()) && this->player->attacking && this->damaging == false))
    {
        this->damaging = true;
        this->player->gainExp(50);
        this->enemy->setPosition(static_cast<float>((std::rand() % 200) + 300), static_cast<float>((std::rand() % 200) + 300));
        this->mx = static_cast<float>((std::rand() % 3) - 1);
        this->my = static_cast<float>((std::rand() % 3) - 1);
        this->enemy->speed += 10.f;
    }

    if(!this->player->attackHitboxLeft.getGlobalBounds().intersects(this->enemy->getGlobalBounds()) && !this->player->attacking
            && !this->player->attackHitboxRight.getGlobalBounds().intersects(this->enemy->getGlobalBounds()))
    {
        this->damaging = false;
    }
}

void GameState::updatePlayerGUI(const float &dt)
{
    this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
}

void GameState::updateTileMap(const float &dt)
{
    this->tileMap->update();
    this->tileMap->updateCollision(this->player, dt);
    this->tileMap->updateCollision(this->enemy, dt);
}

void GameState::updateGui()
{
    this->endButton->update(this->mousePosWindow);

    if(this->endButton->isPressed())
    {
        this->endState();
    }
}

void GameState::update(const float &dt)
{
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    if(!this->player->dead)
    {
        this->updateInput(dt);
    }

    if(!this->paused)
    {
        this->updateView(dt);

        if(!this->player->dead)
        {
            this->updatePlayerInput(dt);
        }

        this->updateEnemyMovement(dt);

        if(!this->player->dead)
        {
            this->updateEntitiesCollisions();
        }

        this->updateTileMap(dt);

        this->player->update(dt);

        this->playerGUI->update(dt);

        this->enemy->update(dt);
    }
    else if(!this->player->dead)
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
    if(this->player->dead)
    {
        this->updateGui();
    }
}

//render functions
void GameState::render(sf::RenderTarget *target)
{
    if(!target)
    {
        target = this->window;
    }

    this->renderTexture.clear();

    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

    this->player->render(this->renderTexture);

    this->enemy->render(this->renderTexture);

    this->tileMap->renderDeferred(this->renderTexture);

    this->renderTexture.setView(this->renderTexture.getDefaultView());
    this->playerGUI->render(this->renderTexture);

    if(this->paused && !this->player->dead)
    {
        //this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pmenu->render(this->renderTexture);
    }

    if(this->player->getAttributeComponent()->hp == 0)
    {
        this->player->dead = true;
        this->player->stopVelocity();

        this->endButton->render(this->renderTexture);
        this->renderTexture.draw(this->endText);
    }

    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}
