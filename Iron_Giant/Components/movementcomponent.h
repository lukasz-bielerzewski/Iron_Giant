#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
    //variables
    sf::Sprite &sprite;


    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    //initializing functions

public:
    float maxVelocity;

    //constructors/destructors
    MovementComponent(sf::Sprite &sprite,
                      float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    //getters
    const sf::Vector2f &getVelocity() const;
    const float &getMaxVelocity() const;
    bool getState(const short unsigned state);

    //update functions
    void move(const float dir_x, const float dir_y, const float &dt);
    void update(const float &dt);

    //functions
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
};

#endif // MOVEMENTCOMPONENT_H
