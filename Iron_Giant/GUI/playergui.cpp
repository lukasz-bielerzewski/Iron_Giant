#include "Source_Files/pch.h"
#include "playergui.h"

//initialization fucntions
void PlayerGUI::initFont()
{
    this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf");
}

void PlayerGUI::initExpBar()
{
    float width = 300.f;
    float height = 25.f;
    float x = 90.f;
    float y = 60.f;

    this->expBarMaxWidth = width;

    this->expBarBack.setSize(sf::Vector2f(width, height));
    this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->expBarBack.setPosition(x, y);

    this->expBarInner.setSize(sf::Vector2f(width, height));
    this->expBarInner.setFillColor(sf::Color(250, 20, 200, 200));
    this->expBarInner.setPosition(this->expBarBack.getPosition());

    this->expBarText.setFont(this->font);
    this->expBarText.setCharacterSize(12);
    this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
    this->expBarText.setString(this->expBarString);
    this->expBarText.setPosition(this->expBarInner.getPosition().x + (this->expBarInner.getGlobalBounds().width / 2.f) - this->expBarText.getGlobalBounds().width / 2.f,
                                this->expBarInner.getPosition().y + (this->expBarInner.getGlobalBounds().height / 2.f) - this->expBarText.getGlobalBounds().height / 2.f);
}

void PlayerGUI::initHpBar()
{
    float width = 300.f;
    float height = 35.f;
    float x = 90.f;
    float y = 20.f;

    this->hpBarMaxWidth = width;

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());

    this->hpBarText.setFont(this->font);
    this->hpBarText.setCharacterSize(16);
    this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
    this->hpBarText.setString(this->hpBarString);
    this->hpBarText.setPosition(this->hpBarInner.getPosition().x + (this->hpBarInner.getGlobalBounds().width / 2.f) - this->hpBarText.getGlobalBounds().width / 2.f,
                                this->hpBarInner.getPosition().y + (this->hpBarInner.getGlobalBounds().height / 2.f) - this->hpBarText.getGlobalBounds().height / 2.f);
}

void PlayerGUI::initLevelBar()
{
    float width = 60.f;
    float height = 60.f;
    float x = 20.f;
    float y = 20.f;

    this->levelBarBack.setSize(sf::Vector2f(width, height));
    this->levelBarBack.setFillColor(sf::Color(50, 250, 50, 200));
    this->levelBarBack.setOutlineColor(sf::Color(250, 250, 250, 200));
    this->levelBarBack.setOutlineThickness(-3.f);
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(this->font);
    this->levelBarText.setCharacterSize(20);
    this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
    this->levelBarText.setString(this->levelBarString);
    this->levelBarText.setPosition(this->levelBarBack.getPosition().x + (this->levelBarBack.getGlobalBounds().width / 2.f) - this->levelBarText.getGlobalBounds().width / 2.f,
                                this->levelBarBack.getPosition().y + (this->levelBarBack.getGlobalBounds().height / 2.f) - this->levelBarText.getGlobalBounds().height / 2.f);
}

//constructors/destructors
PlayerGUI::PlayerGUI(Player *player)
{
    this->player = player;

    this->initFont();
    this->initHpBar();
    this->initExpBar();
    this->initLevelBar();
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

    this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
    this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::updateExpBar()
{
    float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);
    this->expBarInner.setSize(sf::Vector2f(
                                 static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
                                 this->expBarInner.getSize().y));

    this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
    this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateLevelBar()
{
    this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
    this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::update(const float &dt)
{
    this->updateHpBar();
    this->updateExpBar();
    this->updateLevelBar();
}

void PlayerGUI::renderHpBar(sf::RenderTarget &target)
{
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
    target.draw(this->hpBarText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget &target)
{
    target.draw(this->expBarBack);
    target.draw(this->expBarInner);
    target.draw(this->expBarText);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget &target)
{
    target.draw(this->levelBarBack);
    target.draw(this->levelBarText);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->renderHpBar(target);
    this->renderExpBar(target);
    this->renderLevelBar(target);
}
