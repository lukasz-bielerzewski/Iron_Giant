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

    this->map.resize(this->maxSize.x, std::vector< std::vector <Tile*> > ());

    for(size_t i = 0; i<this->maxSize.x; i++)
    {
        for(size_t j = 0; j<this->maxSize.y; j++)
        {
            this->map[i].resize(this->maxSize.y, std::vector<Tile*> ());

            for(size_t k = 0; k<this->layers; k++)
            {
                this->map[i][j].resize(this->layers, nullptr);
            }
        }
    }

    if(!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
    {
        std::cout<<"ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET"<<std::endl;
    }
}

TileMap::~TileMap()
{
    for(size_t i = 0; i<this->maxSize.x; i++)
    {
        for(size_t j = 0; j<this->maxSize.y; j++)
        {
            for(size_t k = 0; k<this->layers; k++)
            {
                delete this->map[i][j][k];
            }
        }
    }
}

//getters
const sf::Texture *TileMap::getTileTextureSheet() const
{
    return &this->tileTextureSheet;
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
            for(auto *k: j)
            {
                if(k != nullptr)
                {
                    k->render(target);
                }
            }
        }
    }
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect)
{
    if(x < this->maxSize.x && x >= 0 &&
            y < this->maxSize.y && y >= 0 &&
            z < this->layers && z >= 0)
    {
        if(this->map[x][y][z] == nullptr)
        {
            this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet, texture_rect);
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    if(x < this->maxSize.x && x >= 0 &&
            y < this->maxSize.y && y >= 0 &&
            z < this->layers && z >= 0)
    {
        if(this->map[x][y][z] != nullptr)
        {
            delete this->map[x][y][z];
            this->map[x][y][z] = nullptr;
        }
    }
}
