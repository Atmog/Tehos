#include "GameState.hpp"

GameState::GameState(cf::StateManager& manager)
: cf::State(manager)
, mWorld(GameModeState::getGameMode(cf::Application::getData().get("gamemode")))
{
    mGameEnded = false;
}

bool GameState::handleEvent(sf::Event const& event)
{
    mWorld.handleEvent(event);
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);

    if (!mGameEnded)
    {
        mEnd = mWorld.getEnd();
        if (mEnd != World::GameEnd::None)
        {
            mGameEnded = true;
        }
        mGameEndClock.restart();
    }

    if (mGameEnded && mGameEndClock.getElapsedTime() >= sf::seconds(3))
    {
        toGameEnd(mEnd);
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
