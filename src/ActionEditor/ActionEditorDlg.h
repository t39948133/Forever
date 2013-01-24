// ActionEditorDlg.h : 標頭檔
//

#pragma once
#include "CActionSystem.h"

// CActionEditorDlg 對話方塊
class CActionEditorDlg : public CDialog
{
// 建構
public:
	CActionEditorDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_ACTIONEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援

private:
   void updateActionList();
   void clearActionData();
   void updateEventList();
   void clearEventData();

   CActionSystem *m_pActionSystem;
   int m_iActionListIdx;
   int m_iEventListIdx;

// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedNewaction();
   afx_msg void OnLbnSelchangeActionlist();
   afx_msg void OnBnClickedCancelselactionlist();
   afx_msg void OnBnClickedDelaction();
   afx_msg void OnBnClickedNewevent();
   afx_msg void OnLbnSelchangeEventlist();
   afx_msg void OnBnClickedCancelseleventlist();
   afx_msg void OnBnClickedDelevent();
   afx_msg void OnBnClickedSave();
   afx_msg void OnBnClickedLoad();
};
