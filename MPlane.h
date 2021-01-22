#pragma once
#include "GameObject.h"
class MPlane :
    public GameObject
{
public:
    MPlane();
    ~MPlane();
    BOOL Draw(CDC* pDC, BOOL bPause);
    BOOL DrawOther(CDC* pDC, BOOL bPause);
    static BOOL LoadImage(int playerid);
    CRect GetRect();
    int GetHorMotion();
    int GetVerMotion();
    void SetHorMotion(int nMotion);
    void SetVerMotion(int nMotion);
    BOOL Fried();
    static const int MPLANE_WIDTH = 50;
    static const int MPLANE_HEIGHT = 60;
private:
    static CImageList m_Images;
    static CImageList m_ImagesOther;
    int m_nHorMotion;
    int m_nVerMotion;
    int m_nWait;
};

