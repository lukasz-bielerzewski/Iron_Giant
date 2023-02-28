#include "Source_Files/pch.h"
#include "enemy.h"

//constructors/destructors
void Enemy::initVariables()
{
    this->speed = 300.f;
}

void Enemy::initAnimations()
{
    this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
    this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
    this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
    this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
    this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);
}

void Enemy::initAI()
{

}

Enemy::Enemy(float x, float y, sf::Texture &texture_sheet, Entity &player)
{
    this->initVariables();

    this->sprite.setScale(3, 3);
    this->createHitboxComponent(this->sprite, 49.f, 127.f, 70.f, 70.f);
    this->createMovementComponent(this->speed, 800.f, 500.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(1);

    this->setPosition(x, y);
    this->initAnimations();
}

Enemy::~Enemy()
{

}

//functions
void Enemy::updateAnimation(const float &dt)
{
    if (this->movementComponent->getState(IDLE))
        {
            this->animationComponent->play("IDLE", dt);
        }
        else if (this->movementComponent->getState(MOVING_LEFT))
        {
            this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
        else if (this->movementComponent->getState(MOVING_RIGHT))
        {
            this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
        else if (this->movementComponent->getState(MOVING_UP))
        {
            this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
        }
        else if (this->movementComponent->getState(MOVING_DOWN))
        {
            this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
        }

}

void Enemy::updateSpeed()
{
    this->movementComponent->maxVelocity = this->speed;
}

void Enemy::update(const float &dt)
{
    this->movementComponent->update(dt);

    this->updateAnimation(dt);

    this->hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);

    this->hitboxComponent->render(target);
}
