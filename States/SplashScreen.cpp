#include "SplashScreen.hpp"

std::string SplashScreen::getID()
{
    return "SplashScreen";
}

SplashScreen::SplashScreen(app::StateManager& manager) : app::State(manager)
{
    load();
    mState = 0;
}

void SplashScreen::load()
{
    mLeader.setPosition(850,575);
    mLeader.setPatrolPos(sf::Vector2f(-4000,575));
    mLeader.setSpeed(300);

    if (!mSFML.loadFromFile("Assets/Atmog/libs.png"))
    {
        app::System::getLog() << "Error : SFML texture";
    }
    if (!mLudum.loadFromFile("Assets/Atmog/ld.png"))
    {
        app::System::getLog() << "Error : Ludum texture";
    }
    if (!mAtmog.loadFromFile("Assets/Atmog/backgroundSplashscreen.png"))
    {
        app::System::getLog() << "Error : BgSplash texture";
    }
    if (!mHeyTexture.loadFromFile("Assets/Textures/hey.png"))
    {
        app::System::getLog() << "Error : Hey texture";
    }
    if (!mAtmogFont.loadFromFile("Assets/Atmog/atmogFont.ttf"))
    {
        app::System::getLog() << "Error : Atmog font";
    }

    mSprite.setTexture(mLudum);
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
    mSprite.setPosition(400,300);

    mHey.setTexture(mHeyTexture);
    mHey.setPosition(10,600-32-50);

    mAtmogText.setFont(mAtmogFont);
    mAtmogText.setColor(sf::Color::White);
    mAtmogText.setCharacterSize(200);
    mAtmogText.setString(L"Atmög");
    mAtmogText.setPosition(800,200);
    mAtmogShadow.setFont(mAtmogFont);
    mAtmogShadow.setColor(sf::Color::Black);
    mAtmogShadow.setCharacterSize(200);
    mAtmogShadow.setString(L"Atmög");
    mAtmogText.setPosition(400 - mAtmogText.getGlobalBounds().width /2,mAtmogText.getPosition().y);
    mAtmogShadow.setPosition(mAtmogText.getPosition().x + 5.f,mAtmogText.getPosition().y + 5.f);

    mMap.setTexture(app::System::getResources().getTexture("Map"));
    mMap.setPosition(800,0);
}

bool SplashScreen::update(sf::Time dt)
{
    mTime += dt;

    if (mState != 3)
    {
        mLeader.update(dt);
        mWalkTime += dt;

        if (mState == 0 && mWalkTime >= sf::seconds(0.4) && mLeader.getPosition().x > -30)
        {
            Game::playSound("Assets/Sounds/walk.wav");
            mWalkTime -= sf::seconds(0.4);
        }
        if (mState == 1)
        {
            if (mWalkTime >= sf::seconds(0.25) && mLeader.getPosition().x < 830)
            {
                Game::playSound("Assets/Sounds/walk.wav");
                mWalkTime -= sf::seconds(0.25);
            }
            mLeader.updateDirection(sf::Vector2f(4000,575));
        }
        if (mState == 2)
        {
            if (mWalkTime >= sf::seconds(0.1))
            {
                Game::playSound("Assets/Sounds/walk.wav");
                mWalkTime -= sf::seconds(0.1);
            }
            for (unsigned int i = 0; i < mEnemies.size(); i++)
            {
                mEnemies[i].update(dt);
            }
            std::sort(mEnemies.begin(), mEnemies.end(),
            [](FakeEnemy a, FakeEnemy b) -> bool
            {
                return a.getPosition().y - a.getOrigin().y + a.getBounds().height < b.getPosition().y - b.getOrigin().y + b.getBounds().height;
            });
        }
    }
    if (mState == 3)
    {
        /// EDIT HERE

        requestPop();
        requestPush(GameState::getID());
        Game::playMusic("Assets/Musics/menu.ogg");
        requestPush(Menu::getID());

        /// EDIT HERE
    }

    if (mTime >= sf::seconds(3) && mState == 0)
    {
        mState = 1;
        mSprite.setTexture(mSFML);
        mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
        mSprite.setPosition(400,300);
        mLeader.setPosition(-50,575);
        mLeader.setPatrolPos(sf::Vector2f(4000,580));
        mLeader.setSpeed(450);
        mWalkTime = sf::Time::Zero;
        Game::playSound("Assets/Sounds/hover.wav");
        Game::playSound("Assets/Sounds/click.wav");
    }
    if (mTime >= sf::seconds(5) && mState == 1)
    {
        mState = 2;
        mSprite.setTexture(mAtmog);
        mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
        mSprite.setPosition(400,300);
        mLeader.setPosition(850,575);
        mLeader.setPatrolPos(sf::Vector2f(-4000,575));
        mLeader.setSpeed(450);
        mWalkTime = sf::Time::Zero;

        for (int i = 0; i < 20; i++)
        {
            FakeEnemy e;
            float x = 950 + app::Math::random<float>(-50.f,50.f);
            float y = 575 + app::Math::random<float>(-25.f,25.f);
            e.setPosition(x,y);
            e.setPatrolPos(sf::Vector2f(-4000,y));
            e.setSpeed(450);
            mEnemies.push_back(e);
        }
    }
    if (mTime >= sf::seconds(7) && mState == 2)
    {
        mState = 3;
        mEnemies.clear();
    }

    return true;
}

void SplashScreen::render()
{
    app::System::getWindow().clear(sf::Color::White);
    app::System::getWindow().draw(mSprite);
    app::System::getWindow().draw(mLeader);
    if (mState == 1 && mTime < sf::seconds(3.5))
    {
        app::System::getWindow().draw(mHey);
    }
    if (mState == 2)
    {
        app::System::getWindow().draw(mAtmogShadow);
        app::System::getWindow().draw(mAtmogText);
        for (unsigned int i = 0; i < mEnemies.size(); i++)
        {
            app::System::getWindow().draw(mEnemies[i]);
        }
    }
}
