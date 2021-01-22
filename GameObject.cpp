#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(int x, int y) :m_ptPos(x, y) {}

GameObject::~GameObject() {}

CPoint GameObject::GetPoint()
{
    // TODO: �ڴ˴����ʵ�ִ���.
    return m_ptPos;
}

BOOL GameObject::LoadImage(CImageList& imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial)
{
    // TODO: �ڴ˴����ʵ�ִ���.
    CBitmap bmp;
    if (!bmp.LoadBitmap(bmpID)) {
        return FALSE;
    }
    if (!imgList.Create(cx, cy, ILC_COLOR24 | ILC_MASK, nInitial, 0)) {
        return FALSE;
    }

    imgList.Add(&bmp, crMask);
    return 0;
}
