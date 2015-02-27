#include "Lib/Application.hpp"

#include "State/IntroState.hpp"
#include "State/MenuState.hpp"
#include "State/GameState.hpp"

int main()
{
    try
    {
        cf::Application app;

        /*

        -> Chargement des resources
        -> Parametrage de la fenetre
        -> Gestion des Log
        -> Gestion de l'audio
        -> Gestion des Statistics
        -> ...
        -> Enfin bref, tout ce qui est plus ou moins une partie de l'Application

        */

        app.getWindow().create(800,600,sf::Style::Close);

        app.getStates().registerState<IntroState>(IntroState::getID());
        app.getStates().registerState<MenuState>(MenuState::getID());
        app.getStates().registerState<GameState>(GameState::getID());

        app.getStates().pushState(IntroState::getID());

        app.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
