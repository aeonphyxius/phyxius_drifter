#include "title_screen.h"
#include "raylib.h"

void TitleScreen::InitScreen()
{
    m_framesCounter = 0;
    m_finishScreen = 0;
}
void TitleScreen::UpdateScreen()
{
     // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        m_finishScreen = 2;   // GAMEPLAY
        PlaySound(fxCoin);
    }
}

void TitleScreen::DrawScreen()
{
 // TODO: Draw TITLE screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    DrawTextEx(font, "TITLE SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
}

void TitleScreen::UnloadScreen()
{

}

int TitleScreen::FinishScreen()
{
    return  m_finishScreen;
}