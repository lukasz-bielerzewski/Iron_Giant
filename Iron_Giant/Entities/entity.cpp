#include "Source_Files/pch.h"
#include "entity.h"

//initialization fucntions
void Entity::initVariables()
{
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
    this->collision = false;
}

//constructors/destructors
Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
    delete this->attributeComponent;
}

//component functions
void Entity::setTexture(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite &sprite,
                                   float offset_x, float offset_y,
                                   float width, float height)
{
    this->hitboxComponent = new HitboxComponent(sprite,
                                                offset_x, offset_y,
                                                width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
    this->attributeComponent = new AttributeComponent(level);
}

//getters
const sf::Vector2f &Entity::getPosition() const
{
    if(this->hitboxComponent)
    {
        return this->hitboxComponent->getPosition();
    }

    return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
    if(this->hitboxComponent)
    {
        return sf::Vector2i(this->hitboxComponent->getPosition().x / gridSizeI,
                            this->hitboxComponent->getPosition().y / gridSizeI);
    }

    return sf::Vector2i(this->sprite.getPosition().x / gridSizeI,
                        this->sprite.getPosition().y / gridSizeI);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if(this->hitboxComponent)
    {
        return this->hitboxComponent->getGlobalBounds();
    }

    return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float &dt) const
{
    if(this->hitboxComponent && this->movementComponent)
    {
        return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
    }
    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//functions
void Entity::setPosition(const float x, const float y)
{
    if(this->hitboxComponent)
    {
        this->hitboxComponent->setPosition(x, y);
    }
    else
    {
        this->sprite.setPosition(x, y);
    }
}

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
    if(this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt);
    }
}

void Entity::stopVelocity()
{
    if(this->movementComponent)
    {
        this->movementComponent->stopVelocity();
    }
}

void Entity::stopVelocityX()
{
    if(this->movementComponent)
    {
        this->movementComponent->stopVelocityX();
    }
}

void Entity::stopVelocityY()
{
    if(this->movementComponent)
    {
        this->movementComponent->stopVelocityY();
    }
}

void Entity::update(const float &dt)
{

}

void Entity::render(sf::RenderTarget &target)
{

}
