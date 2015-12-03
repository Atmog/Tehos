#include "Pause.hpp"

std::string Pause::getID()
{
    return "Pause";
}

Pause::Pause(app::StateManager& manager) : app::State(manager)
{
    load();
}

void Pause::load()
{
    auto buttonPlay = mGUI.createButton();
    buttonPlay->setPosition(sf::Vector2f(400-175,300-75-50));
    buttonPlay->setTexture(app::System::getResources().getTexture("GUI"));
    buttonPlay->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonPlay->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonPlay->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonPlay->setFont(app::System::getResources().getFont("Sansation"));
    buttonPlay->setString(Game::getTextLang("play"));
    buttonPlay->setColor(sf::Color::Black);
    buttonPlay->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/click.wav");
        switchToGame();
    },0);
    buttonPlay->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);

    auto buttonMenu = mGUI.createButton();
    buttonMenu->setPosition(sf::Vector2f(400-175,300+50));
    buttonMenu->setTexture(app::System::getResources().getTexture("GUI"));
    buttonMenu->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonMenu->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonMenu->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonMenu->setFont(app::System::getResources().getFont("Sansation"));
    buttonMenu->setString(Game::getTextLang("tomenu"));
    buttonMenu->setColor(sf::Color::Black);
    buttonMenu->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/click.wav");
        switchToMenu();
    },0);
    buttonMenu->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);

    mShape.setFillColor(sf::Color(76,76,76,76));
    mShape.setSize(sf::Vector2f(800,600));
}

bool Pause::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,app::System::getWindow());
    return false;
}

bool Pause::update(sf::Time dt)
{
    mGUI.update();
    return false;
}

void Pause::render()
{
    app::System::getWindow().draw(mShape);
    app::System::getWindow().draw(mGUI);
}

void Pause::switchToGame()
{
    requestPop();
}

void Pause::switchToMenu()
{
    requestPop();
    Game::playMusic("Assets/Sounds/menu.ogg");
    requestPush(Menu::getID());
}
