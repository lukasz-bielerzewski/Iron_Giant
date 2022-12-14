#include "Source_Files/pch.h"
#include "mainmenustate.h"

//initializing functions
void MainMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(
                                 static_cast<float>(this->window->getSize().x),
                                 static_cast<float>(this->window->getSize().y)
                                 )
                             );

    if(!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/menu_background.jpg"))
    {
        throw("ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE");
    }

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts()
{
    if(!this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf"))
    {
        throw("ERROR::MAIN_MENU_STATE::COUL_NOT_LOAD_FONT");
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new gui::Button(
                200.f, 275.f, 350.f, 70.f,
                &this->font, "Start game", 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));

    this->buttons["SETTINGS_STATE"] = new gui::Button(
                200.f, 400.f, 350.f, 70.f,
                &this->font, "Settings", 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));

    this->buttons["EDITOR_STATE"] = new gui::Button(
                200.f, 525.f, 350.f, 70.f,
                &this->font, "Editor", 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));

    this->buttons["EXIT_STATE"] = new gui::Button(
                200.f, 850.f, 350.f, 70.f,
                &this->font, "Quit", 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));
}

//contructors/destructors
MainMenuState::MainMenuState(StateData *state_data)
    : State(state_data)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

//functions
void MainMenuState::updateInput(const float &dt)
{

}

void MainMenuState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if(this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->stateData));
    }

    if(this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->states->push(new SettingsState(this->stateData));
    }

    if(this->buttons["EDITOR_STATE"]->isPressed())
    {
        this->states->push(new EditorState(this->stateData));
    }

    if(this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget &target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if(!target)
    {
        target = this->window;
    }

    target->draw(this->background);

    this->renderButtons(*target);

    //Narz??dzie do pozycjonowania
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x + 25, this->mousePosView.y + 25);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}
