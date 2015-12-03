#ifndef FINALSTATE_HPP
#define FINALSTATE_HPP

#include <vector>
#include "../Game/FakeEnemy.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "../Application/System.hpp"
#include "../Application/State.hpp"

#include "../SimpleGui/Container.hpp"
#include "../SimpleGui/Button.hpp"

#include "GameState.hpp"
#include "Menu.hpp"

class FinalState : public app::State
{
    public:
        static std::string getID();
        typedef std::unique_ptr<FinalState> Ptr;

    public:
        FinalState(app::StateManager& manager);

        void load();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

        void switchToGame();
        void switchToMenu();

    private:
        SGUI::Container mGUI;
        std::vector<FakeEnemy> mEnemies;
};

#endif // FINALSTATE_HPP
