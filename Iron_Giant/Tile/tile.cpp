#include "Source_Files/pch.h"
#include "tile.h"

//constructors/destructors
Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF, sf::Texture &texture)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::White);
    //this->shape.setOutlineThickness(1.f);
    //this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
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
