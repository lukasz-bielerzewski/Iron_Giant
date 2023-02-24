#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

//forward declarations
class Entity;

class Player : public Entity
{
private:
    //variables
    bool attacking;

    //initializing functions
    void initVariables();
    void initComponents();

public:
    //constructors/destructors
    Player(float x, float y, sf::Texture &texture_sheet);
    virtual ~Player();

    //getters
    AttributeComponent *getAttributeComponent();

    //functions
    void updateAttack();
    void loseHp(const int hp);
    void loseExp(const int exp);
    void gainHp(const int hp);
    void gainExp(const int exp);
    void updateAnimation(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget &target);
};

#endif // PLAYER_H
