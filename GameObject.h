#pragma once
class GameObject:
	public CObject
{
public:
	GameObject(int x=0, int y=0);
	~GameObject();
	virtual BOOL Draw(CDC* pDC, BOOL bPause)=0;
	virtual CRect GetRect()=0;
	CPoint GetPoint();
protected:
	// ×óÉÏ½Ç×ø±ê
	CPoint m_ptPos;
	static BOOL LoadImage(CImageList& imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);
};

