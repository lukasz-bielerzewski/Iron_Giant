#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Entities/player.h"

class Player;

class PlayerGUI
{
private:
    //variables
    Player *player;

    sf::Font font;
    float hpBarMaxWidth;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;

    //initialization functions
    void initFont();
    void initHpBar();

public:
    //constructors/destructors
    PlayerGUI(Player *player);
    virtual ~PlayerGUI();

    //functions
    void updateHpBar();
    void update(const float &dt);

    void renderHpBar(sf::RenderTarget &target);
    void render(sf::RenderTarget &target);
};

#endif // PLAYERGUI_H
