#include "MenuState.hpp"

MenuState::MenuState(cf::StateManager& manager)
: cf::State(manager)
{
    auto shadow = mGUI.newLabel();
    shadow->setFont(cf::Application::getResources().getFont("Assets/Fonts/sansation.ttf"));
    shadow->setString("Tehos");
    shadow->setCharacterSize(60);
    shadow->setPosition(400-shadow->cf::Text::getSize().x/2+5,10+5);
    shadow->setColor(sf::Color::Black);

    auto title = mGUI.newLabel();
    title->setFont(cf::Application::getResources().getFont("Assets/Fonts/sansation.ttf"));
    title->setString("Tehos");
    title->setCharacterSize(60);
    title->setPosition(400-shadow->cf::Text::getSize().x/2,10);
    title->setColor(sf::Color::White);

    auto buttonPlay = mGUI.newButton();
    buttonPlay->setPosition(sf::Vector2f(400-175,100));
    buttonPlay->setTexture(cf::Application::getResources().getTexture("Assets/Textures/gui.png"));
    buttonPlay->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonPlay->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonPlay->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonPlay->setFont(cf::Application::getResources().getFont("Assets/Fonts/sansation.ttf"));
    buttonPlay->setString("Play");
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
    buttonQuit->setString("Quit");
    buttonQuit->setColor(sf::Color::Black);
    buttonQuit->setCallback([&] ()
    {
        requestClear();
    },0);
    buttonQuit->setCallback([&] ()
    {
    },1);

}

bool MenuState::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,cf::Application::getWindow());
    return true;
}

bool MenuState::update(sf::Time dt)
{
    mGUI.update();
    return true;
}

void MenuState::render()
{
    cf::Application::getWindow().draw(mGUI);
}

void MenuState::toGameMode()
{
    requestPop();
    requestPush(GameModeState::getID());
}
