#if !defined(SCREEN_H)
#define SCREEN_H

#include "raylib.h"

// extern Font;
// extern Music;
// extern Sound;

class Screen
{
public:
    enum GameScreen { NONE = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING };
    

    
public:
    virtual void InitScreen() = 0;
    virtual void UpdateScreen() = 0;
    virtual void DrawScreen() = 0;
    virtual void UnloadScreen() = 0;
    virtual int  FinishScreen() = 0;

protected:
    Font font;
    Music music;
    Sound fxCoin;
    int m_framesCounter = 0;
    int m_finishScreen = 0;
};

#endif  // !defined(SCREEN_H)