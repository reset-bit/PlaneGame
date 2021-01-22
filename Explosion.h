#pragma once
#include "GameObject.h"
class Explosion :
    public GameObject
{
public:
    Explosion(int x, int y);
    ~Explosion();
    BOOL Draw(CDC* pDC, BOOL bPause);
    static BOOL LoadImage();
    CRect GetRect();
private:
    static CImageList m_Images;
    // ͼ�������Ĳ�������
    int m_nProcess;
    static const int EXPLOSION_WIDTH = 66;
};

