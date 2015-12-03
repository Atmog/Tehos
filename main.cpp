#include "Application/System.hpp"
#include "Application/Application.hpp"

#include "Game/Game.hpp"

#include <iostream>

/// ADD YOUR STATES HERE

#include "States/SplashScreen.hpp"
#include "States/Menu.hpp"
#include "States/GameState.hpp"
#include "States/FinalState.hpp"
#include "States/Help.hpp"
#include "States/Settings.hpp"
#include "States/Pause.hpp"
#include "States/Bonus.hpp"

/// ADD YOUR STATES HERE

int main()
{
    try
    {
        std::string appName = "Tehos";

        app::System::init(appName);
        Game::init();


        app::System::getWindow().create(800,600,appName,sf::Style::Close);


        /// ADD YOUR TEXTURE HERE
        if (!app::System::getResources().loadTexture("Cursor","Assets/Textures/cursor.png"))
        {
            app::System::getLog() << "Texture Cursor Failed";
            std::cout << "Texture Cursor failed" << std::endl;
            return 0;
        }
        if (!app::System::getResources().loadTexture("Skeleton","Assets/Textures/skeleton.png"))
        {
            app::System::getLog() << "Texture Skeleton Failed";
            std::cout << "Texture Skeleton failed" << std::endl;
            return 0;
        }
        if (!app::System::getResources().loadTexture("Soldier","Assets/Textures/soldier.png"))
        {
            app::System::getLog() << "Texture Soldier Failed";
            std::cout << "Texture Soldier failed" << std::endl;
            return 0;
        }
        if (!app::System::getResources().loadTexture("Weapons","Assets/Textures/weapons.png"))
        {
            app::System::getLog() << "Texture Weapons Failed";
            std::cout << "Texture Weapons failed" << std::endl;
            return 0;
        }
        if (!app::System::getResources().loadTexture("Map","Assets/Textures/map.png"))
        {
            app::System::getLog() << "Texture Map Failed";
            std::cout << "Texture Map failed" << std::endl;
            return 0;
        }
        if (!app::System::getResources().loadTexture("GUI","Assets/Textures/gui.png"))
        {
            app::System::getLog() << "Texture GUI Failed";
            std::cout << "Texture GUI failed" << std::endl;
            return 0;
        }
        if (!app::System::getResources().loadTexture("Help","Assets/Textures/helpBox.png"))
        {
            app::System::getLog() << "Texture h Failed";
            std::cout << "Texture h failed" << std::endl;
            return 0;
        }

        /// ADD YOUR FONT HERE
        if (!app::System::getResources().loadFont("Sansation","Assets/Fonts/sansation.ttf"))
        {
            app::System::getLog() << "Font Sansation Failed";
            std::cout << "Font Sansation failed" << std::endl;
            return 0;
        }

        app::System::getWindow().setMouseCursorTexture(app::System::getResources().getTexture("Cursor"));
        app::System::getWindow().useCustomMouseCursor();

        app::Application app;
        app.registerState<SplashScreen>(SplashScreen::getID());
        app.registerState<Menu>(Menu::getID());
        app.registerState<GameState>(GameState::getID());
        app.registerState<FinalState>(FinalState::getID());
        app.registerState<Help>(Help::getID());
        app.registerState<Settings>(Settings::getID());
        app.registerState<Pause>(Pause::getID());
        app.registerState<Bonus>(Bonus::getID());
        app.setState(SplashScreen::getID());
        app.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    Game::release();
    app::System::release();
    return EXIT_SUCCESS;
}
