#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include <vector>
#include <iostream>

#include "Menu.hpp"
#include "GameState.hpp"

class SplashScreen : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<SplashScreen> Ptr;

    public:
        SplashScreen(app::StateManager& manager);

        void load();

        bool update(sf::Time dt);
        void render();

    private:
        sf::Time mTime;

        sf::Sprite mSprite;
        sf::Sprite mMap;
        sf::Sprite mHey;

        sf::Texture mHeyTexture;

        sf::Texture mLudum;
        sf::Texture mSFML;
        sf::Texture mAtmog;

        sf::Font mAtmogFont;

        sf::Text mAtmogText;
        sf::Text mAtmogShadow;

        FakeEnemy mLeader;
        std::vector<FakeEnemy> mEnemies;
        int mState;
        sf::Time mWalkTime;
};

#endif // SPLASHSCREEN_HPP
