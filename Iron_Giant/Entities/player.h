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

    //functions
    void updateAttack();
    void updateAnimation(const float &dt);
    virtual void update(const float &dt);
};

#endif // PLAYER_H
