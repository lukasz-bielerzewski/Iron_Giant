#ifndef ENTITY_H
#define ENTITY_H

#include "Components/hitboxcomponent.h"
#include "Components/movementcomponent.h"
#include "Components/animationcomponent.h"

//forward declarations
class HitboxComponent;
class MovementComponent;
class AnimationComponent;

class Entity
{
private:
    void initVariables();

protected:
    //variables
    sf::Sprite sprite;

    HitboxComponent *hitboxComponent;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;

public:
    //constructors/destructors
    Entity();
    virtual ~Entity();

    //component functions
    void setTexture(sf::Texture &texture);
    void createHitboxComponent(sf::Sprite &sprite,
                               float offset_x, float offset_y,
                               float width, float height);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture &texture_sheet);

    //functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float &dt);
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget &target);
};

#endif // ENTITY_H
