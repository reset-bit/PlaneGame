
// PlaneGameView.h: CPlaneGameView 类的接口
//

#pragma once

class MPlane;
class CPlaneGameView : public CView
{
protected: // 仅从序列化创建
	CPlaneGameView() noexcept;
	DECLARE_DYNCREATE(CPlaneGameView)

// 特性
public:
	CPlaneGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	BOOL InitGame();
	// 设备DC
	CClientDC* m_pDC;
	// 内存DC
	CDC* m_pMemDC;
	// 内存位图
	CBitmap* m_pMemBitmap;
	MPlane* m_pMe;
	MPlane* m_pMeOther;
	CObList m_objList[5];
	CRect rc;
	enum ObjType { enEPlane, enMBomb1,enMBomb2, enEBomb, enExplosion };
	void UpdateFrame();
	void UpdateInterface();
public:
	CButton start;//普通模式
	CButton easy;// 无敌模式
	CButton oneplayer;//单人模式
	CButton twoplayers;//双人模式
	CButton regame;
	CButton exit;
protected:
	void OnStartDown();
	void OnReGameDown();
	void OnExitDown();
	void OnEasyDown();
	void StopGame();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
protected:
	// 标记战机是否被击毁
	BOOL exist1;
	BOOL exist2;
	// 标记是否无敌模式
	BOOL invincible;
	BOOL twoPeople;
	// 按钮控件id
	int* idOfButton;
	int numOfDeadEPlane1;
	int numOfDeadEPlane2;
	void OnOneDown();
	void OnTwoDown();
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	bool isA;
	bool isS;
	bool isD;
	bool isW;
	void BlowUpPlane(MPlane* pMe, int playerid);
	int p2MoveDriction;
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

