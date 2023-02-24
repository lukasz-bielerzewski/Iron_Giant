#include "Source_Files/pch.h"
#include "pausemenu.h"

//contructors/destructors
PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font)
    : font(font)
{
    this->background.setSize(sf::Vector2f(
                                 static_cast<float>(window.getSize().x),
                                 static_cast<float>(window.getSize().y)
                                 )
                             );

    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    this->container.setSize(sf::Vector2f(
                                static_cast<float>(window.getSize().x) / 4.f,
                                static_cast<float>(window.getSize().y) - 120.f
                                )
                            );

    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
                                60.f);

    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(60);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
                               this->container.getPosition().y + 40.f);
}

PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

//getters
std::map<std::string, gui::Button *> &PauseMenu::getButtons()
{
    return this->buttons;
}

//functions
bool PauseMenu::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
    float width = 350.f;
    float height = 70.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new gui::Button(
                x, y, width, height,
                &this->font, text, 14,
                sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(100, 100, 100, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 250, 255), sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2i &mousePosWindow)
{
    for(auto &i: this->buttons)
    {
        i.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);

    for(auto &it : buttons)
    {
        it.second->render(target);
    }

    target.draw(this->menuText);
}
