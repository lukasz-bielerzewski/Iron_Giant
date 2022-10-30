#include "Source_Files/pch.h"
#include "editorstate.h"

//initializing functions
void EditorState::initVariables()
{
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
}

void EditorState::initFonts()
{
    if(!this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf"))
    {
        throw("ERROR::EDITOR_STATE::COUL_NOT_LOAD_FONT");
    }
}

void EditorState::initText()
{
    this->cursorText.setFont(this->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(12);
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("Config/editorstate_keybinds.ini");

    if(ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while(ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
    this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
    this->selectorRect.setTextureRect(this->textureRect);
}

void EditorState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

void EditorState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 800.f, "Quit");
}

//contructors/destructors
EditorState::EditorState(StateData *state_data)
    : State(state_data)
{
    this->initVariables();
    this->initFonts();
    this->initText();
    this->initKeybinds();
    this->initPauseMenu();
    this->initButtons();
    this->initTileMap();
    this->initGui();
}

EditorState::~EditorState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    delete this->pmenu;

    delete this->tileMap;
}

//functions
void EditorState::updateInput(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if(!this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unpauseState();
        }
    }
}

void EditorState::updateEditorInput(const float &dt)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
    {
        this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
    {
        this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->getKeytime())
    {
        if(this->textureRect.left < 100)
        {
            this->textureRect.left += 100;
        }
    }
}

void EditorState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void EditorState::updateGui()
{
    this->selectorRect.setTextureRect(this->textureRect);
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);

    this->cursorText.setPosition(this->mousePosView.x + 25.f, this->mousePosView.y + 25.f);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y - 50 << "\n" << this->textureRect.left << " " <<this->textureRect.top;
    this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons()
{
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
}

void EditorState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateKeytime(dt);
    this->updateInput(dt);

    if(!this->paused)
    {
        this->updateButtons();
        this->updateGui();
        this->updateEditorInput(dt);
    }
    else
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void EditorState::renderButtons(sf::RenderTarget &target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target)
{
    target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget *target)
{
    if(!target)
    {
        target = this->window;
    }

    this->tileMap->render(*target);

    this->renderButtons(*target);

    this->renderGui(*target);

    target->draw(this->cursorText);

    if(this->paused)
    {
        this->pmenu->render(*target);
    }
}
