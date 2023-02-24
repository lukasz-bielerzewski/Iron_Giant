#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
    //variables
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

public:
    //constructors/destructors
    HitboxComponent(sf::Sprite &sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    virtual ~HitboxComponent();

    //getters
    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect &getNextPosition(const sf::Vector2f &velocity);

    //setters
    void setPosition(const sf::Vector2f &position);
    void setPosition(const float x, const float y);

    //functions
    bool intersects(const sf::FloatRect &frect);
    void update();
    void render(sf::RenderTarget &target);
};

#endif // HITBOXCOMPONENT_H
