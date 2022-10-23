#include "Source_Files/pch.h"
#include "settingsstate.h"

//initializing functions
void SettingsState::initBackground()
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

void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
    if(!this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf"))
    {
        throw("ERROR::MAIN_MENU_STATE::COUL_NOT_LOAD_FONT");
    }
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
    this->buttons["BACK"] = new gui::Button(
                1040.f, 880.f, 350.f, 70.f,
                &this->font, "Back", 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));

    this->buttons["APPLY"] = new gui::Button(
                590.f, 880.f, 350.f, 70.f,
                &this->font, "Apply", 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));

    std::vector<std::string> modes_str;

    for(auto &i: this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }

    this->dropdownLists["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
    this->optionsText.setFont(font);

    this->optionsText.setPosition(sf::Vector2f(590.f, 350.f));

    this->optionsText.setCharacterSize(25);

    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

    this->optionsText.setString(
                "Resolution: \n\n\nFullscreen: \n\n\nVsync: \n\n\nAntialiasing:"
);
}

//constructors/destructors
SettingsState::SettingsState(StateData *state_data)
    : State(state_data)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->initText();
}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    auto it2 = this->dropdownLists.begin();
    for(it2 = this->dropdownLists.begin(); it2 != this->dropdownLists.end(); ++it2)
    {
        delete it2->second;
    }
}

//functions
void SettingsState::updateInput(const float &dt)
{

}

void SettingsState::updateGui(const float &dt)
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if(this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }

    if(this->buttons["APPLY"]->isPressed())
    {
        this->stateData->gfxSettings->resolution = this->modes[this->dropdownLists["RESOLUTION"]->getActiveElementId()];

        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
    }

    for(auto &it2 : this->dropdownLists)
    {
        it2.second->update(this->mousePosView, dt);
    }
}

void SettingsState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget &target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }

    for(auto &it2 : this->dropdownLists)
    {
        it2.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget *target)
{
    if(!target)
    {
        target = this->window;
    }

    target->draw(this->background);

    this->renderGui(*target);

    target->draw(this->optionsText);

    //Narzędzie do pozycjonowania
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x + 25, this->mousePosView.y + 25);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}

