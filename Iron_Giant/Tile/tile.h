#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING, ON_TOP};

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
    Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect, bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //getters
    const std::string getAsString() const;
    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const bool &getCollision() const;
    const short &getType() const;

    //functions  
    bool intersects(const sf::FloatRect bounds) const;
    void update();
    void render(sf::RenderTarget &target);
};

#endif // TILE_H
