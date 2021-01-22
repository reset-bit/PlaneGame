
// PlaneGameView.cpp: CPlaneGameView 类的实现
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlaneGame.h"
#endif

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "EBomb.h"
#include "EPlane.h"
#include "Explosion.h"
#include "MBomb.h"
#include "MPlane.h"
#include "resource.h"
#include "WinUser.h"
#include "Base.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDB_BUTTONSTART, OnStartDown)//点击开始游戏按钮
	ON_BN_CLICKED(IDB_BUTTONREGAME, OnReGameDown)
	ON_BN_CLICKED(IDB_BUTTONEXIT, OnExitDown)
	ON_BN_CLICKED(IDB_BUTTONEASY, OnEasyDown)
	ON_BN_CLICKED(IDB_BUTTONONE, OnOneDown)
	ON_BN_CLICKED(IDB_BUTTONTWO, OnTwoDown)
	ON_WM_TIMER()
	ON_WM_INITMENU()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView() noexcept
{
	// TODO: 在此处添加构造代码

}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘图

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序


BOOL CPlaneGameView::InitGame()
{
	//--------双缓冲--------
	m_pDC = new CClientDC(this);//设备DC
	m_pMemDC = new CDC;//内存DC
	m_pMemDC->CreateCompatibleDC(m_pDC);

	numOfDeadEPlane1 = 0;
	numOfDeadEPlane2 = 0;

	return TRUE;
}


void CPlaneGameView::StopGame()
{
	KillTimer(1);

	delete m_pMe;
	m_pMe = NULL;

	if (m_pMeOther != NULL) {
		delete m_pMeOther;
		m_pMeOther = NULL;
	}

	delete m_pMemDC;
	m_pMemDC = NULL;
	
	delete m_pDC;
	m_pDC = NULL;
	
	delete m_pMemBitmap;
	m_pMemBitmap = NULL;

	PostMessage(WM_QUIT, 0, 0);//退出程序
}


//判断是否按下某键
int GetKey(int nVirKey) {
	return (GetKeyState(nVirKey) & 0x8000) ? 1 : 0;
}


