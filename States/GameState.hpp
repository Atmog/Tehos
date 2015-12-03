#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../Game/Game.hpp"
#include "../Game/Weapon.hpp"

#include "FinalState.hpp"
#include "Pause.hpp"

class GameState : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<GameState> Ptr;

    public:
        GameState(app::StateManager& manager);

        void load();

        void onActivate();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

        void switchToFinal();
        void pause();

    private:

        sf::Texture mSellerTexture;
        sf::Texture mSellerWeapons;
        sf::Texture mSellerArrows;
        sf::Texture mHUDTexture;

        sf::Sprite mMapSprite;
        sf::Sprite mSellerSprite;
        sf::Sprite mSellerItems;
        sf::Sprite mSellerLeft;
        sf::Sprite mSellerRight;
        sf::Sprite mHUD;

        sf::Text mMoneyText;
        sf::Text mSoldiersText;
        sf::Text mEnemiesText;
        sf::Text mTimeText;

        Weapon mWeapon;

        bool mSellerActive;
        int mSellerWeapon;
        float mSellerMenuY;

        bool mIsPaused;
};

#endif // GAMESTATE_HPP
