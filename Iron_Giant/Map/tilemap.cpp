#include "Source_Files/pch.h"
#include "tilemap.h"

//constructors/destructors
TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;

    for(size_t i = 0; i<this->maxSize.x; i++)
    {
        this->map.push_back(std::vector< std::vector <Tile> > ());

        for(size_t j = 0; j<this->maxSize.y; j++)
        {
            this->map[i].resize(this->maxSize.y);
            this->map[i].push_back(std::vector<Tile> ());

            for(size_t k = 0; k<this->layers; k++)
            {
                this->map[i][j].resize(this->layers);
                this->map[i][j].push_back(Tile(i * this->gridSizeF, j * this->gridSizeF, this->gridSizeF));
            }
        }
    }
}

TileMap::~TileMap()
{

}

//functions
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
    for(auto &i: this->map)
    {
        for(auto &j: i)
        {
            for(auto &k: j)
            {
                k.render(target);
            }
        }
    }
}

void TileMap::addTile()
{

}

void TileMap::removeTile()
{

}
