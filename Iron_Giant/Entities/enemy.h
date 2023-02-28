#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Entity;

class Enemy : public Entity
{
private:
    //initialization functions
    void initVariables();
    void initAnimations();
    void initAI();

public:
    float speed;

    //constructors/destructors
    Enemy(float x, float y, sf::Texture &texture_sheet, Entity &player);
    virtual ~Enemy();

    //functions
    void updateAnimation(const float &dt);
    void updateSpeed();
    void update(const float &dt);
    void render(sf::RenderTarget &target);
};

#endif // ENEMY_H
