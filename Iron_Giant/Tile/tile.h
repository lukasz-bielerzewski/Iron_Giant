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
    Tile(float x, float y, float gridSizeF);
    virtual ~Tile();

    //functions
    void update();
    void render(sf::RenderTarget &target);
};

#endif // TILE_H
