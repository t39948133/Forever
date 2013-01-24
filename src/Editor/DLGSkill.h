#pragma once

#include "CSkill.h"
#include "Common.h"

// DLGSkill 對話方塊

class DLGSkill : public CDialog
{
	DECLARE_DYNAMIC(DLGSkill)

public:
	DLGSkill(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~DLGSkill();

// 對話方塊資料
	enum { IDD = IDD_SkillEdit };
    void initDLG();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
    void OnClose () ;
	void OnOK () ;
	void OnCancel () ;

    void upDate();
    void replaceSelSkill(CSkillInfo* pInfo);
    CSkillInfo* getSkillInfo();
    void attrShow(CSkillInfo* pInfo);
    void attrShow(AdvancedAttribute adv);
    void attrShow(FloatPrecentAttribute pre);
    void attrSave(CSkillInfo* pInfo);
    void attrSave(AdvancedAttribute& adv);
    void attrSave(FloatPrecentAttribute& pre);

	DECLARE_MESSAGE_MAP()
private:
    enum{BASE_ATTR, PRECENT_ATTR};
    int AttrType;
public:
    afx_msg void OnLbnSelchangeSkilllist();
    afx_msg void OnCbnSelchangeSkilltype();
    afx_msg void OnEnChangeSkilllevel();
    afx_msg void OnEnChangeSkilliconname();
    afx_msg void OnEnChangeSkillname();
    afx_msg void OnEnChangeSkilldesc();
    afx_msg void OnEnChangeSkillactionid();
    afx_msg void OnEnChangeSkillcasttime();
    afx_msg void OnEnChangeSkillcooldown();
    afx_msg void OnEnChangeSkillcastrange();
    afx_msg void OnCbnSelchangeSkilltargettype();
    afx_msg void OnLbnSelchangeSkillbuff();
    afx_msg void OnLbnSelchangeSkilltriggermotion();
    afx_msg void OnLbnSelchangeSkillmotioneffects();
    afx_msg void OnCbnSelchangeSkillattrtype();
    afx_msg void OnBnClickedSkillattrsave();
    afx_msg void OnBnClickedSkillnew();
    afx_msg void OnBnClickedSkillsave();
    afx_msg void OnBnClickedSkillload();
    afx_msg void OnEnChangeSkillcastmp();
};
