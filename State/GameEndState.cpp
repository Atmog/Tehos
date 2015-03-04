#include "GameEndState.hpp"

GameEndState::GameEndState(cf::StateManager& manager)
: cf::State(manager)
{
    auto buttonPlay = mGUI.newButton();
    buttonPlay->setPosition(sf::Vector2f(400-175,100));
    buttonPlay->setTexture(cf::Application::getResources().getTexture("Assets/Textures/gui.png"));
    buttonPlay->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonPlay->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonPlay->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonPlay->setFont(cf::Application::getResources().getFont("Assets/Fonts/sansation.ttf"));
    buttonPlay->setString("Play again");
    buttonPlay->setColor(sf::Color::Black);
    buttonPlay->setCallback([&] ()
    {
        toGameMode();
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
    buttonQuit->setString("Return to Menu");
    buttonQuit->setColor(sf::Color::Black);
    buttonQuit->setCallback([&] ()
    {
        toMenu();
    },0);
    buttonQuit->setCallback([&] ()
    {
    },1);
}

bool GameEndState::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,cf::Application::getWindow());
    return true;
}

bool GameEndState::update(sf::Time dt)
{
    mGUI.update();
    return true;
}

void GameEndState::render()
{
    cf::Application::getWindow().draw(mGUI);
}

void GameEndState::toGameMode()
{
    requestPop();
    requestPush(GameModeState::getID());
}

void GameEndState::toMenu()
{
    requestPop();
    requestPush(MenuState::getID());
}
