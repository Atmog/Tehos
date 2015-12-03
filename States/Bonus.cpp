#include "Bonus.hpp"

std::string Bonus::getID()
{
    return "Bonus";
}

Bonus::Bonus(app::StateManager& manager) : app::State(manager)
{
    load();
}

void Bonus::load()
{
    auto buttonQuit = mGUI.createButton();
    buttonQuit->setPosition(sf::Vector2f(400-175,500));
    buttonQuit->setTexture(app::System::getResources().getTexture("GUI"));
    buttonQuit->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonQuit->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonQuit->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonQuit->setFont(app::System::getResources().getFont("Sansation"));
    buttonQuit->setString(Game::getTextLang("quit"));
    buttonQuit->setColor(sf::Color::Black);
    buttonQuit->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/click.wav");
        requestPop();
    },0);
    buttonQuit->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);

}

bool Bonus::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,app::System::getWindow());
    return true;
}

bool Bonus::update(sf::Time dt)
{
    mGUI.update();
    return true;
}

void Bonus::render()
{
    app::System::getWindow().draw(mGUI);
}
