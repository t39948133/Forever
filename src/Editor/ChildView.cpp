// ChildView.cpp : CChildView 類別的實作
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
    m_pGameClient = NULL;
}

CChildView::~CChildView()
{
   ::DeleteObject(m_hBMP);
   ::ReleaseDC(NULL, m_memDC);

   if(m_pGameClient != NULL) {
       delete m_pGameClient;
       m_pGameClient = NULL;
   }
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_CREATE ()
	ON_WM_TIMER ()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 訊息處理常式

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct )
{
	int r = CWnd::OnCreate (lpCreateStruct) ;

    m_pGameClient = new CGameClient();
    m_pGameClient->init();

    // 建立背景繪圖區(為了避免畫面閃爍)
    HDC screenDC = ::GetDC(NULL);
    m_memDC = ::CreateCompatibleDC(screenDC);
    m_hBMP = ::CreateBitmap(900, 900, 1, 32, NULL);
    ::SelectObject(m_memDC, m_hBMP);
    ::ReleaseDC(NULL, screenDC);

	SetTimer (100, 1000/30, NULL) ;

	dlgItem.Create(IDD_ItemEdit, this);
	dlgItem.ShowWindow (SW_SHOW);
	dlgItem.initDlg();

    dlgBuff.Create(IDD_BuffEdit, this);
    dlgBuff.ShowWindow(SW_SHOW);
    dlgBuff.initDlg();

    dlgSkill.Create(IDD_SkillEdit, this);
    dlgSkill.ShowWindow(SW_SHOW);
    dlgSkill.initDLG();

	return r ;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    m_pGameClient->work(m_hWnd);

	Invalidate (true) ;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 繪製的裝置內容
	
	// TODO: 在此加入您的訊息處理常式程式碼
	
	// 不要呼叫描繪訊息的 CWnd::OnPaint()

	HDC hdc = dc;
    m_pGameClient->draw(m_memDC);
    ::BitBlt(hdc, 0, 0, 900, 900, m_memDC, 0, 0, SRCCOPY);
}

