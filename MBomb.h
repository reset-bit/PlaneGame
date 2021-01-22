#pragma once
#include "GameObject.h"
class MBomb :
    public GameObject
{
public:
    MBomb(int x, int y);
    ~MBomb();
    BOOL Draw(CDC* pDC, BOOL bPause);
    static BOOL LoadImage();
    CRect GetRect();
private:
    static CImageList m_Images;
    static const int BOMB_HEIGHT = 20;
};

