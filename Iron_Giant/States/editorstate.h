#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "state.h"
#include "Resource_Files/gui.h"
#include "GUI/pausemenu.h"
#include "Map/tilemap.h"

//forward declarations
class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState : public State
{
private:
    //variables
    sf::Font font;
    PauseMenu *pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape selectorRect;

    //intitializing fucntions
    void initBackground();
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

public:
    //constructors/destructors
    EditorState(StateData *state_data);
    virtual ~EditorState();

    //functions
    void updateInput(const float &dt);
    void updateButtons();
    void updateGui();
    void updatePauseMenuButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget &target);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // EDITORSTATE_H
