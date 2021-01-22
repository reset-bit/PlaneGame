#include "pch.h"
#include "Explosion.h"
#include "resource.h"

CImageList Explosion::m_Images;

Explosion::Explosion(int x, int y):GameObject(x, y){
	m_nProcess = 0;
}

Explosion::~Explosion() {}

BOOL Explosion::Draw(CDC* pDC, BOOL bPause)
{
	if (m_nProcess == 9) {
		m_nProcess = 0;
		return FALSE;
	}

	m_Images.Draw(pDC, m_nProcess, m_ptPos, ILD_TRANSPARENT);
	m_nProcess++;

	return TRUE;
}


BOOL Explosion::LoadImage()
{
	// TODO: 在此处添加实现代码.
	return GameObject::LoadImage(m_Images, IDB_BITMAP4, RGB(0,0,0), 66, 66, 8);
}


CRect Explosion::GetRect()
{
	// TODO: 在此处添加实现代码.
	return CRect(m_ptPos, CPoint(m_ptPos.x+EXPLOSION_WIDTH, m_ptPos.y+EXPLOSION_WIDTH));
}
