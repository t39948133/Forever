#pragma once

#include "CItem.h"
#include "CWeaponInfo.h"

// WeaponPage 對話方塊

class WeaponPage : public CDialog
{
	DECLARE_DYNAMIC(WeaponPage)

public:
	WeaponPage(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~WeaponPage();

// 對話方塊資料
	enum { IDD = IDD_ItemTypeWeapon };

	void initPage(CWeaponInfo* pInfo);

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
	CWeaponInfo* m_pCW;
public:
	afx_msg void OnBnClickedAttrsave();
	afx_msg void OnCbnSelchangeAttrtype();
	afx_msg void OnCbnSelchangeQuality();
	afx_msg void OnCbnSelchangeWield();
	afx_msg void OnEnChangeMeshname();
};
