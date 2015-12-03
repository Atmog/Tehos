#include "Settings.hpp"

std::string Settings::getID()
{
    return "Settings";
}

Settings::Settings(app::StateManager& manager) : app::State(manager)
{
    mMusicVol = Game::getMusicVolume();
    mSoundVol = Game::getSoundVolume();

    load();
}

void Settings::load()
{
    auto buttonFull = mGUI.createButton();
    buttonFull->setPosition(sf::Vector2f(400-175,200));
    buttonFull->setTexture(app::System::getResources().getTexture("GUI"));
    buttonFull->setTextureRect(sf::IntRect(0,0,350,75),0);
    buttonFull->setTextureRect(sf::IntRect(0,75,350,75),1);
    buttonFull->setTextureRect(sf::IntRect(0,150,350,75),2);
    buttonFull->setFont(app::System::getResources().getFont("Sansation"));
    buttonFull->setString(Game::getTextLang("full") + " : OFF");
    buttonFull->setColor(sf::Color::Black);
    buttonFull->setCallback([&] () { },0);
    buttonFull->setCallback([&] ()
    {
    },1);
    buttonFull->disable();

    mMusic = mGUI.createSlider();
    mMusic->setPosition(sf::Vector2f(400+25,300));
    mMusic->setTexture(app::System::getResources().getTexture("GUI"));
    mMusic->setTextureRect(sf::IntRect(0,225,150,75),0);
    mMusic->setTextureRect(sf::IntRect(0,300,150,75),1);
    mMusic->setTextureRect(sf::IntRect(0,375,150,75),2);
    mMusic->setCursorSize(sf::Vector2f(20,75));
    mMusic->setInterval(0,100);
    mMusic->setValue<int>(mMusicVol);
    mMusic->setCallback([&] () {  },0);

    mSound = mGUI.createSlider();
    mSound->setPosition(sf::Vector2f(400+25,400));
    mSound->setTexture(app::System::getResources().getTexture("GUI"));
    mSound->setTextureRect(sf::IntRect(0,225,150,75),0);
    mSound->setTextureRect(sf::IntRect(0,300,150,75),1);
    mSound->setTextureRect(sf::IntRect(0,375,150,75),2);
    mSound->setCursorSize(sf::Vector2f(20,75));
    mSound->setInterval(0,100);
    mSound->setValue<int>(mSoundVol);
    mSound->setCallback([&] () { },0);

    auto lblMusic = mGUI.createLabelBox();
    lblMusic->setFont(app::System::getResources().getFont("Sansation"));
    lblMusic->setString(Game::getTextLang("music") + " : ");
    lblMusic->setCharacterSize(30);
    lblMusic->setPosition(400-175,300);
    lblMusic->setColor(sf::Color::White);
    lblMusic->setTexture(app::System::getResources().getTexture("GUI"));
    lblMusic->setTextureRect(sf::IntRect(0,225,150,75),0);
    lblMusic->setTextureRect(sf::IntRect(0,225,150,75),1);
    lblMusic->setTextureRect(sf::IntRect(0,225,150,75),2);

    auto lblSound = mGUI.createLabelBox();
    lblSound->setFont(app::System::getResources().getFont("Sansation"));
    lblSound->setString(Game::getTextLang("sound") + " : ");
    lblSound->setCharacterSize(30);
    lblSound->setPosition(400-175,400);
    lblSound->setColor(sf::Color::White);
    lblSound->setTexture(app::System::getResources().getTexture("GUI"));
    lblSound->setTextureRect(sf::IntRect(0,225,150,75),0);
    lblSound->setTextureRect(sf::IntRect(0,225,150,75),1);
    lblSound->setTextureRect(sf::IntRect(0,225,150,75),2);

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
        requestPop();
        Game::playSound("Assets/Sounds/click.wav");
    },0);
    buttonQuit->setCallback([&] ()
    {
        Game::playSound("Assets/Sounds/hover.wav");
    },1);
}

bool Settings::handleEvent(sf::Event const& event)
{
    mGUI.handleEvent(event,app::System::getWindow());

    return false;
}

bool Settings::update(sf::Time dt)
{
    mGUI.update();

    if (mMusicVol != mMusic->getValueInt())
    {
        mMusicVol = mMusic->getValueInt();
        Game::setMusicVolume(mMusicVol);
    }
    if (mSoundVol != mSound->getValueInt())
    {
        mSoundVol = mSound->getValueInt();
        Game::setSoundVolume(mSoundVol);
    }

    return true;
}

void Settings::render()
{
    app::System::getWindow().draw(mGUI);
}
