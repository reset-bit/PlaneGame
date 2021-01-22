#pragma once
#include "GameObject.h"

class EBomb :
    public GameObject
{
public:
    EBomb(int x, int y);
    ~EBomb();
    // 绘制敌机炮弹
    BOOL Draw(CDC* pDC, BOOL bPause);
    static BOOL LoadImage();
    CRect GetRect();
private:
    static CImageList m_Images;
    //值与真实图片大小有关
    static const int EBOMB_HEIGHT = 8;
};

