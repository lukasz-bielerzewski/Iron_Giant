#include "Source_Files/pch.h"
#include "playergui.h"

//initialization fucntions
void PlayerGUI::initFont()
{
    this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");
}

void PlayerGUI::initHpBar()
{
    float width = 300.f;
    float height = 35.f;
    float x = 20.f;
    float y = 20.f;

    this->hpBarMaxWidth = width;

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());
}

//constructors/destructors
PlayerGUI::PlayerGUI(Player *player)
{
    this->player = player;

    this->initFont();
    this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{

}

//functions
void PlayerGUI::updateHpBar()
{
    float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);
    this->hpBarInner.setSize(sf::Vector2f(
                                 static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
                                 this->hpBarInner.getSize().y));
}

void PlayerGUI::update(const float &dt)
{
    this->updateHpBar();
}

void PlayerGUI::renderHpBar(sf::RenderTarget &target)
{
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->renderHpBar(target);
}
