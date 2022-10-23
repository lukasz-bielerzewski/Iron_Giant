#include "Source_Files/pch.h"
#include "movementcomponent.h"

//constructors/destructors
MovementComponent::MovementComponent(sf::Sprite &sprite,
                                     float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite),
    maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

//getters
const sf::Vector2f &MovementComponent::getVelocity() const
{
    return this->velocity;
}

const float &MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

bool MovementComponent::getState(const unsigned short state)
{
    switch(state)
    {
    case IDLE:
        if(this->velocity.x == 0.f && this->velocity.y == 0.f)
        {
            return true;
        }
        break;

    case MOVING:
        if(this->velocity.x != 0.f || this->velocity.y != 0.f)
        {
            return true;
        }
        break;

    case MOVING_LEFT:
        if(this->velocity.x < 0.f)
        {
            return true;
        }
        break;

    case MOVING_RIGHT:
        if(this->velocity.x > 0.f)
        {
            return true;
        }
        break;

    case MOVING_UP:
        if(this->velocity.y < 0.f)
        {
            return true;
        }
        break;

    case MOVING_DOWN:
        if(this->velocity.y > 0.f)
        {
            return true;
        }
        break;
    }

    return false;
}

//update functions
void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
    //acceleration

    this->velocity.x += this->acceleration * dir_x;

    this->velocity.y = this->maxVelocity * dir_y;
}

void MovementComponent::update(const float &dt)
{
    //deceleration
    if(this->velocity.x > 0.f)
    {
        if(this->velocity.x > this->maxVelocity)
        {
            this->velocity.x = this->maxVelocity;
        }

        this->velocity.x -= deceleration;
        if(this->velocity.x < 0.f)
        {
            this->velocity.x = 0.f;
        }
    }
    else if(this->velocity.x < 0.f)
    {
        if(this->velocity.x < -this->maxVelocity)
        {
            this->velocity.x = -this->maxVelocity;
        }

        this->velocity.x += deceleration;
        if(this->velocity.x > 0.f)
        {
            this->velocity.x = 0.f;
        }
    }

    if(this->velocity.y > 0.f)
    {
        if(this->velocity.y > this->maxVelocity)
        {
            this->velocity.y = this->maxVelocity;
        }

        this->velocity.y -= deceleration;
        if(this->velocity.y < 0.f)
        {
            this->velocity.y = 0.f;
        }
    }
    else if(this->velocity.y < 0.f)
    {
        if(this->velocity.y < -this->maxVelocity)
        {
            this->velocity.y = -this->maxVelocity;
        }

        this->velocity.y += deceleration;
        if(this->velocity.y > 0.f)
        {
            this->velocity.y = 0.f;
        }
    }

    //final move
    this->sprite.move(this->velocity * dt);
}
