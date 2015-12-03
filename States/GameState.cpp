#include "GameState.hpp"
#include "../Application/StateManager.hpp"

std::string GameState::getID()
{
    return "GameState";
}

GameState::GameState(app::StateManager& manager) : app::State(manager)
{
    mSellerActive = false;
    mSellerWeapon = 1;
    mSellerMenuY = 600;

    mIsPaused = false;

    load();
}

void GameState::load()
{
    mMapSprite.setTexture(app::System::getResources().getTexture("Map"));

    if (!mSellerTexture.loadFromFile("Assets/Textures/seller.png"))
        app::System::getLog() << "Texture Seller Failed";
    mSellerSprite.setTexture(mSellerTexture);
    mSellerSprite.setPosition(320,480);

    if (!mSellerWeapons.loadFromFile("Assets/Textures/sellerWeapons.png"))
        app::System::getLog() << "Texture SellerWeapons Failed";
    mSellerItems.setTexture(mSellerWeapons);
    mSellerItems.setPosition(290,600);
    mSellerItems.setTextureRect(sf::IntRect(0,(mSellerWeapon - 1) * 55,220,55));

    if (!mSellerArrows.loadFromFile("Assets/Textures/sellerArrows.png"))
        app::System::getLog() << "Texture SellerArrows Failed";
    mSellerLeft.setTexture(mSellerArrows);
    mSellerLeft.setTextureRect(sf::IntRect(0,0,55,55));
    mSellerLeft.setPosition(290,600);
    mSellerRight.setTexture(mSellerArrows);
    mSellerRight.setTextureRect(sf::IntRect(55,0,55,55));
    mSellerRight.setPosition(455,600);

    if (!mHUDTexture.loadFromFile("Assets/Textures/hud.png"))
        app::System::getLog() << "Texture HUD Failed";
    mHUD.setTexture(mHUDTexture);
    mHUD.setPosition(800-240,0);

    mMoneyText.setFont(app::System::getResources().getFont("Sansation"));
    mMoneyText.setPosition(800-240+30,5);
    mMoneyText.setCharacterSize(15);
    mMoneyText.setColor(sf::Color::White);

    mSoldiersText.setFont(app::System::getResources().getFont("Sansation"));
    mSoldiersText.setPosition(800-120+10,5);
    mSoldiersText.setCharacterSize(15);
    mSoldiersText.setColor(sf::Color::White);

    mEnemiesText.setFont(app::System::getResources().getFont("Sansation"));
    mEnemiesText.setPosition(800-120+10,27);
    mEnemiesText.setCharacterSize(15);
    mEnemiesText.setColor(sf::Color::White);

    mTimeText.setFont(app::System::getResources().getFont("Sansation"));
    mTimeText.setPosition(800-240+30,27);
    mTimeText.setCharacterSize(15);
    mTimeText.setColor(sf::Color::White);
}

void GameState::onActivate()
{
    mIsPaused = false;
}

bool GameState::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            pause();
        }
    }

    Game::handleEvent(event);
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (mSellerActive == true && mSellerItems.getGlobalBounds().contains(app::System::getWindow().getMousePosition()))
            {
                if (mSellerLeft.getGlobalBounds().contains(app::System::getWindow().getMousePosition()))
                {
                    if (mSellerWeapon > 1)
                    {
                        mSellerWeapon--;
                    }
                    mSellerItems.setTextureRect(sf::IntRect(0,(mSellerWeapon -1) * 55,220,55));
                }
                else if (mSellerRight.getGlobalBounds().contains(app::System::getWindow().getMousePosition()))
                {
                    if (mSellerWeapon < 4)
                    {
                        mSellerWeapon++;
                    }
                }
                mWeapon.setType(mSellerWeapon);
                mSellerItems.setTextureRect(sf::IntRect(0,(mSellerWeapon -1) * 55,220,55));
            }
            else if (mSellerSprite.getGlobalBounds().contains(app::System::getWindow().getMousePosition()))
            {
                if (mSellerActive == false)
                {
                    mSellerActive = true;
                    mSellerMenuY = 600;
                    mWeapon.setType(mSellerWeapon);
                    mSellerItems.setTextureRect(sf::IntRect(0,(mSellerWeapon -1) * 55,220,55));
                }
                else
                {
                    mSellerActive = false;
                    mWeapon.setType(Weapon::Nothing);
                }
            }
            else
            {
                if (Game::getMoney() >= 100 + mWeapon.getPrice())
                {
                    Game::spendMoney(100+mWeapon.getPrice());
                    if (!Game::getEntityManager().spawnSoldier(app::System::getWindow().getMousePosition(),mWeapon.getType()))
                    {
                        Game::earnMoney(100+mWeapon.getPrice());
                    }
                }
                if (Game::getMoney() >= mWeapon.getPrice() && Game::getEntityManager().giveWeaponToSoldier(app::System::getWindow().getMousePosition(),mWeapon.getType())
                && mWeapon.getPrice() != 0)
                {
                    Game::spendMoney(mWeapon.getPrice());
                }
            }
        }
    }
    return true;
}

