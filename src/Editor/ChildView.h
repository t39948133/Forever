// ChildView.h : CChildView 類別的介面
//


#pragma once

#include "DLGItem.h"
#include "DLGBuff.h"
#include "DLGSkill.h"

#include "Common.h"
#include "CItem.h"
#include "CBuff.h"
#include "CSkill.h"
#include "CGameClient.h"

// CChildView 視窗

class CChildView : public CWnd
{
// 建構
public:
	CChildView();

// 屬性
public:
	DLGItem dlgItem ;
    DLGBuff dlgBuff ;
    DLGSkill dlgSkill;

private:
    CGameClient *m_pGameClient;
    HDC          m_memDC;
    HBITMAP      m_hBMP;

// 作業
public:

// 覆寫
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 程式碼實作
public:
	virtual ~CChildView();

	// 產生的訊息對應函式
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct ) ;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
//	afx_msg void OnKeyDown (UINT, UINT, UINT) ;

	DECLARE_MESSAGE_MAP()
};

