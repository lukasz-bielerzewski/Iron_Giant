#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Resource_Files/gui.h"

//forward declarations
class Gui;

class PauseMenu
{
private:
    sf::Font &font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

public:
    //constructors/destructors
    PauseMenu(sf::RenderWindow &window, sf::Font &font);
    virtual ~PauseMenu();

    //getters
    std::map<std::string, gui::Button*> &getButtons();

    //functions
    bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float y, const std::string text);
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
};

#endif // PAUSEMENU_H
