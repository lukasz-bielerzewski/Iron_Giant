#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:

protected:
    //variables
    sf::RectangleShape shape;
    bool collision;
    short type;

public:
    //constructors/destructors
    Tile();
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect, bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //getters
    const std::string getAsString() const;

    //functions  
    void update();
    void render(sf::RenderTarget &target);
};

#endif // TILE_H
