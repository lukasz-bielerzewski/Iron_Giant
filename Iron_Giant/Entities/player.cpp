#include "Source_Files/pch.h"
#include "player.h"

//initializing functions
void Player::initVariables()
{
    this->attacking = false;
}

void Player::initComponents()
{

}

//constructors/destructors
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
    this->initVariables();

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 86.f, 66.f, 86.f, 116.f);
    this->createMovementComponent(325.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}

Player::~Player()
{

}

//functions
void Player::updateAttack()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->attacking = true;
    }
}

void Player::updateAnimation(const float &dt)
{
    if(this->attacking)
    {
        if(this->sprite.getScale().x > 0.f)
        {
            this->sprite.setOrigin(96.f, 0.f);
        }
        else
        {
            this->sprite.setOrigin(258.f + 96.f, 0.f);
        }

        if(this->animationComponent->play("ATTACK", dt, true))
        {
            this->attacking = false;

            if(this->sprite.getScale().x > 0.f)
            {
                this->sprite.setOrigin(0.f, 0.f);
            }
            else
            {
                this->sprite.setOrigin(258.f, 0.f);
            }
        }
    }

    if(this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt);
    }
    else if(this->movementComponent->getState(MOVING_LEFT))
    {
        if(this->sprite.getScale().x < 0.f)
        {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }

        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if(this->movementComponent->getState(MOVING_RIGHT))
    {
        if(this->sprite.getScale().x > 0.f)
        {
            this->sprite.setOrigin(258.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
        }

        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if(this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
    else if(this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float &dt)
{
    this->movementComponent->update(dt);

    this->updateAttack();

    this->updateAnimation(dt);

    this->hitboxComponent->update();
}
