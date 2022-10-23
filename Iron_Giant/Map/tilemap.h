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
    std::vector< std::vector< std::vector<Tile> > > map;

public:
    //constructors/destructors
    TileMap(float gridSize, unsigned width, unsigned height);
    virtual ~TileMap();

    //functions
    void update();
    void render(sf::RenderTarget &target);
    void addTile();
    void removeTile();
};

#endif // TILEMAP_H
