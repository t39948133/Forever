#pragma once

#include "CConsumableInfo.h"

// ConsumablePage 對話方塊

class ConsumablePage : public CDialog
{
	DECLARE_DYNAMIC(ConsumablePage)

public:
	ConsumablePage(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~ConsumablePage();

// 對話方塊資料
	enum { IDD = IDD_ItemTypeConsumable };

	void initPage(CConsumableInfo* pInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

private:
	CConsumableInfo* m_pCC;
public:
	afx_msg void OnEnChangeDesc();
	afx_msg void OnCbnSelchangeEffect();
	afx_msg void OnEnChangeMuch();
};
