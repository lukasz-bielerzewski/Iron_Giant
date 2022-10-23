#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "States/gamestate.h"
#include "Resource_Files/gui.h"
#include "States/editorstate.h"
#include "States/settingsstate.h"

//forward declarations
class GameState;
class Gui;
class EditorState;
class SettingsState;

class MainMenuState : public State
{
private:
    //variables
    sf::Texture backgroundTexture;
    sf::Font font;
    sf::RectangleShape background;

    std::map<std::string, gui::Button*> buttons;

    //intitializing fucntions
    void initBackground();
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    //constructors/destructors
    MainMenuState(StateData *state_data);
    virtual ~MainMenuState();

    //functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // MAINMENUSTATE_H
