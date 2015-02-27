#include "GameState.hpp"

GameState::GameState(cf::StateManager& manager)
: cf::State(manager)
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    return true;
}

bool GameState::update(sf::Time dt)
{
    return true;
}

void GameState::render()
{
}

void GameState::toMenu()
{
    requestPop();
    requestPush(MenuState::getID());
}
