#include "FinalState.hpp"

std::string FinalState::getID()
{
    return "FinalState";
}

FinalState::FinalState(app::StateManager& manager) : app::State(manager)
{
    load();
}

void FinalState::load()
{
    auto lbl = mGUI.createLabelBox();
    lbl->setFont(app::System::getResources().getFont("Sansation"));
    lbl->setString(Game::getTextLang("score"));
    lbl->setCharacterSize(30);
    lbl->setPosition(400-175,200);
    lbl->setColor(sf::Color::Black);
    lbl->setTexture(app::System::getResources().getTexture("GUI"));
    lbl->setTextureRect(sf::IntRect(0,0,350,75),0);
    lbl->setTextureRect(sf::IntRect(0,0,350,75),1);
    lbl->setTextureRect(sf::IntRect(0,0,350,75),2);

    auto lbl2 = mGUI.createLabelBox();
    lbl2->setFont(app::System::getResources().getFont("Sansation"));
    lbl2->setString(app::IO::toString(Game::getTime()));
    lbl2->setCharacterSize(30);
    lbl2->setPosition(400-175,300);
    lbl2->setColor(sf::Color::White);
    lbl2->setTexture(app::System::getResources().getTexture("GUI"));
    lbl2->setTextureRect(sf::IntRect(0,0,350,75),0);
    lbl2->setTextureRect(sf::IntRect(0,0,350,75),1);
    lbl2->setTextureRect(sf::IntRect(0,0,350,75),2);

    auto buttonPlay = mGUI.createButton();
    buttonPlay->setPosition(sf::Vector2f(400-175,400));
    buttonPlay->setTexture(app::System::getResources().getTexture("GUI"));
    buttonPlay->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonPlay->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonPlay->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonPlay->setFont(app::System::getResources().getFont("Sansation"));
    buttonPlay->setString(Game::getTextLang("playagain"));
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
    buttonMenu->setPosition(sf::Vector2f(400-175,500));
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

    for (unsigned int i = 0; i < 60; i++)
    {
        mEnemies.push_back(FakeEnemy());
    }

    // Now we have all our data from Game
    // we can reset its data
    Game::startNewGame();
}

bool FinalState::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,app::System::getWindow());
    return false;
}

bool FinalState::update(sf::Time dt)
{
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

void FinalState::render()
{
    for (unsigned int i = 0; i < mEnemies.size(); i++)
    {
        app::System::getWindow().draw(mEnemies[i]);
    }
    app::System::getWindow().draw(mGUI);
}

void FinalState::switchToGame()
{
    requestPop();
    Game::playMusic("Assets/Musics/game.ogg");
    Game::addGame();
}

void FinalState::switchToMenu()
{
    requestPop();
    requestPush(Menu::getID());
    Game::playMusic("Assets/Musics/menu.ogg");
}
