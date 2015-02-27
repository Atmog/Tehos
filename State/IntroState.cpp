#include "IntroState.hpp"

IntroState::IntroState(cf::StateManager& manager)
: cf::State(manager)
{
}

bool IntroState::handleEvent(sf::Event const& event)
{
    return true;
}

bool IntroState::update(sf::Time dt)
{
    return true;
}

void IntroState::render()
{
}

void IntroState::toMenu()
{
    requestPop();
    requestPush(MenuState::getID());
}
