#if !defined(TITLE_SCREEN_H)
#define TITLE_SCREEN_H

#include "game/screens/screen.h"

class TitleScreen : public Screen 
{
public:
    virtual void InitScreen();
    virtual void UpdateScreen();
    virtual void DrawScreen();
    virtual void UnloadScreen();
    virtual int  FinishScreen();
};

#endif  // !defined(TITLE_SCREEN_H)