bool GameState::update(sf::Time dt)
{
    // TODO : Lang
    mMoneyText.setString(app::IO::toString(Game::getMoney()) + "$");
    mSoldiersText.setString(Game::getTextLang("soldiers") + " : " + app::IO::toString(Game::getEntityManager().getSoldierCount()));
    mEnemiesText.setString(Game::getTextLang("enemies") + " : " + app::IO::toString(Game::getEntityManager().getEnemyCount()));
    mTimeText.setString(Game::getTextLang("time") + " : " + app::IO::toString(Game::getTime()));

    if (mSellerActive)
    {
        if (mSellerMenuY > 545)
        {
            mSellerMenuY -= 100 * dt.asSeconds();

            mSellerItems.setPosition(mSellerItems.getPosition().x,mSellerMenuY);
            mSellerLeft.setPosition(mSellerLeft.getPosition().x,mSellerMenuY);
            mSellerRight.setPosition(mSellerRight.getPosition().x,mSellerMenuY);
        }
        else if (mSellerMenuY < 545)
        {
            mSellerMenuY = 545;

            mSellerItems.setPosition(mSellerItems.getPosition().x,mSellerMenuY);
            mSellerLeft.setPosition(mSellerLeft.getPosition().x,mSellerMenuY);
            mSellerRight.setPosition(mSellerRight.getPosition().x,mSellerMenuY);
        }
    }
    else
    {
        if (mSellerMenuY > 600)
        {
            mSellerMenuY = 600;

            mSellerItems.setPosition(mSellerItems.getPosition().x,mSellerMenuY);
            mSellerLeft.setPosition(mSellerLeft.getPosition().x,mSellerMenuY);
            mSellerRight.setPosition(mSellerRight.getPosition().x,mSellerMenuY);
        }
        else if (mSellerMenuY < 600)
        {
            mSellerMenuY += 100 * dt.asSeconds();

            mSellerItems.setPosition(mSellerItems.getPosition().x,mSellerMenuY);
            mSellerLeft.setPosition(mSellerLeft.getPosition().x,mSellerMenuY);
            mSellerRight.setPosition(mSellerRight.getPosition().x,mSellerMenuY);
        }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Game::update(dt);

        if (Game::getBaseLife() <= 0)
        {
            switchToFinal();
        }
    }
    return true;
}

void GameState::render()
{
    app::System::getWindow().draw(mMapSprite);

    // Only draw if ACTIVE
    if (mManager.getSize() == 1 || mIsPaused)
    {

        Game::render();

        app::System::getWindow().draw(mSellerSprite);
        if (Game::getBaseLife() < 1000)
        {
            sf::RectangleShape bg;
            bg.setPosition(400 - 60,505);
            bg.setSize(sf::Vector2f(120,7));
            bg.setFillColor(sf::Color::Red);
            bg.setOutlineThickness(1);
            bg.setOutlineColor(sf::Color::Black);
            app::System::getWindow().draw(bg);
            sf::RectangleShape l;
            l.setPosition(400 - 60,505);
            l.setSize(sf::Vector2f(120.f * static_cast<float>(Game::getBaseLife()) / static_cast<float>(1000),7));
            l.setFillColor(sf::Color::Green);
            app::System::getWindow().draw(l);
        }

        app::System::getWindow().draw(mSellerItems);
        app::System::getWindow().draw(mSellerLeft);
        app::System::getWindow().draw(mSellerRight);

        app::System::getWindow().draw(mHUD);

        app::System::getWindow().draw(mMoneyText);
        app::System::getWindow().draw(mSoldiersText);
        app::System::getWindow().draw(mEnemiesText);
        app::System::getWindow().draw(mTimeText);

        mWeapon.setPosition(app::System::getWindow().getMousePosition() - sf::Vector2f(3,3));
        app::System::getWindow().draw(mWeapon);

    }
}

void GameState::switchToFinal()
{
    Game::playMusic("Assets/Musics/final.ogg");

    mSellerActive = false;
    mSellerWeapon = 1;
    mSellerMenuY = 600;
    mMoneyText.setString("");
    mSoldiersText.setString("");
    mEnemiesText.setString("");
    mTimeText.setString("");
    mWeapon.setType(Weapon::Type::Nothing);
    mIsPaused = false;
    mSellerItems.setTextureRect(sf::IntRect(0,(mSellerWeapon - 1) * 55,220,55));

    // Awesome Transition Begin

    sf::RectangleShape mShape;
    mShape.setSize(sf::Vector2f(800,600));

    Game::playSound("Assets/Sounds/explosion.wav");

    sf::Time explosionTimer;
    sf::Time timer;
    sf::Clock clock;
    while (timer< sf::seconds(1))
    {
        sf::Time dt = clock.restart();
        timer += dt;
        explosionTimer += dt;
        if (explosionTimer >= sf::seconds(0.1) && timer < sf::seconds(0.5))
        {
            explosionTimer = sf::Time::Zero;
            Game::playSound("Assets/Sounds/explosion.wav");
        }

        float value = 256 * 1 / (1- timer.asSeconds());
        mShape.setFillColor(sf::Color(value,value,value,value));

        // Render
        app::System::getWindow().clear();

        render();

        app::System::getWindow().draw(mShape);

        app::System::getWindow().display();
    }


    // Transition end

    requestPush(FinalState::getID());
}

void GameState::pause()
{
    mIsPaused = true;
    requestPush(Pause::getID());
}
