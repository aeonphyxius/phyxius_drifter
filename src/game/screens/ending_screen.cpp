#include "ending_screen.h"
#include "raylib.h"

void EndingScreen::InitScreen(void)
{
// TODO: Initialize ENDING screen variables here!
    m_framesCounter = 0;
    m_finishScreen = 0;
}
void EndingScreen::UpdateScreen(void)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        m_finishScreen = 1;
        PlaySound(fxCoin);
    }
}

void EndingScreen::DrawScreen(void)
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    DrawTextEx(font, "ENDING SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
}

void EndingScreen::UnloadScreen(void)
{

}

int EndingScreen::FinishScreen(void)
{
    return  m_finishScreen;
}