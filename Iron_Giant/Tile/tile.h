#ifndef TILE_H
#define TILE_H

class Tile
{
private:

protected:
    //variables
    sf::RectangleShape shape;

public:
    //constructors/destructors
    Tile();
    Tile(float x, float y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect);
    virtual ~Tile();

    //functions
    void update();
    void render(sf::RenderTarget &target);
};

#endif // TILE_H
