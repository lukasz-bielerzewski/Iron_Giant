#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "state.h"
#include "Resource_Files/gui.h"

//forward declarations
class State;
class Gui;

class SettingsState : public State
{
private:
    //variables
    sf::Texture backgroundTexture;
    sf::Font font;
    sf::RectangleShape background;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropdownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //intitializing fucntions
    void initBackground();
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();

public:
    //constructors/destructors
    SettingsState(StateData *state_data);
    virtual ~SettingsState();

    //getters

    //functions
    void updateInput(const float &dt);
    void updateGui(const float &dt);
    void update(const float &dt);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // SETTINGSSTATE_H
