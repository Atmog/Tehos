#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../SimpleGui/Container.hpp"
#include "../SimpleGui/Button.hpp"

#include "GameState.hpp"
#include "Help.hpp"
#include "Settings.hpp"
#include "Bonus.hpp"

#include "../Game/FakeEnemy.hpp"

class Menu : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<Menu> Ptr;

    public:
        Menu(app::StateManager& manager);

        void load();
        void onActivate();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    private:
        SGUI::Container mGUI;
        bool mIsActive;
        std::vector<FakeEnemy> mEnemies;
};

#endif // MENU_HPP
