#ifndef GAMEMODESTATE_HPP
#define GAMEMODESTATE_HPP

#include "../Lib/State.hpp"

#include "../Lib/Container.hpp"

#include "MenuState.hpp"
#include "GameState.hpp"

#include "../Game/World.hpp"

class GameModeState : public cf::State
{
    public:
        static std::string getID() { return "GameModeState"; }

        typedef std::unique_ptr<GameModeState> Ptr;

    public:
        GameModeState(cf::StateManager& manager);

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

        static World::GameMode getGameMode(std::string dataString);
        static std::string getGameModeString(World::GameMode gamemode);

    protected:
        void toGame();
        void toMenu();

    protected:
        World::GameMode mGameMode;
        cf::Container mGUI;

};

#endif // GAMEMODESTATE_HPP
