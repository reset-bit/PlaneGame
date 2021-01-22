#include "pch.h"
#include "EBomb.h"
#include "Resource.h"
#include "Base.h"

CImageList EBomb::m_Images;

EBomb::EBomb(int x, int y) :GameObject(x, y){}

EBomb::~EBomb() {}

// ���Ƶл��ڵ�
BOOL EBomb::Draw(CDC* pDC, BOOL bPause)
{
    if (!bPause) {
        m_ptPos.y += 8;
    }

    if (m_ptPos.y > GAME_HEIGHT) {
        return FALSE;
    }
    if (m_ptPos.y < EBOMB_HEIGHT) {
        return FALSE;
    }

    // 0ͼ��������m_ptPosҪ���Ƶ�ͼ��λ�ã�ILD_TRANSPARENT͸���Ļ���ͼ�񣬲����Ǳ���ɫ
    m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
    
    return TRUE;
}


BOOL EBomb::LoadImage()
{
    return GameObject::LoadImage(m_Images, IDB_BITMAP2, RGB(0, 0, 0), 8, 8, 1);
}


CRect EBomb::GetRect()
{
    return CRect(m_ptPos, CPoint(m_ptPos.x + EBOMB_HEIGHT, m_ptPos.y + EBOMB_HEIGHT));
}
