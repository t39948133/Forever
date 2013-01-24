#pragma once

#include "WeaponPage.h"
#include "ArmorPage.h"
#include "ConsumablePage.h"

#include "CItem.h"
// DLGItem 對話方塊

class DLGItem : public CDialog
{
	DECLARE_DYNAMIC(DLGItem)

public:
	DLGItem(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~DLGItem();

// 對話方塊資料
	enum { IDD = IDD_ItemEdit };

	void initDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	void OnClose () ;
	void OnOK () ;
	void OnCancel () ;
	void upDate();
	void createPage();
	void replaceSelItem(CItemInfo* pInfo);
	void pageShow(CItemInfo* pInfo);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeItemlist();
	afx_msg void OnEnChangeItemname();
	afx_msg void OnCbnSelchangeItemtype();
	afx_msg void OnBnClickedItemsoulbind();
	afx_msg void OnEnChangeItemlevel();
	afx_msg void OnEnChangeItemstacklimit();
	afx_msg void OnEnChangeItemsellprice();
	afx_msg void OnEnChangeItembuyprice();
private:
	CTabCtrl m_tab;
	enum {WAEPON = 0, ARMOR, CONSUMABLE, TOTLO};
	int m_CurSelTab;
	WeaponPage m_page1;
	ArmorPage m_page2;
	ConsumablePage m_page3;
	CDialog* pDialog[TOTLO];

public:
	afx_msg void OnBnClickedSavelist();
	afx_msg void OnBnClickedLoadlist();
	afx_msg void OnBnClickedAdditem();
	afx_msg void OnEnChangeiconname();
};
