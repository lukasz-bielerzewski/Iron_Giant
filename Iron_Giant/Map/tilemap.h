#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile/tile.h"
#include "Entities/entity.h"

//forward declarations
class Tile;
class Entity;

class TileMap
{
private:
    //variables
    float gridSizeF;
    int gridSizeI;
    sf::Vector2i maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    int layers;
    std::vector< std::vector< std::vector< std::vector<Tile*> > > > map;
    std::stack<Tile*> deferredRenderStack;
    std::string textureFile;
    sf::Texture tileTextureSheet;
    sf::RectangleShape collisionBox;

    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

    //functions
    void clear();

public:
    //constructors/destructors
    TileMap(float gridSize, int width, int height, std::string texture_file);
    virtual ~TileMap();

    //getters
    const sf::Texture *getTileTextureSheet() const;
    int getLayerSize(const int x, const int y, const int layer) const;

    //functions
    void update();
    void render(sf::RenderTarget &target, const sf::Vector2i &gridPosition);
    void renderDeferred(sf::RenderTarget &target);
    void addTile(const int x, const int y, const int z, const sf::IntRect &texture_rect, const bool &collision, const short &type);
    void removeTile(const int x, const int y, const int z);

    void updateCollision(Entity *entity, const float &dt);

    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};

#endif // TILEMAP_H
