#ifndef STATE_H
#define STATE_H

#include "Entities/player.h"
#include "Resource_Files/graphicssettings.h"

//forward declarations
class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
    //constructors/destructors
    StateData() {};

    //variables
    float gridSize;
    sf::RenderWindow *window;
    GraphicsSettings *gfxSettings;
    std::map<std::string, int> *supportedKeys;
    std::stack<State*> *states;
};

class State
{
private:

protected:
    //variables
    StateData *stateData;
    std::stack<State*> *states;
    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    //resources
    std::map<std::string, sf::Texture> textures;

    //fucntions
    virtual void initKeybinds() = 0;

public:
    //constructors/destructors
    State(StateData *state_data);
    virtual ~State();

    //getters
    const bool &getQuit() const;
    bool getKeytime();

    //functions
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePositions();
    virtual void updateKeytime(const float &dt);
    virtual void updateInput(const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

#endif // STATE_H