void CPlaneGameView::UpdateFrame()
{
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->LoadBitmap(IDB_BITMAP1);
	BITMAP bitmap;
	m_pMemBitmap->GetBitmap(&bitmap);//得到背景图信息
	m_pMemDC->SelectObject(m_pMemBitmap);//位图选入内存DC

	//MPlane
	if (invincible == FALSE) {//普通模式
		if (exist1) {
			m_pMe->Draw(m_pMemDC, FALSE);
		}
		if (twoPeople && exist2) {
			m_pMeOther->DrawOther(m_pMemDC, FALSE);
		}
		if((exist1 == FALSE && twoPeople == FALSE)||(exist1 == FALSE && exist2 == FALSE)) {
			//Game over
			exist1 = FALSE;
			if (twoPeople) {
				exist2 = FALSE;
			}
			this->KillTimer(1);
			MessageBox(_T("     游戏结束！    "),_T("提示信息"));
			regame.ShowWindow(1);
			exit.ShowWindow(1);
		}
	}
	else {//无敌模式
		CString str = _T("在本模式下，击毁100架敌机即取得胜利");
		m_pMemDC->SetBkMode(TRANSPARENT);
		m_pMemDC->SetTextColor(RGB(255, 255, 255));
		m_pMemDC->TextOut(70, 20, str);

		if (numOfDeadEPlane1 == 100 || numOfDeadEPlane2 == 100) {
			this->KillTimer(1);
			CString str = (numOfDeadEPlane1 == 100) ? _T("游戏结束！祝贺玩家1取得胜利！") : _T("游戏结束！祝贺玩家2取得胜利！");
			MessageBox(str, _T("提示信息"));
			regame.ShowWindow(1);
			exit.ShowWindow(1);
		}
		else {
			m_pMe->Draw(m_pMemDC, FALSE);
			if (twoPeople) {
				m_pMeOther->DrawOther(m_pMemDC, FALSE);
			}
		}
	}
	
	
	//EPlane,MBomb1,MBomb2,EBomb,Explosion
	for (int i = 0;i < 5;i++) {
		POSITION pos1 = NULL, pos2 = NULL;
		for (pos1 = m_objList[i].GetHeadPosition();(pos2 = pos1) != NULL;) {
			GameObject* pobj = (GameObject*)m_objList[i].GetNext(pos1);
			if (!pobj->Draw(m_pMemDC, FALSE)) {
				m_objList[i].RemoveAt(pos2);
				delete pobj;
			}
		}
	}

	CString str = _T("键盘上下左右键控制飞机移动，回车键开火，shift+回车键进入反击模式");
	m_pMemDC->SetBkMode(TRANSPARENT);
	m_pMemDC->SetTextColor(RGB(52, 168, 83));
	m_pMemDC->TextOut(70, 40, str);

	str = _T("已击毁敌机架数：");
	m_pMemDC->SetBkMode(TRANSPARENT);
	m_pMemDC->SetTextColor(RGB(52, 168, 83));
	m_pMemDC->TextOut(70, 60, str);

	str.Format(_T("%d"), numOfDeadEPlane1);
	m_pMemDC->TextOut(70, 80, str);

	if (twoPeople) {
		str = _T("键盘WASD键控制飞机移动，空格键开火，capslock+空格键进入反击模式");
		m_pMemDC->SetBkMode(TRANSPARENT);
		m_pMemDC->SetTextColor(RGB(186, 104, 200));
		m_pMemDC->TextOut(70, 120, str);

		str = _T("已击毁敌机架数：");
		m_pMemDC->SetBkMode(TRANSPARENT);
		m_pMemDC->SetTextColor(RGB(186, 104, 200));
		m_pMemDC->TextOut(70, 140, str);

		str.Format(_T("%d"), numOfDeadEPlane2);
		m_pMemDC->TextOut(70, 160, str);
	}

	GetClientRect(&rc);
	//复制内存DC到设备DC
	m_pDC->StretchBlt(0, 0, rc.right, rc.bottom, m_pMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


void CPlaneGameView::UpdateInterface()
{
	static int nCreator = rand() % 5 + 5;//控制难度
	if (nCreator <= 0) {//随机产生敌机
		nCreator = rand() % 5 + 5;
		m_objList[enEPlane].AddTail(new EPlane(rc));
	}
	--nCreator;

	if (twoPeople == FALSE && exist1 == FALSE) {
		return;
	}
	else if (twoPeople == TRUE && exist1 == FALSE && exist2 == FALSE) {
		return;
	}

	if (exist1) {
		//移动战机
		for (int i = 0;i < 4;++i) {
			int op = 0;
			m_pMe->SetVerMotion(0);
			m_pMe->SetHorMotion(0);

			op = GetKey(VK_UP);
			if (op == 1) {
				m_pMe->SetVerMotion(-1);
			}

			op = GetKey(VK_DOWN);
			if (op == 1) {
				m_pMe->SetVerMotion(1);
			}

			op = GetKey(VK_RIGHT);
			if (op == 1) {
				m_pMe->SetHorMotion(1);
			}

			op = GetKey(VK_LEFT);
			if (op == 1) {
				m_pMe->SetHorMotion(-1);
			}
		}
		//战机开火
		if (GetKey(VK_RETURN) == 1) {
			if (NULL != m_pMe && m_pMe->Fried()) {
				CPoint mp = m_pMe->GetPoint();
				m_objList[enMBomb1].AddTail(new MBomb(mp.x + 10, mp.y + 10));
				m_objList[enMBomb1].AddTail(new MBomb(mp.x + 30, mp.y + 10));
				if (GetKey(VK_SHIFT) == 1) {
					m_objList[enMBomb1].AddTail(new MBomb(mp.x - 10, mp.y + 10));
					m_objList[enMBomb1].AddTail(new MBomb(mp.x + 50, mp.y + 10));
				}
			}
		}
	}

	if (twoPeople) {
		if (exist2) {
			for (int i = 0;i < 4;++i) {
				int op = 0;
				m_pMeOther->SetVerMotion(0);
				m_pMeOther->SetHorMotion(0);

				op = (isW == true) ? 1 : 0;
				if (op == 1) {
					m_pMeOther->SetVerMotion(-1);
				}

				op = (isS == true) ? 1 : 0;
				if (op == 1) {
					m_pMeOther->SetVerMotion(1);
				}

				op = (isD == true) ? 1 : 0;
				if (op == 1) {
					m_pMeOther->SetHorMotion(1);
				}

				op = (isA == true) ? 1 : 0;
				if (op == 1) {
					m_pMeOther->SetHorMotion(-1);
				}

				//备用方案：针对大键盘数字5123移动
				//int op = 0;
				//m_pMeOther->SetVerMotion(0);
				//m_pMeOther->SetHorMotion(0);

				//op = GetKey(VK_NUMPAD5);
				//if (op == 1) {
				//	m_pMeOther->SetVerMotion(-1);
				//}

				//op = GetKey(VK_NUMPAD2);
				//if (op == 1) {
				//	m_pMeOther->SetVerMotion(1);
				//}

				//op = GetKey(VK_NUMPAD3);
				//if (op == 1) {
				//	m_pMeOther->SetHorMotion(1);
				//}

				//op = GetKey(VK_NUMPAD1);
				//if (op == 1) {
				//	m_pMeOther->SetHorMotion(-1);
				//}

			}

			if (GetKey(VK_SPACE) == 1) {
				if (NULL != m_pMeOther && m_pMeOther->Fried()) {
					CPoint mp = m_pMeOther->GetPoint();
					m_objList[enMBomb2].AddTail(new MBomb(mp.x + 10, mp.y + 10));
					m_objList[enMBomb2].AddTail(new MBomb(mp.x + 30, mp.y + 10));
					if (GetKey(VK_CAPITAL) == 1) {
						m_objList[enMBomb2].AddTail(new MBomb(mp.x - 10, mp.y + 10));
						m_objList[enMBomb2].AddTail(new MBomb(mp.x + 50, mp.y + 10));
					}
				}
			}
		}
	}

	//敌机开火
	CPoint mp = m_pMe->GetPoint();
	for (POSITION epos = m_objList[enEPlane].GetHeadPosition();epos != NULL;) {
		EPlane* tmpEPlane = (EPlane*)m_objList[enEPlane].GetNext(epos);

		if (tmpEPlane->Fired(rc) == TRUE) {
			CPoint ep = tmpEPlane->GetPoint();
			if (ep.y > 0 && ep.y < mp.y && ep.x > mp.x && ep.x < mp.x + MPlane::MPLANE_WIDTH) {
				m_objList[enEBomb].AddTail(new EBomb(ep.x + 10, ep.y + 10));
			}
		}
	}

	BlowUpPlane(m_pMe, 1);

	if (twoPeople) {
		BlowUpPlane(m_pMeOther, 2);
	}

	isW = false;
	isS = false;
	isD = false;
	isA = false;
}


void CPlaneGameView::BlowUpPlane(MPlane* pMe, int playerid)
{
	//击毁战机

	CPoint mp = pMe->GetPoint();
	CRect mRect = pMe->GetRect();
	//被敌机炮弹击中
	POSITION bpos1 = NULL, bpos2 = NULL;
	for (bpos1 = m_objList[enEBomb].GetHeadPosition();(bpos2 = bpos1) != NULL;) {
		EBomb* tmpEBomb = (EBomb*)m_objList[enEBomb].GetNext(bpos1);
		CRect tEBRect = tmpEBomb->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&tEBRect, mRect)) {//敌机炮弹与战机相交
			m_objList[enExplosion].AddTail(new Explosion(mp.x, mp.y));

			m_objList[enEBomb].RemoveAt(bpos2);
			delete tmpEBomb;

			if (invincible == FALSE) {
				if (playerid == 1) {
					exist1 = FALSE;
				}
				else {
					exist2 = FALSE;
				}
			}
			break;
		}
	}
	//与敌机相撞
	POSITION epos1 = NULL, epos2 = NULL;
	for (epos1 = m_objList[enEPlane].GetHeadPosition();(epos2 = epos1) != NULL;) {
		EPlane* tmpEPlane = (EPlane*)m_objList[enEPlane].GetNext(epos1);
		CRect tERect = tmpEPlane->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&tERect, mRect)) {//敌机与战机相交
			CPoint tep = tmpEPlane->GetPoint();
			m_objList[enExplosion].AddTail(new Explosion(tep.x, tep.y));

			m_objList[enEPlane].RemoveAt(epos2);
			delete tmpEPlane;
			if (playerid == 1) {
				++numOfDeadEPlane1;
			}
			else {
				++numOfDeadEPlane2;
			}

			if (invincible == FALSE) {
				if (playerid == 1) {
					exist1 = FALSE;
				}
				else {
					exist2 = FALSE;
				}
			}
			break;
		}
	}


	//击毁敌机

	int tmpmb = (playerid == 1) ? enMBomb1 : enMBomb2;
	POSITION mbpos1 = NULL, mbpos2 = NULL;
	for (mbpos1 = m_objList[tmpmb].GetHeadPosition();(mbpos2 = mbpos1) != NULL;) {
		MBomb* tmpMBomb = (MBomb*)m_objList[tmpmb].GetNext(mbpos1);
		CRect tMBRect = tmpMBomb->GetRect();

		POSITION epos1 = NULL, epos2 = NULL;
		for (epos1 = m_objList[enEPlane].GetHeadPosition();(epos2 = epos1) != NULL;) {
			EPlane* tmpEPlane = (EPlane*)m_objList[enEPlane].GetNext(epos1);
			CRect tERect = tmpEPlane->GetRect();
			CRect tmpRect;

			if (tmpRect.IntersectRect(&tERect, tMBRect) && tERect.top > 0) {//敌机与战机炮弹相交
				CPoint tep = tmpEPlane->GetPoint();
				m_objList[enExplosion].AddTail(new Explosion(tep.x, tep.y));

				m_objList[tmpmb].RemoveAt(mbpos2);
				delete tmpMBomb;

				m_objList[enEPlane].RemoveAt(epos2);
				delete tmpEPlane;
				if (playerid == 1) {
					++numOfDeadEPlane1;
				}
				else {
					++numOfDeadEPlane2;
				}
				break;
			}
		}
	}
}


int CPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)//产生基本结构和变量
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rc;
	GetClientRect(rc);

	idOfButton = new int[6];
	start.Create(L"普通模式", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(300, 280, 400, 330), this, IDB_BUTTONSTART);
	start.ShowWindow(SW_SHOWNORMAL);
	idOfButton[0] = start.GetDlgCtrlID();

	easy.Create(L"无敌模式", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(400, 280, 500, 330), this, IDB_BUTTONEASY);
	easy.ShowWindow(SW_SHOWNORMAL);
	idOfButton[1] = easy.GetDlgCtrlID();

	regame.Create(L"重新游戏", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(300, 280, 400, 330), this, IDB_BUTTONREGAME);
	regame.ShowWindow(SW_SHOWNORMAL);
	idOfButton[2] = regame.GetDlgCtrlID();

	exit.Create(L"退出游戏", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(400, 280, 500, 330), this, IDB_BUTTONEXIT);
	exit.ShowWindow(SW_SHOWNORMAL);
	idOfButton[3] = exit.GetDlgCtrlID();

	oneplayer.Create(L"单人模式", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(300, 280, 400, 330), this, IDB_BUTTONONE);
	oneplayer.ShowWindow(SW_SHOWNORMAL);
	idOfButton[4] = oneplayer.GetDlgCtrlID();

	twoplayers.Create(L"双人模式", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(400, 280, 500, 330), this, IDB_BUTTONTWO);
	twoplayers.ShowWindow(SW_SHOWNORMAL);
	idOfButton[5] = twoplayers.GetDlgCtrlID();

	regame.ShowWindow(0);
	exit.ShowWindow(0);
	oneplayer.ShowWindow(0);
	twoplayers.ShowWindow(0);

	return 0;
}


