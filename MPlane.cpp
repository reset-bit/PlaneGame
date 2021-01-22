#include "pch.h"
#include "MPlane.h"
#include "resource.h"
#include "Base.h"

CImageList MPlane::m_Images;
CImageList MPlane::m_ImagesOther;

MPlane::MPlane() {
	m_nWait = 0;

	//初始位置
	m_ptPos.x = 500;
	m_ptPos.y = 400;

	m_nHorMotion = 0;
	m_nVerMotion = 0;
}

MPlane::~MPlane() {}

BOOL MPlane::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 5) {
		m_nWait = 0;
	}
	if (!bPause) {
		m_ptPos.x += m_nHorMotion * 6;
		m_ptPos.y += m_nVerMotion * 6;
	}

	//限制战机不能飞出用户区
	if (m_ptPos.x >= GAME_WIDTH - MPLANE_WIDTH) {
		m_ptPos.x = GAME_WIDTH - MPLANE_WIDTH;
	}
	
	if (m_ptPos.y >= GAME_HEIGHT - MPLANE_HEIGHT) {
		m_ptPos.y = GAME_HEIGHT - MPLANE_HEIGHT;
	}

	if (m_ptPos.x <= 0) {
		m_ptPos.x = 0;
	}

	if (m_ptPos.y <= 0) {
		m_ptPos.y = 0;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


BOOL MPlane::DrawOther(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 5) {
		m_nWait = 0;
	}
	if (!bPause) {
		m_ptPos.x += m_nHorMotion * 6;
		m_ptPos.y += m_nVerMotion * 6;
	}

	//限制战机不能飞出用户区
	if (m_ptPos.x >= GAME_WIDTH - MPLANE_WIDTH) {
		m_ptPos.x = GAME_WIDTH - MPLANE_WIDTH;
	}

	if (m_ptPos.y >= GAME_HEIGHT - MPLANE_HEIGHT) {
		m_ptPos.y = GAME_HEIGHT - MPLANE_HEIGHT;
	}

	if (m_ptPos.x <= 0) {
		m_ptPos.x = 0;
	}

	if (m_ptPos.y <= 0) {
		m_ptPos.y = 0;
	}

	m_ImagesOther.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


BOOL MPlane::LoadImage(int playerid)
{
	if (playerid == 1) {
		return GameObject::LoadImage(m_Images, IDB_BITMAP6, RGB(0, 0, 0), 50, 60, 1);
	}
	else {
		return GameObject::LoadImage(m_ImagesOther, IDB_BITMAP7, RGB(0, 0, 0), 50, 60, 1);
	}
}


CRect MPlane::GetRect()
{
	// TODO: 在此处添加实现代码.
	return CRect(m_ptPos, CPoint(m_ptPos.x+MPLANE_WIDTH, m_ptPos.y+MPLANE_HEIGHT));
}


int MPlane::GetHorMotion()
{
	// TODO: 在此处添加实现代码.
	return m_nHorMotion;
}


int MPlane::GetVerMotion()
{
	// TODO: 在此处添加实现代码.
	return m_nVerMotion;
}


void MPlane::SetHorMotion(int nMotion)
{
	// TODO: 在此处添加实现代码.
	m_nHorMotion = nMotion;
}


void MPlane::SetVerMotion(int nMotion)
{
	// TODO: 在此处添加实现代码.
	m_nVerMotion = nMotion;
}


BOOL MPlane::Fried()
{
	// TODO: 在此处添加实现代码.
	if (m_nWait == 0) {
		return TRUE;
	}
	else{
		return FALSE;
	}
}
