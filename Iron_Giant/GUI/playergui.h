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

    std::string expBarString;
    sf::Text expBarText;
    float expBarMaxWidth;
    sf::RectangleShape expBarBack;
    sf::RectangleShape expBarInner;

    std::string hpBarString;
    sf::Text hpBarText;
    float hpBarMaxWidth;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;

    std::string levelBarString;
    sf::Text levelBarText;
    sf::RectangleShape levelBarBack;

    //initialization functions
    void initFont();
    void initExpBar();
    void initHpBar();
    void initLevelBar();

public:
    //constructors/destructors
    PlayerGUI(Player *player);
    virtual ~PlayerGUI();

    //functions
    void updateHpBar();
    void updateExpBar();
    void updateLevelBar();
    void update(const float &dt);

    void renderHpBar(sf::RenderTarget &target);
    void renderExpBar(sf::RenderTarget &target);
    void renderLevelBar(sf::RenderTarget &target);
    void render(sf::RenderTarget &target);
};

#endif // PLAYERGUI_H
