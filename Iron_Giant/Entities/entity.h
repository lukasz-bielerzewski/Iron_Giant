#ifndef ENTITY_H
#define ENTITY_H

#include "Components/hitboxcomponent.h"
#include "Components/movementcomponent.h"
#include "Components/animationcomponent.h"
#include "Components/attributecomponent.h"

//forward declarations
class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;

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
    AttributeComponent *attributeComponent;

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
    void createAttributeComponent(const unsigned level);

    //getters
    virtual const sf::Vector2f &getPosition() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::FloatRect getNextPositionBounds(const float &dt) const;

    //functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float &dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget &target) = 0;
};

#endif // ENTITY_H
