#include "pch.h"
#include "MBomb.h"
#include "resource.h"

CImageList MBomb::m_Images;

MBomb::MBomb(int x, int y):GameObject(x, y){}

MBomb::~MBomb() {}

BOOL MBomb::Draw(CDC* pDC, BOOL bPause)
{
    if (!bPause) {
        m_ptPos.y -= 8;
    }

    if (m_ptPos.y < -BOMB_HEIGHT) {
        return FALSE;
    }

    m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

    return TRUE;
}


BOOL MBomb::LoadImage()
{
    // TODO: 在此处添加实现代码.
    return GameObject::LoadImage(m_Images, IDB_BITMAP5, RGB(0,0,0), 10, 20, 1);
}


CRect MBomb::GetRect()
{
    // TODO: 在此处添加实现代码.
    return CRect(m_ptPos, CPoint(m_ptPos.x+BOMB_HEIGHT, m_ptPos.y+BOMB_HEIGHT));
}
