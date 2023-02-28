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
    this->createMovementComponent(325.f, 1500.f, 500.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(1);

    this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);

    this->attackHitboxLeft.setSize(sf::Vector2f(this->getGlobalBounds().width * 1.5f, this->getGlobalBounds().height));
    this->attackHitboxLeft.setPosition(this->getPosition().x - (this->getGlobalBounds().width * 1.5f), this->getPosition().y);
    this->attackHitboxLeft.setFillColor(sf::Color::Transparent);
    this->attackHitboxLeft.setOutlineThickness(-1.f);
    this->attackHitboxLeft.setOutlineColor(sf::Color::Magenta);

    this->attackHitboxRight.setSize(sf::Vector2f(this->getGlobalBounds().width * 1.5f, this->getGlobalBounds().height));
    this->attackHitboxRight.setPosition(this->getPosition().x + (this->getGlobalBounds().width * 1.f), this->getPosition().y);
    this->attackHitboxRight.setFillColor(sf::Color::Transparent);
    this->attackHitboxRight.setOutlineThickness(-1.f);
    this->attackHitboxRight.setOutlineColor(sf::Color::Magenta);

    this->rendAHL = false;
    this->rendAHR = false;
    this->dead = false;
}

Player::~Player()
{

}

//getters
AttributeComponent *Player::getAttributeComponent()
{
    return this->attributeComponent;
}

//functions
void Player::updateAttack()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->attacking = true;
    }
}

void Player::loseHp(const int hp)
{
    this->attributeComponent->hp -= hp;

    if(this->attributeComponent->hp < 0)
    {
        this->attributeComponent->hp = 0;
    }
}

void Player::loseExp(const int exp)
{
    this->attributeComponent->exp -= exp;

    if(this->attributeComponent->exp < 0)
    {
        this->attributeComponent->exp = 0;
    }
}

void Player::gainHp(const int hp)
{
    this->attributeComponent->hp += hp;

    if(this->attributeComponent->hp > this->attributeComponent->hpMax)
    {
        this->attributeComponent->hp = this->attributeComponent->hpMax;
    }
}

void Player::gainExp(const int exp)
{
    this->attributeComponent->gainExp(exp);
}

void Player::updateAnimation(const float &dt)
{
    if(!this->dead)
    {
        if(this->attacking)
        {
            if(this->sprite.getScale().x > 0.f)
            {
                this->sprite.setOrigin(96.f, 0.f);
                this->rendAHL = true;
            }
            else
            {
                this->sprite.setOrigin(258.f + 96.f, 0.f);
                this->rendAHR = true;
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
}

void Player::update(const float &dt)
{
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
//    {
//        this->attributeComponent->gainExp(20);
//    }
//    system("cls");
//    std::cout << this->attributeComponent->debugPrint() << "\n";

    this->movementComponent->update(dt);

    this->updateAttack();

    this->updateAnimation(dt);

    this->hitboxComponent->update();

    this->attackHitboxLeft.setSize(sf::Vector2f(this->getGlobalBounds().width * 1.5f, this->getGlobalBounds().height));
    this->attackHitboxRight.setSize(sf::Vector2f(this->getGlobalBounds().width * 1.5f, this->getGlobalBounds().height));
    this->attackHitboxLeft.setPosition(this->getPosition().x - (this->getGlobalBounds().width * 2.f), this->getPosition().y);
    this->attackHitboxRight.setPosition(this->getPosition().x + (this->getGlobalBounds().width * 1.5f), this->getPosition().y);
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);

    if(this->rendAHL)
    {
        target.draw(this->attackHitboxLeft);
        this->rendAHL = false;
    }
    if(this->rendAHR)
    {
        target.draw(this->attackHitboxRight);
        this->rendAHR = false;
    }

    this->hitboxComponent->render(target);
}
