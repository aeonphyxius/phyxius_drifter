#include "game/screens/screen.h"

class LogoScreen : public Screen 
{
public:
    virtual void InitScreen();
    virtual void UpdateScreen();
    virtual void DrawScreen();
    virtual void UnloadScreen();
    virtual int FinishScreen();

private:
    int m_logoPositionX = 0;
    int m_logoPositionY = 0;

    int m_lettersCount = 0;

    int m_topSideRecWidth = 0;
    int m_leftSideRecHeight = 0;

    int m_bottomSideRecWidth = 0;
    int m_rightSideRecHeight = 0;

    int m_state = 0;              // Logo animation states
    float m_alpha = 1.0f;    
};