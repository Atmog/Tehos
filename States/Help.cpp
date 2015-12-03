#include "Help.hpp"

std::string Help::getID()
{
    return "Help";
}

Help::Help(app::StateManager& manager) : app::State(manager)
{
    load();
}

void Help::load()
{
    auto buttonQuit = mGUI.createButton();
    buttonQuit->setPosition(sf::Vector2f(400-175,500));
    buttonQuit->setTexture(app::System::getResources().getTexture("GUI"));
    buttonQuit->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonQuit->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonQuit->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonQuit->setFont(app::System::getResources().getFont("Sansation"));
    buttonQuit->setString(Game::getTextLang("return"));
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

    std::string mouseStr = Game::getTextLang("mouse1") + "\n" + Game::getTextLang("mouse2") + "\n" + Game::getTextLang("mouse3");
    auto mouseLabel = mGUI.createLabelBox();
    mouseLabel->setString(mouseStr);
    mouseLabel->setFont(app::System::getResources().getFont("Sansation"));
    mouseLabel->setTexture(app::System::getResources().getTexture("Help"));
    mouseLabel->setTextureRect(sf::IntRect(0,0,500,150),0);
    mouseLabel->setTextureRect(sf::IntRect(0,0,500,150),1);
    mouseLabel->setCharacterSize(30);
    mouseLabel->setColor(sf::Color::Black);

    std::string keyStr = Game::getTextLang("key1") + "\n" + Game::getTextLang("key2");
    auto keyLabel = mGUI.createLabelBox();
    keyLabel->setString(keyStr);
    keyLabel->setFont(app::System::getResources().getFont("Sansation"));
    keyLabel->setTexture(app::System::getResources().getTexture("Help"));
    keyLabel->setTextureRect(sf::IntRect(0,0,500,150),0);
    keyLabel->setTextureRect(sf::IntRect(0,0,500,150),1);
    keyLabel->setCharacterSize(30);
    keyLabel->setColor(sf::Color::Black);

    mouseLabel->setPosition(175,75);
    keyLabel->setPosition(175,250);
}

bool Help::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,app::System::getWindow());
    return true;
}

bool Help::update(sf::Time dt)
{
    mGUI.update();
    return true;
}

void Help::render()
{
    app::System::getWindow().draw(mGUI);
}
