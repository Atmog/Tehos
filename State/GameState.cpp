#include "GameState.hpp"

GameState::GameState(cf::StateManager& manager)
: cf::State(manager)
, mWorld(GameModeState::getGameMode(cf::Application::getData().get("gamemode")))
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    mWorld.handleEvent(event);
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << cf::Application::getWindow().getMousePosition().x << " " << cf::Application::getWindow().getMousePosition().y << std::endl;
        }
    }
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
    return true;
}

void GameState::render()
{
    mWorld.render();
}

void GameState::toMenu()
{
    requestPop();
    requestPush(MenuState::getID());
}
