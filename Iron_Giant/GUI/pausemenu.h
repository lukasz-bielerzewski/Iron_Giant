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
    PauseMenu(sf::VideoMode &vm, sf::Font &font);
    virtual ~PauseMenu();

    //getters
    std::map<std::string, gui::Button*> &getButtons();

    //functions
    bool isButtonPressed(const std::string key);
    void addButton(const std::string key, const float y, const float width, const float height, const unsigned char_size, const std::string text);
    void update(const sf::Vector2i &mousePosWindow);
    void render(sf::RenderTarget &target);
};

#endif // PAUSEMENU_H
