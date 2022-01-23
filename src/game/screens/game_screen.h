#if !defined(GAME_SCREEN_H)
#define GAME_SCREEN_H

#include "game/screens/screen.h"

class GameScreen : public Screen 
{
public:
    virtual void InitScreen();
    virtual void UpdateScreen();
    virtual void DrawScreen();
    virtual void UnloadScreen();
    virtual int  FinishScreen();
};

#endif  // !defined(GAME_SCREEN_H)