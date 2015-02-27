#include "MenuState.hpp"

MenuState::MenuState(cf::StateManager& manager)
: cf::State(manager)
{
}

bool MenuState::handleEvent(sf::Event const& event)
{
    return true;
}

bool MenuState::update(sf::Time dt)
{
    return true;
}

void MenuState::render()
{
}

void MenuState::toGame()
{
    requestPop();
    requestPush(GameState::getID());
}
