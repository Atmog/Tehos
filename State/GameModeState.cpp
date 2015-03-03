#include "GameModeState.hpp"

GameModeState::GameModeState(cf::StateManager& manager)
: cf::State(manager)
{
    mGameMode = World::GameMode::Survival;

    auto buttonPlay = mGUI.newButton();
    buttonPlay->setPosition(sf::Vector2f(400-175,100));
    buttonPlay->setTexture(cf::Application::getResources().getTexture("Assets/Textures/gui.png"));
    buttonPlay->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonPlay->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonPlay->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonPlay->setFont(cf::Application::getResources().getFont("Assets/Fonts/sansation.ttf"));
    buttonPlay->setString("Survival");
    buttonPlay->setColor(sf::Color::Black);
    buttonPlay->setCallback([&] ()
    {
        toGame();
    },0);
    buttonPlay->setCallback([&] ()
    {
    },1);

    auto buttonQuit = mGUI.newButton();
    buttonQuit->setPosition(sf::Vector2f(400-175,500));
    buttonQuit->setTexture(cf::Application::getResources().getTexture("Assets/Textures/gui.png"));
    buttonQuit->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonQuit->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonQuit->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonQuit->setFont(cf::Application::getResources().getFont("Assets/Fonts/sansation.ttf"));
    buttonQuit->setString("Return");
    buttonQuit->setColor(sf::Color::Black);
    buttonQuit->setCallback([&] ()
    {
        toMenu();
    },0);
    buttonQuit->setCallback([&] ()
    {
    },1);
}

bool GameModeState::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,cf::Application::getWindow());
    return true;
}

bool GameModeState::update(sf::Time dt)
{
    mGUI.update();
    return true;
}

void GameModeState::render()
{
    cf::Application::getWindow().draw(mGUI);
}

World::GameMode GameModeState::getGameMode(std::string dataString)
{
    if (dataString == "deathmatch")
        return World::GameMode::DeathMatch;
    if (dataString == "domination")
        return World::GameMode::Domination;
    return World::GameMode::Survival;
}

std::string GameModeState::getGameModeString(World::GameMode gamemode)
{
    switch (gamemode)
    {
        case World::GameMode::DeathMatch: return "deathmatch"; break;
        case World::GameMode::Domination: return "domination"; break;
        default: return "survival"; break;
    }
}

void GameModeState::toGame()
{
    cf::Application::getData().set("gamemode",getGameModeString(mGameMode));

    requestPop();
    requestPush(GameState::getID());
}

void GameModeState::toMenu()
{
    requestPop();
    requestPush(MenuState::getID());
}
