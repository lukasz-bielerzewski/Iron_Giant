#include "Source_Files/pch.h"
#include "game.h"

//static functions

//initializing functions
void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;

    this->gridSize = 50.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;

}

void Game::initWindow()
{
    if(this->gfxSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                            this->gfxSettings.title,
                                            sf::Style::Fullscreen,
                                            this->gfxSettings.contextSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                            this->gfxSettings.title,
                                            sf::Style::Titlebar | sf::Style::Close,
                                            this->gfxSettings.contextSettings);
    }

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(gfxSettings.vsync);
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");

    if(ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while(ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}

//constructors/destructors
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//functions

//regular
void Game::endApplication()
{

}

//updates
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while(this->window->pollEvent(this->sfEvent))
    {
        if(this->sfEvent.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if(!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if(this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }
}

//renders
void Game::render()
{
    this->window->clear();

    if(!this->states.empty())
    {
        this->states.top()->render();
    }

    this->window->display();
}

//core
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
