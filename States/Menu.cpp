#include "Menu.hpp"
#include "../Application/StateManager.hpp"

std::string Menu::getID()
{
    return "Menu";
}

Menu::Menu(app::StateManager& manager) : app::State(manager)
{
    mIsActive = true;
    load();
}

void Menu::load()
{
    auto shadow = mGUI.createLabel();
    shadow->setFont(app::System::getResources().getFont("Sansation"));
    shadow->setString("Tehos");
    shadow->setCharacterSize(60);
    shadow->setPosition(400-shadow->SGUI::Text::getSize().x/2+5,10+5);
    shadow->setColor(sf::Color::Black);

    auto title = mGUI.createLabel();
    title->setFont(app::System::getResources().getFont("Sansation"));
    title->setString("Tehos");
    title->setCharacterSize(60);
    title->setPosition(400-shadow->SGUI::Text::getSize().x/2,10);
    title->setColor(sf::Color::White);

    auto buttonPlay = mGUI.createButton();
    buttonPlay->setPosition(sf::Vector2f(400-175,100));
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
        Game::addGame();
        mIsActive = false;
        requestPop();
        Game::playMusic("Assets/Musics/game.ogg");
    },0);
    buttonPlay->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);

    auto buttonBonus = mGUI.createButton();
    buttonBonus->setPosition(sf::Vector2f(400-175,200));
    buttonBonus->setTexture(app::System::getResources().getTexture("GUI"));
    buttonBonus->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonBonus->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonBonus->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonBonus->setFont(app::System::getResources().getFont("Sansation"));
    buttonBonus->setString(Game::getTextLang("bonus"));
    buttonBonus->setColor(sf::Color::Black);
    buttonBonus->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/click.wav");
        mIsActive = false;
        requestPush(Bonus::getID());
    },0);
    buttonBonus->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);


    // Enable if we have time
    buttonBonus->disable();


    auto buttonHelp = mGUI.createButton();
    buttonHelp->setPosition(sf::Vector2f(400-175,300));
    buttonHelp->setTexture(app::System::getResources().getTexture("GUI"));
    buttonHelp->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonHelp->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonHelp->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonHelp->setFont(app::System::getResources().getFont("Sansation"));
    buttonHelp->setString(Game::getTextLang("help"));
    buttonHelp->setColor(sf::Color::Black);
    buttonHelp->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/click.wav");
        mIsActive = false;
        requestPush(Help::getID());
    },0);
    buttonHelp->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);

    auto buttonSettings = mGUI.createButton();
    buttonSettings->setPosition(sf::Vector2f(400-175,400));
    buttonSettings->setTexture(app::System::getResources().getTexture("GUI"));
    buttonSettings->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonSettings->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonSettings->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonSettings->setFont(app::System::getResources().getFont("Sansation"));
    buttonSettings->setString(Game::getTextLang("settings"));
    buttonSettings->setColor(sf::Color::Black);
    buttonSettings->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/click.wav");
        mIsActive = false;
        requestPush(Settings::getID());
    },0);
    buttonSettings->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);

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
        requestClear();
    },0);
    buttonQuit->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);


    for (unsigned int i = 0; i < 20; i++)
    {
        mEnemies.push_back(FakeEnemy());
    }
}

void Menu::onActivate()
{
    mIsActive = true;
}

bool Menu::handleEvent(sf::Event const& event)
{
    if (mIsActive)
        mGUI.handleEvent(event,app::System::getWindow());
    return false;
}

bool Menu::update(sf::Time dt)
{
    if (mIsActive)
        mGUI.update();
    for (unsigned int i = 0; i < mEnemies.size(); i++)
    {
        mEnemies[i].update(dt);
    }
    std::sort(mEnemies.begin(), mEnemies.end(),
    [](FakeEnemy a, FakeEnemy b) -> bool
    {
        return a.getPosition().y - a.getOrigin().y + a.getBounds().height < b.getPosition().y - b.getOrigin().y + b.getBounds().height;
    });
    return false;
}

void Menu::render()
{
    for (unsigned int i = 0; i < mEnemies.size(); i++)
    {
        app::System::getWindow().draw(mEnemies[i]);
    }
    // Only draw if ACTIVE
    if (mManager.getSize() == 2)
    {
        app::System::getWindow().draw(mGUI);
    }
}
