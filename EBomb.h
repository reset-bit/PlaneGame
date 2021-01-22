#pragma once
#include "GameObject.h"

class EBomb :
    public GameObject
{
public:
    EBomb(int x, int y);
    ~EBomb();
    // ���Ƶл��ڵ�
    BOOL Draw(CDC* pDC, BOOL bPause);
    static BOOL LoadImage();
    CRect GetRect();
private:
    static CImageList m_Images;
    //ֵ����ʵͼƬ��С�й�
    static const int EBOMB_HEIGHT = 8;
};

