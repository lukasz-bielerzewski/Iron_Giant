#include "Source_Files/pch.h"
#include "editorstate.h"

//initializing functions
void EditorState::initVariables()
{

}

void EditorState::initFonts()
{
    if(!this->font.loadFromFile("Resources/Fonts/PressStart2P-Regular.ttf"))
    {
        throw("ERROR::EDITOR_STATE::COUL_NOT_LOAD_FONT");
    }
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
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
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
    this->initKeybinds();
    this->initPauseMenu();
    this->initButtons();
    this->initGui();
    this->initTileMap();
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
        this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
    {
        this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
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
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
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

    this->renderButtons(*target);

    this->renderGui(*target);

    this->tileMap->render(*target);

    if(this->paused)
    {
        this->pmenu->render(*target);
    }

    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x + 25, this->mousePosView.y + 25);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y - 50;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}
