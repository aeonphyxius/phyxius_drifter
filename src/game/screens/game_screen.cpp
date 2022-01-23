#include "game/screens/game_screen.h"
#include "raylib.h"

void GameScreen::InitScreen()
{
    m_framesCounter = 0;
    m_finishScreen = 0;
}
void GameScreen::UpdateScreen()
{
    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        m_finishScreen = 1;
        PlaySound(fxCoin);
    }
}

void GameScreen::DrawScreen()
{
     // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    DrawTextEx(font, "GAMEPLAY SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

void GameScreen::UnloadScreen()
{
}

int GameScreen::FinishScreen()
{
    return  m_finishScreen;
}