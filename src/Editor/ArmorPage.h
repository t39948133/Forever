#pragma once

#include "CItem.h"
#include "CArmorInfo.h"

// ArmorPage 對話方塊

class ArmorPage : public CDialog
{
	DECLARE_DYNAMIC(ArmorPage)

public:
	ArmorPage(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~ArmorPage();

// 對話方塊資料
	enum { IDD = IDD_ItemTypeArmor };

	void initPage(CArmorInfo* pInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	void AttrTypeShow();
	void setAttrAll(AdvancedAttribute Attr);
	AdvancedAttribute getAttrAll();
	void AttrSave();

	DECLARE_MESSAGE_MAP()

private:
	enum{BASE_ATTR, EXTEND_ATTR};
	int AttrType;
	CArmorInfo* m_pCA;
public:
	afx_msg void OnBnClickedAttrsave();
	afx_msg void OnCbnSelchangeAttrtype();
	afx_msg void OnCbnSelchangeQuality();
	afx_msg void OnCbnSelchangeWear();
	afx_msg void OnEnChangeMeshname();
};