void CPlaneGameView::OnPaint()
{
	CPaintDC   dc(this);
	GetClientRect(rc);
	CDC   pDC;
	pDC.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpOld = pDC.SelectObject(&bmpBackground);

	dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &pDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


void CPlaneGameView::OnInitialUpdate()//初始化视图中控件
{
	CView::OnInitialUpdate();
	InitGame();
}


void CPlaneGameView::OnStartDown()
{
	MPlane::LoadImage(1);
	MPlane::LoadImage(2);
	MBomb::LoadImage();
	EPlane::LoadImage();
	EBomb::LoadImage();
	Explosion::LoadImage();

	m_pMe = new MPlane;
	m_pMeOther = new MPlane;
	invincible = FALSE;

	start.ShowWindow(0);
	easy.ShowWindow(0);
	oneplayer.ShowWindow(1);
	twoplayers.ShowWindow(1);
}


void CPlaneGameView::OnEasyDown()
{
	MPlane::LoadImage(1);
	MPlane::LoadImage(2);
	MBomb::LoadImage();
	EPlane::LoadImage();
	EBomb::LoadImage();
	Explosion::LoadImage();

	m_pMe = new MPlane;
	m_pMeOther = new MPlane;
	invincible = TRUE;
	
	start.ShowWindow(0);
	easy.ShowWindow(0);
	oneplayer.ShowWindow(1);
	twoplayers.ShowWindow(1);
}


void CPlaneGameView::OnOneDown()
{
	exist1 = TRUE;
	exist2 = FALSE;
	twoPeople = FALSE;

	oneplayer.ShowWindow(0);
	twoplayers.ShowWindow(0);

	SetTimer(1, 30, NULL);
}


void CPlaneGameView::OnTwoDown()
{
	//MPlane::LoadImage(2);

	exist1 = TRUE;
	exist2 = TRUE;
	twoPeople = TRUE;

	oneplayer.ShowWindow(0);
	twoplayers.ShowWindow(0);

	SetTimer(1, 30, NULL);
}


void CPlaneGameView::OnReGameDown()
{
	//清除现有数据
	for (int i = 0;i < 4;i++) {
		if (!m_objList[i].IsEmpty()) {
			POSITION pos;
			pos = m_objList[i].GetHeadPosition();
			if (pos != NULL) {
				m_objList[i].RemoveAll();
			}
		}
	}

	if (MessageBox(L"是否选择无敌模式？",L"提示信息", MB_YESNO) == IDYES) {
		invincible = TRUE;
	}
	else {
		invincible = FALSE;
	}

	InitGame();

	regame.ShowWindow(0);
	exit.ShowWindow(0);
	oneplayer.ShowWindow(1);
	twoplayers.ShowWindow(1);
}


void CPlaneGameView::OnExitDown()
{
	StopGame();
}


void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	UpdateFrame();
	UpdateInterface();

	CView::OnTimer(nIDEvent);
}


void CPlaneGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CWnd* pWnd;
	if (nType != SIZE_MINIMIZED)
	{
		for (int i = 0; i < 6; i++)
		{
			int n = idOfButton[i];
			pWnd = GetDlgItem(n);
			if (pWnd)
			{
				CRect rc;
				GetClientRect(rc);
				if (i == 0||i == 2||i == 4) {
					pWnd->SetWindowPos(NULL, (rc.right - rc.left) / 2-150, (rc.bottom - rc.top) / 2, 20, 35, SWP_NOZORDER | SWP_NOSIZE); 
				}
				else {
					pWnd->SetWindowPos(NULL, (rc.right - rc.left) / 2+50, (rc.bottom - rc.top) / 2, 20, 35, SWP_NOZORDER | SWP_NOSIZE);
				}

			}

		}
		GetClientRect(rc);
	}
}


void CPlaneGameView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 65 || nChar == 97) {
		isA = true;
	}

	if (nChar == 83 || nChar == 115) {
		isS = true;
	}

	if (nChar == 68 || nChar == 100) {
		isD = true;
	}

	if (nChar == 87 || nChar == 119) {
		isW = true;
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}
