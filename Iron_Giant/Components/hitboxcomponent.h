#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
    //variables
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    float offsetX;
    float offsetY;

public:
    //constructors/destructors
    HitboxComponent(sf::Sprite &sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    virtual ~HitboxComponent();

    //functions
    bool checkIntersect(const sf::FloatRect &frect);
    void update();
    void render(sf::RenderTarget &target);
};

#endif // HITBOXCOMPONENT_H
