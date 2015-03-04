#include "Lib/Application.hpp"

#include "State/IntroState.hpp"
#include "State/MenuState.hpp"
#include "State/GameState.hpp"
#include "State/GameModeState.hpp"
#include "State/GameEndState.hpp"

int main()
{
    try
    {
        cf::Application app;

        // -> Chargement des resources
        cf::Application::getResources().loadTexture("Assets/Textures/playerblue.png");
        cf::Application::getResources().getTexture("Assets/Textures/playerblue.png").setSmooth(true);
        cf::Application::getResources().loadTexture("Assets/Textures/playerred.png");
        cf::Application::getResources().getTexture("Assets/Textures/playerred.png").setSmooth(true);
        cf::Application::getResources().loadTexture("Assets/Textures/tileset.png");
        cf::Application::getResources().loadTexture("Assets/Textures/basered.png");
        cf::Application::getResources().loadTexture("Assets/Textures/baseblue.png");
        cf::Application::getResources().loadTexture("Assets/Textures/gui.png");
        //cf::Application::getResources().loadTexture("Assets/Textures/weapons.png");
        cf::Application::getResources().loadTexture("Assets/Textures/explosion.png");
        cf::Application::getResources().getTexture("Assets/Textures/explosion.png").setSmooth(true);

        cf::Application::getResources().loadFont("Assets/Fonts/sansation.ttf");

        // -> Parametrage de la fenetre
        // -> Gestion des Log
        // -> Gestion de l'audio
        // -> Gestion des Statistics
        // -> ...
        // -> Enfin bref, tout ce qui est plus ou moins une partie de l'Application

        app.getWindow().create(800,600,sf::Style::Close);

        app.getStates().registerState<IntroState>(IntroState::getID());
        app.getStates().registerState<MenuState>(MenuState::getID());
        app.getStates().registerState<GameState>(GameState::getID());
        app.getStates().registerState<GameModeState>(GameModeState::getID());
        app.getStates().registerState<GameEndState>(GameEndState::getID());

        app.getStates().pushState(IntroState::getID());

        app.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
