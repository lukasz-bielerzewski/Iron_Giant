#include "Source_Files/pch.h"
#include "tile.h"

//constructors/destructors
Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setPosition(x, y);
}

Tile::~Tile()
{

}

//functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}
