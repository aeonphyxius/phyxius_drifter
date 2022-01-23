/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


#include "game/screens/screen.h"    
#include "game/screens/title_screen.h"
#include "game/screens/logo_screen.h"
#include "game/screens/ending_screen.h"
#include "game/screens/game_screen.h"
#include "game.h"
#include "raylib.h"
#include <map>
#include <iostream>
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
Screen::GameScreen currentScreen = Screen::LOGO;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static Screen::GameScreen transFromScreen;
static Screen::GameScreen transToScreen;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // Change to screen, no transition effect

static void TransitionToScreen(int screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

static void UpdateDrawFrame(void);          // Update and draw one frame


static std::map <Screen::GameScreen, Screen*> screens_map;

// Screen currentScreen;
//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    
    screens_map.insert ( std::make_pair<Screen::GameScreen, Screen*> (Screen::LOGO,new LogoScreen() ) ); 
    screens_map.insert ( std::make_pair<Screen::GameScreen, Screen*> (Screen::TITLE,new TitleScreen() ) ); 
    screens_map.insert ( std::make_pair<Screen::GameScreen, Screen*> (Screen::GAMEPLAY,new GameScreen() ) ); 
    screens_map.insert ( std::make_pair<Screen::GameScreen, Screen*> (Screen::ENDING,new EndingScreen() ) ); 
    
    
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib game template");

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/mecha.png");
    music = LoadMusicStream("resources/ambient.ogg");
    fxCoin = LoadSound("resources/coin.wav");

    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    // Setup and init first screen
    currentScreen = Screen::LOGO;

    // InitLogoScreen();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    screens_map[currentScreen]->UnloadScreen();
    screens_map.clear();

    // Unload global data loaded
    UnloadFont(font);
    UnloadMusicStream(music);
    UnloadSound(fxCoin);

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void ChangeToScreen(int screen)
{
    screens_map[currentScreen]->UnloadScreen();
    screens_map[static_cast<Screen::GameScreen>(screen)]->InitScreen();

    currentScreen = static_cast<Screen::GameScreen> (screen);
}

// Request transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = static_cast<Screen::GameScreen> (screen);
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;
            screens_map[transFromScreen]->UnloadScreen();
            screens_map[transToScreen]->InitScreen();

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            // transFromScreen;
            // transToScreen;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        screens_map[currentScreen]->UpdateScreen();
        switch(currentScreen)
        {
            case Screen::LOGO:
            {
                // UpdateLogoScreen();
                // logo_screen.UpdateScreen();

                if (screens_map[currentScreen]->FinishScreen()) TransitionToScreen(Screen::TITLE);

            } break;
            case Screen::TITLE:
            {
                // UpdateTitleScreen();
                // title_screen.UpdateScreen();

                if (screens_map[currentScreen]->FinishScreen() == 1) TransitionToScreen(Screen::OPTIONS);
                else if (screens_map[currentScreen]->FinishScreen() == 2) TransitionToScreen(Screen::GAMEPLAY);

            } break;
            // case Screen.OPTIONS:
            // {
            //     UpdateOptionsScreen();

            //     if (FinishOptionsScreen()) TransitionToScreen(Screen.TITLE);

            // } break;
            case Screen::GAMEPLAY:
            {
                // UpdateGameplayScreen();
                if (screens_map[currentScreen]->FinishScreen() == 1) TransitionToScreen(Screen::ENDING);
                if (screens_map[currentScreen]->FinishScreen() == 2) TransitionToScreen(Screen::TITLE);
                // if (FinishGameplayScreen() == 1) TransitionToScreen(Screen::ENDING);
                //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);

            } break;
            case Screen::ENDING:
            {
                // UpdateEndingScreen();

                // if (FinishEndingScreen() == 1) TransitionToScreen(Screen::TITLE);
                if (screens_map[currentScreen]->FinishScreen() == 1) TransitionToScreen(Screen::TITLE);

            } break;
            default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);
        screens_map[currentScreen]->DrawScreen();

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
