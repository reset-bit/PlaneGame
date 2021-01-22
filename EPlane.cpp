#include "pch.h"
#include "EPlane.h"
#include "resource.h"
#include "Base.h"

CImageList EPlane::m_Images;

EPlane::EPlane(CRect rc) {
    m_ptPos.x = rand() % (rc.Width() - EPLANE_HEIGHT) + 1;
    m_ptPos.y = -EPLANE_HEIGHT;
    
    m_nspeed = rand() % 4 + 2;
    m_nWait = 0;
}

EPlane::~EPlane() {}

BOOL EPlane::Draw(CDC* pDC, BOOL bPause)
{
    m_nWait++;
    if (m_nWait > 20) {//发射炮弹速度
        m_nWait = 0;
    }
    if (!bPause) {
        m_ptPos.y += m_nspeed;
    }

    if (m_ptPos.y > GAME_HEIGHT + EPLANE_HEIGHT)
        return FALSE;
    if (m_ptPos.y < -EPLANE_HEIGHT)
        return FALSE;

    m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

    return TRUE;
}


BOOL EPlane::LoadImage()
{
    // TODO: 在此处添加实现代码.
    return GameObject::LoadImage(m_Images, IDB_BITMAP3, RGB(0,0,0), 36, 34, 1);
}


CRect EPlane::GetRect()
{
    // TODO: 在此处添加实现代码.
    return CRect(m_ptPos, CPoint(m_ptPos.x + EPLANE_HEIGHT, m_ptPos.y + EPLANE_HEIGHT));
}


BOOL EPlane::Fired(CRect rc)
{
    if (m_nWait == 0) {
        CPoint epos = GetPoint();
        if (epos.y > 0 || epos.y < rc.bottom) {
            return TRUE;
        }
    }
    return FALSE;
}
