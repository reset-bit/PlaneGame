#pragma once
#include "GameObject.h"
class EPlane :
    public GameObject
{
public:
    EPlane(CRect rc);
    ~EPlane();
    BOOL Draw(CDC* pDC, BOOL bPause);
    static BOOL LoadImage();
    CRect GetRect();
    BOOL Fired(CRect rc);
private:
    static CImageList m_Images;
    int m_nspeed;
    // ∑¢…‰—” ±
    int m_nWait;
    static const int EPLANE_HEIGHT = 34;
};

