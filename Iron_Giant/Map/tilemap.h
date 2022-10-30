#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile/tile.h"

//forward declarations
class Tile;

class TileMap
{
private:
    //variables
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector< std::vector< std::vector<Tile*> > > map;
    sf::Texture tileTextureSheet;

public:
    //constructors/destructors
    TileMap(float gridSize, unsigned width, unsigned height);
    virtual ~TileMap();

    //getters
    const sf::Texture *getTileTextureSheet() const;

    //functions
    void update();
    void render(sf::RenderTarget &target);
    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
};

#endif // TILEMAP_H
