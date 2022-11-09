#include "Source_Files/pch.h"
#include "tilemap.h"

//functions
void TileMap::clear()
{
    for(size_t x = 0; x<this->maxSize.x; x++)
    {
        for(size_t y = 0; y<this->maxSize.y; y++)
        {
            for(size_t z = 0; z<this->layers; z++)
            {
                delete this->map[x][y][z];
                this->map[x][y][z] = nullptr;
            }

            this->map[x][y].clear();
        }

       this->map[x].clear();
    }

    this->map.clear();
}

//constructors/destructors
TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    this->textureFile = texture_file;

    this->map.resize(this->maxSize.x, std::vector< std::vector <Tile*> > ());

    for(size_t x = 0; x<this->maxSize.x; x++)
    {
        for(size_t y = 0; y<this->maxSize.y; y++)
        {
            this->map[x].resize(this->maxSize.y, std::vector<Tile*> ());

            for(size_t z = 0; z<this->layers; z++)
            {
                this->map[x][y].resize(this->layers, nullptr);
            }
        }
    }

    if(!this->tileTextureSheet.loadFromFile(texture_file))
    {
        std::cout<<"ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file <<std::endl;
    }
}

TileMap::~TileMap()
{
    this->clear();
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
    for(auto &x: this->map)
    {
        for(auto &y: x)
        {
            for(auto *z: y)
            {
                if(z != nullptr)
                {
                    z->render(target);
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
            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect);
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

void TileMap::saveToFile(const std::string file_name)
{
    std::ofstream out_file;

    out_file.open(file_name);

    if(out_file.is_open())
    {
        out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
            << this->gridSizeU << "\n"
            << this->layers << "\n"
            << this->textureFile << "\n";

        for(size_t x = 0; x<this->maxSize.x; x++)
        {
            for(size_t y = 0; y<this->maxSize.y; y++)
            {
                for(size_t z = 0; z<this->layers; z++)
                {
                    if(this->map[x][y][z])
                    {
                        out_file << x << " " << y << " " << z << " " <<
                                    this->map[x][y][z]->getAsString() << " ";
                    }
                }
            }
        }
    }
    else
    {
        std::cout<<"ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: "<< file_name <<std::endl;
    }

    out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
    std::ifstream in_file;

    in_file.open(file_name);

    if(in_file.is_open())
    {
        sf::Vector2u size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string texture_file = "";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned txrx = 0;
        unsigned txry = 0;
        bool collision = false;
        short type = 0;

        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeU = gridSize;
        this->maxSize.x = size.x;
        this->maxSize.y = size.y;
        this->layers = layers;
        this->textureFile = texture_file;

        this->clear();

        this->map.resize(this->maxSize.x, std::vector< std::vector <Tile*> > ());

        for(size_t x = 0; x<this->maxSize.x; x++)
        {
            for(size_t y = 0; y<this->maxSize.y; y++)
            {
                this->map[x].resize(this->maxSize.y, std::vector<Tile*> ());

                for(size_t z = 0; z<this->layers; z++)
                {
                    this->map[x][y].resize(this->layers, nullptr);
                }
            }
        }

        if(!this->tileTextureSheet.loadFromFile(texture_file))
        {
            std::cout<<"ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file <<std::endl;
        }

        while(in_file >> x >> y >> z >> txrx >> txry >> collision >> type)
        {
            this->map[x][y][z] = new Tile(x, y, gridSizeF, this->tileTextureSheet, sf::IntRect(txrx, txry, this->gridSizeU, this->gridSizeU), collision, type);
        }
    }
    else
    {
        std::cout<<"ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: "<< file_name <<std::endl;
    }

    in_file.close();
}
