#include "screen.h"

class EndingScreen : public Screen 
{
public:
    virtual void InitScreen();
    virtual void UpdateScreen();
    virtual void DrawScreen();
    virtual void UnloadScreen();
    virtual int FinishScreen();


};