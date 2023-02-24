#include "Source_Files/pch.h"
#include "editorstate.h"

//initializing functions
void EditorState::initVariables()
{
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));

    this->collision = false;
    this->type = TileTypes::DEFAULT;

    this->cameraSpeed = 300.f;

    this->layer = 0;
}

void EditorState::initView()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width),
                                    static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->view.setCenter(static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
                         static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f);
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
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
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
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50.f, 50.f, 50.f, 100.f));
    this->sidebar.setOutlineColor(sf::Color(200.f, 200.f, 200.f, 150.f));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
    this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(20.f, 20.f, 900.f, 300.f,
                                                     this->stateData->gridSize, this->tileMap->getTileTextureSheet(),
                                                     this->font, "TS");
}

void EditorState::initTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet1.png");
}

void EditorState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 800.f, "Quit");
    this->pmenu->addButton("SAVE", 300.f, "Save map");
    this->pmenu->addButton("LOAD", 400.f, "Load map");
}

//contructors/destructors
EditorState::EditorState(StateData *state_data)
    : State(state_data)
{
    this->initVariables();
    this->initView();
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

    delete this->textureSelector;
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
    {
        this->view.move(0.f, -std::floor(this->cameraSpeed * dt));
    }

     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
    {
        this->view.move(0.f, std::floor(this->cameraSpeed * dt));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
    {
        this->view.move(-std::floor(this->cameraSpeed * dt), 0.f);
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
    {
        this->view.move(std::floor(this->cameraSpeed * dt), 0.f);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
    {
        if(!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
        {
            if(!this->textureSelector->getActive())
            {
                this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
            }
            else
            {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
    {
        if(!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
        {
            if(!this->textureSelector->getActive())
            {
                this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
    {
        if(this->collision)
        {
            this->collision = false;
        }
        else
        {
            this->collision = true;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
    {
        ++this->type;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
    {
        if(this->type > 0)
        {
            --this->type;
        }
    }
}

void EditorState::updateButtons()
{
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow);
    }
}

void EditorState::updateGui(const float &dt)
{
    this->textureSelector->update(this->mousePosWindow, dt);

    if(!this->textureSelector->getActive())
    {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
    }

    this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y + 25.f);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y <<
          "\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
          "\n" << this->textureRect.left << " " <<this->textureRect.top <<
          "\n" << "Collision: " << this->collision <<
          "\n" << "Type: " << this->type <<
          "\n" << "Tiles: " << this->tileMap->getLayerSize(this->mousePosGrid.x, this->mousePosGrid.y, this->layer);
    this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons()
{
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }

    if(this->pmenu->isButtonPressed("SAVE"))
    {
        this->tileMap->saveToFile("text.igmp");
    }

    if(this->pmenu->isButtonPressed("LOAD"))
    {
        this->tileMap->loadFromFile("text.igmp");
    }
}

void EditorState::update(const float &dt)
{
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);

    if(!this->paused)
    {
        this->updateButtons();
        this->updateGui(dt);
        this->updateEditorInput(dt);
    }
    else
    {
        this->pmenu->update(this->mousePosWindow);
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
    if(!this->textureSelector->getActive())
    {
        target.setView(this->view);
        target.draw(this->selectorRect);
    }

    target.setView(this->window->getDefaultView());
    this->textureSelector->render(target);
    target.draw(this->sidebar);

    target.setView(this->view);
    target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget *target)
{
    if(!target)
    {
        target = this->window;
    }

    target->setView(this->view);

    this->tileMap->render(*target, this->mousePosGrid);
    this->tileMap->renderDeferred(*target);

    target->setView(this->window->getDefaultView());

    this->renderButtons(*target);

    this->renderGui(*target);

    if(this->paused)
    {
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }
}
