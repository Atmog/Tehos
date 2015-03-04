#include "GameState.hpp"

GameState::GameState(cf::StateManager& manager)
: cf::State(manager)
, mWorld(GameModeState::getGameMode(cf::Application::getData().get("gamemode")))
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    mWorld.handleEvent(event);
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);

    World::GameEnd end = mWorld.getEnd();
    if (end != World::GameEnd::None)
    {
        toGameEnd(end);
    }

    return true;
}

void GameState::render()
{
    mWorld.render();
}

void GameState::toGameEnd(World::GameEnd end)
{
    if (end == World::GameEnd::Win)
        cf::Application::getData().set("game-end","win");
    if (end == World::GameEnd::Loose)
        cf::Application::getData().set("game-end","loose");

    requestPop();
    requestPush(GameEndState::getID());
}
