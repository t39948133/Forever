// DLGSkill.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "DLGSkill.h"

#include "AttributeSet.h"
#include "CBuff.h"


// DLGSkill 對話方塊

IMPLEMENT_DYNAMIC(DLGSkill, CDialog)

DLGSkill::DLGSkill(CWnd* pParent /*=NULL*/)
	: CDialog(DLGSkill::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

DLGSkill::~DLGSkill()
{
}

void DLGSkill::initDLG()
{
    upDate();
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillList);
    pLB->SetCurSel(0);
    AttrType = BASE_ATTR;
    CSkillInfo* pInfo = CSkill::getInfo(pLB->GetCurSel());
    replaceSelSkill(pInfo);
}

void DLGSkill::OnCancel()
{
}

void DLGSkill::OnClose()
{
}

void DLGSkill::OnOK()
{
}

void DLGSkill::upDate()
{
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillList);
    int oriSel = pLB->GetCurSel();
    pLB->ResetContent();

    char buf[256];
    for(int i = 0; CSkill::getInfoCount() > i; i++)
    {
        CSkillInfo* pInfo = CSkill::getInfo(i);
        sprintf_s(buf, sizeof(buf), "[%d] %s", i, pInfo->getName().c_str());
        CString str;
        str = buf;
        pLB->AddString(str);
    }

    pLB->SetCurSel(oriSel);
}

void DLGSkill::replaceSelSkill(CSkillInfo* pInfo)
{
    if(NULL == pInfo)
    {
        return;
    }
    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_SkillType);
    pCB->SetCurSel(pInfo->getType());

    SetDlgItemInt(IDC_SkillLevel, pInfo->getLevel());

    SetDlgItemText(IDC_SkilliconName, pInfo->geticonName().c_str());

    SetDlgItemText(IDC_SkillName, pInfo->getName().c_str());

    SetDlgItemText(IDC_SkillDesc, pInfo->getDesc().c_str());

    SetDlgItemInt(IDC_SkillActionID, pInfo->getActionID());

    SetDlgItemInt(IDC_SkillCastMP, pInfo->getCastMP());

    CString str;
    str.Format("%f", pInfo->getCastTime());
    SetDlgItemText(IDC_SkillCastTime, str);

    str.Format("%f", pInfo->getCoolDown());
    SetDlgItemText(IDC_SkillCoolDown, str);

    str.Format("%f", pInfo->getCastRange());
    SetDlgItemText(IDC_SkillCastRange, str);

    CButton* pB = (CButton*) GetDlgItem(IDC_SkillWeapon);
    pB->SetCheck(pInfo->isRequireWeapon());

    pB = (CButton*) GetDlgItem(IDC_SkillShield);
    pB->SetCheck(pInfo->isRequireShield());

    pCB = (CComboBox*) GetDlgItem(IDC_SkillTargetType);
    pCB->SetCurSel(pInfo->getTarget());

    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillBuff);
    char buf[256];
    pLB->ResetContent();
    for(int i = 0; CBuff::getInfoCount() > i; i++)
    {
        CBuffInfo* pBuffInfo = CBuff::getInfo(i);
        sprintf_s(buf, sizeof(buf), "[%d] %s", i, 
            pBuffInfo->getName().c_str());
        str = buf;
        pLB->AddString(str);
    }
    str = "沒有";
    pLB->AddString(str);
    /*
    動作*/
    pLB = (CListBox*) GetDlgItem(IDC_SkillMotionEffects);
    pLB->ResetContent();
    str = "沒有";
    pLB->AddString(str);
    pLB = (CListBox*) GetDlgItem(IDC_SkillTriggerMotion);
    pLB->ResetContent();
    str = "沒有";
    pLB->AddString(str);
  //  */
    pCB = (CComboBox*) GetDlgItem(IDC_SkillAttrType);
    pCB->SetCurSel(AttrType);
    attrShow(pInfo);

}

CSkillInfo* DLGSkill::getSkillInfo()
{
     CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillList);
    int oriSel = pLB->GetCurSel();
    return CSkill::getInfo(oriSel);
}
    
void DLGSkill::attrShow(CSkillInfo* pInfo)
{
    if(BASE_ATTR == AttrType)
    {
        attrShow(pInfo->getEffectAttr());
    }
    else
    {
        attrShow(pInfo->getEffectAttrPercent());
    }
}

void DLGSkill::attrShow(AdvancedAttribute adv)
{
    SetDlgItemInt(IDC_SkillAttrHP, adv.iHP);
    SetDlgItemInt(IDC_SkillAttrMP, adv.iMP);
    SetDlgItemInt(IDC_SkillAttrHPMax, adv.iHPMax);
    SetDlgItemInt(IDC_SkillAttrMPMax, adv.iMPMax);
    SetDlgItemInt(IDC_SkillAttrATK, adv.iATK);
    SetDlgItemInt(IDC_SkillAttrDEF, adv.iDEF);
    SetDlgItemInt(IDC_SkillAttrHIT, adv.iHIT);
    SetDlgItemInt(IDC_SkillAttrCRI, adv.iCRI);
    SetDlgItemInt(IDC_SkillAttrSDEF, adv.iSDEF);
    SetDlgItemInt(IDC_SkillAttrFlee, adv.iFlee);
    SetDlgItemInt(IDC_SkillAttrMATK, adv.iMATK);
    SetDlgItemInt(IDC_SkillAttrMDEF, adv.iMDEF);
    SetDlgItemInt(IDC_SkillAttrMHIT, adv.iMHIT);
    SetDlgItemInt(IDC_SkillAttrMCRI, adv.iMCRI);
    SetDlgItemInt(IDC_SkillAttrWDEF, adv.iWDEF);
    //---------------------------------------------------
    CString str;
    str.Format("%f", adv.fATKSpeed);
    SetDlgItemText(IDC_SkillAttrATKSpeed, str);
    
    str.Format("%f", adv.fCasting);
    SetDlgItemText(IDC_SkillAttrCasting, str);
    
    str.Format("%f", adv.fMove);
    SetDlgItemText(IDC_SkillAttrMove, str);
}

void DLGSkill::attrShow(FloatPrecentAttribute pre)
{
    SetDlgItemInt(IDC_SkillAttrHP, (int) pre.fHP);
    SetDlgItemInt(IDC_SkillAttrMP, (int) pre.fMP);
    SetDlgItemInt(IDC_SkillAttrHPMax, (int) pre.fHPMax);
    SetDlgItemInt(IDC_SkillAttrMPMax, (int) pre.fMPMax);
    SetDlgItemInt(IDC_SkillAttrATK, (int) pre.fATK);
    SetDlgItemInt(IDC_SkillAttrDEF, (int) pre.fDEF);
    SetDlgItemInt(IDC_SkillAttrHIT, (int) pre.fHIT);
    SetDlgItemInt(IDC_SkillAttrCRI, (int) pre.fCRI);
    SetDlgItemInt(IDC_SkillAttrSDEF, (int) pre.fSDEF);
    SetDlgItemInt(IDC_SkillAttrFlee, (int) pre.fFlee);
    SetDlgItemInt(IDC_SkillAttrMATK, (int) pre.fMATK);
    SetDlgItemInt(IDC_SkillAttrMDEF, (int) pre.fMDEF);
    SetDlgItemInt(IDC_SkillAttrMHIT, (int) pre.fMHIT);
    SetDlgItemInt(IDC_SkillAttrMCRI, (int) pre.fMCRI);
    SetDlgItemInt(IDC_SkillAttrWDEF, (int) pre.fWDEF);
    //---------------------------------------------------
    SetDlgItemInt(IDC_SkillAttrATKSpeed, (int) pre.fATKSpeed);
    SetDlgItemInt(IDC_SkillAttrCasting, (int) pre.fCasting);
    SetDlgItemInt(IDC_SkillAttrMove, (int) pre.fMove);
}

void DLGSkill::attrSave(CSkillInfo* pInfo)
{
    if(BASE_ATTR == AttrType)
    {
        attrSave(pInfo->m_effectAttr);
    }
    else if(PRECENT_ATTR == AttrType)
    {
        attrSave(pInfo->m_effectAttrPercent);
    }
}
    
void DLGSkill::attrSave(AdvancedAttribute& adv)
{
    adv.iHP = GetDlgItemInt(IDC_SkillAttrHP);
    adv.iMP = GetDlgItemInt(IDC_SkillAttrMP);
    adv.iHPMax = GetDlgItemInt(IDC_SkillAttrHPMax);
    adv.iMPMax = GetDlgItemInt(IDC_SkillAttrMPMax);
    adv.iATK = GetDlgItemInt(IDC_SkillAttrATK);
    adv.iDEF = GetDlgItemInt(IDC_SkillAttrDEF);
    adv.iHIT = GetDlgItemInt(IDC_SkillAttrHIT);
    adv.iCRI = GetDlgItemInt(IDC_SkillAttrCRI);
    adv.iSDEF = GetDlgItemInt(IDC_SkillAttrSDEF);
    adv.iFlee = GetDlgItemInt(IDC_SkillAttrFlee);
    adv.iMATK = GetDlgItemInt(IDC_SkillAttrMATK);
    adv.iMDEF = GetDlgItemInt(IDC_SkillAttrMDEF);
    adv.iMHIT = GetDlgItemInt(IDC_SkillAttrMHIT);
    adv.iMCRI = GetDlgItemInt(IDC_SkillAttrMCRI);
    adv.iWDEF = GetDlgItemInt(IDC_SkillAttrWDEF);    
    //------------------------------------------------
    CString str;
    GetDlgItemText(IDC_SkillAttrATKSpeed, str);
    adv.fATKSpeed = (float) atof(str);

    GetDlgItemText(IDC_SkillAttrCasting, str);
    adv.fCasting = (float) atof(str);
    
    GetDlgItemText(IDC_SkillAttrMove, str);
    adv.fMove = (float) atof(str);
}

void DLGSkill::attrSave(FloatPrecentAttribute& pre)
{
    pre.fHP = (float) GetDlgItemInt(IDC_SkillAttrHP);
    pre.fMP = (float) GetDlgItemInt(IDC_SkillAttrMP);
    pre.fHPMax = (float) GetDlgItemInt(IDC_SkillAttrHPMax);
    pre.fMPMax = (float) GetDlgItemInt(IDC_SkillAttrMPMax);
    pre.fATK = (float) GetDlgItemInt(IDC_SkillAttrATK);
    pre.fDEF = (float) GetDlgItemInt(IDC_SkillAttrDEF);
    pre.fHIT = (float) GetDlgItemInt(IDC_SkillAttrHIT);
    pre.fCRI = (float) GetDlgItemInt(IDC_SkillAttrCRI);
    pre.fSDEF = (float) GetDlgItemInt(IDC_SkillAttrSDEF);
    pre.fFlee = (float) GetDlgItemInt(IDC_SkillAttrFlee);
    pre.fMATK = (float) GetDlgItemInt(IDC_SkillAttrMATK);
    pre.fMDEF = (float) GetDlgItemInt(IDC_SkillAttrMDEF);
    pre.fMHIT = (float) GetDlgItemInt(IDC_SkillAttrMHIT);
    pre.fMCRI = (float) GetDlgItemInt(IDC_SkillAttrMCRI);
    pre.fWDEF = (float) GetDlgItemInt(IDC_SkillAttrWDEF);
    pre.fATKSpeed = (float) GetDlgItemInt(IDC_SkillAttrATKSpeed);
    pre.fCasting = (float) GetDlgItemInt(IDC_SkillAttrCasting);
    pre.fMove = (float) GetDlgItemInt(IDC_SkillAttrMove);
}

void DLGSkill::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DLGSkill, CDialog)
    ON_LBN_SELCHANGE(IDC_SkillList, &DLGSkill::OnLbnSelchangeSkilllist)
    ON_CBN_SELCHANGE(IDC_SkillType, &DLGSkill::OnCbnSelchangeSkilltype)
    ON_EN_CHANGE(IDC_SkillLevel, &DLGSkill::OnEnChangeSkilllevel)
    ON_EN_CHANGE(IDC_SkilliconName, &DLGSkill::OnEnChangeSkilliconname)
    ON_EN_CHANGE(IDC_SkillName, &DLGSkill::OnEnChangeSkillname)
    ON_EN_CHANGE(IDC_SkillDesc, &DLGSkill::OnEnChangeSkilldesc)
    ON_EN_CHANGE(IDC_SkillActionID, &DLGSkill::OnEnChangeSkillactionid)
    ON_EN_CHANGE(IDC_SkillCastTime, &DLGSkill::OnEnChangeSkillcasttime)
    ON_EN_CHANGE(IDC_SkillCoolDown, &DLGSkill::OnEnChangeSkillcooldown)
    ON_EN_CHANGE(IDC_SkillCastRange, &DLGSkill::OnEnChangeSkillcastrange)
    ON_CBN_SELCHANGE(IDC_SkillTargetType, &DLGSkill::OnCbnSelchangeSkilltargettype)
    ON_LBN_SELCHANGE(IDC_SkillBuff, &DLGSkill::OnLbnSelchangeSkillbuff)
    ON_LBN_SELCHANGE(IDC_SkillTriggerMotion, &DLGSkill::OnLbnSelchangeSkilltriggermotion)
    ON_LBN_SELCHANGE(IDC_SkillMotionEffects, &DLGSkill::OnLbnSelchangeSkillmotioneffects)
    ON_CBN_SELCHANGE(IDC_SkillAttrType, &DLGSkill::OnCbnSelchangeSkillattrtype)
    ON_BN_CLICKED(IDC_SkillAttrSave, &DLGSkill::OnBnClickedSkillattrsave)
    ON_BN_CLICKED(IDC_SkillNew, &DLGSkill::OnBnClickedSkillnew)
    ON_BN_CLICKED(IDC_SkillSave, &DLGSkill::OnBnClickedSkillsave)
    ON_BN_CLICKED(IDC_SkillLoad, &DLGSkill::OnBnClickedSkillload)
    ON_EN_CHANGE(IDC_SkillCastMP, &DLGSkill::OnEnChangeSkillcastmp)
    ON_BN_CLICKED(IDC_SkillDel, &DLGSkill::OnBnClickedSkilldel)
    ON_BN_CLICKED(IDC_SkillWeapon, &DLGSkill::OnBnClickedSkillweapon)
    ON_BN_CLICKED(IDC_SkillShield, &DLGSkill::OnBnClickedSkillshield)
END_MESSAGE_MAP()


// DLGSkill 訊息處理常式

void DLGSkill::OnLbnSelchangeSkilllist()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    replaceSelSkill(pInfo);
}

void DLGSkill::OnCbnSelchangeSkilltype()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_SkillType);
    pInfo->m_type = (tagSKILL_TYPE) pCB->GetCurSel();
}

void DLGSkill::OnEnChangeSkilllevel()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    pInfo->m_iLevel = GetDlgItemInt(IDC_SkillLevel);
}

void DLGSkill::OnEnChangeSkilliconname()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_SkilliconName, str);
    pInfo->m_iconName = str;
}
void DLGSkill::OnEnChangeSkillname()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_SkillName, str);
    pInfo->m_strName = str;
    upDate();
}

void DLGSkill::OnEnChangeSkilldesc()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_SkillDesc, str);
    pInfo->m_strDesc = str;
}

void DLGSkill::OnEnChangeSkillactionid()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    pInfo->m_iActionID = GetDlgItemInt(IDC_SkillActionID);
}

void DLGSkill::OnEnChangeSkillcasttime()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_SkillCastTime, str);
    pInfo->m_fCastTime = (float) atof(str);
}

void DLGSkill::OnEnChangeSkillcooldown()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_SkillCoolDown, str);
    pInfo->m_fCoolDown = (float) atof(str);
}

void DLGSkill::OnEnChangeSkillcastrange()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_SkillCastRange, str);
    pInfo->m_fCastRange = (float) atof(str);
}

void DLGSkill::OnCbnSelchangeSkilltargettype()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_SkillTargetType);
    pInfo->m_target = (AttackTarget) pCB->GetCurSel();
}

void DLGSkill::OnLbnSelchangeSkillbuff()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillBuff);
    int oriSel = pLB->GetCurSel();
    if(CBuff::getInfoCount() == oriSel)
    {
        pInfo->m_iBuffID = -1;
    }
    else
    {
        pInfo->m_iBuffID = oriSel;
    }
}

void DLGSkill::OnLbnSelchangeSkilltriggermotion()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillTriggerMotion);
    int oriSel = pLB->GetCurSel();
}

void DLGSkill::OnLbnSelchangeSkillmotioneffects()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillMotionEffects);
    int oriSel = pLB->GetCurSel();
}

void DLGSkill::OnCbnSelchangeSkillattrtype()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_SkillAttrType);
    if(pCB->GetCurSel() != AttrType)
    {
        attrSave(pInfo);
        AttrType = pCB->GetCurSel();
        attrShow(pInfo);
    }
}

void DLGSkill::OnBnClickedSkillattrsave()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    if(NULL == pInfo)
    {
        return;
    }
    attrSave(pInfo);
}

void DLGSkill::OnBnClickedSkillnew()
{
    // TODO: 在此加入控制項告知處理常式程式碼    
    CSkillInfo* pInfo = new CSkillInfo();
    AdvancedAttribute adv;
    FloatPrecentAttribute per;
    AttributeClear(adv);
    AttributeClear(per);
    adv.fATKSpeed = 0.0f;
    adv.fCasting = 0.0f;
    adv.fMove = 0.0f;
    pInfo->initSkillInfo(TYPE_ACTIVE, 1, "", "新技能", "說明", -1, 0, 0.0f, 0.0f, 0.0f,
        ENEMY, adv, per, -1, -1, -1, false, false);
    CSkill::addInfo(pInfo);
    upDate();
}

void DLGSkill::OnBnClickedSkillsave()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkill::write("Skill.fla");
}

void DLGSkill::OnBnClickedSkillload()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CSkill::read("Skill.fla");
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillList);
    pLB->SetCurSel(0);
    CSkillInfo* pInfo = CSkill::getInfo(pLB->GetCurSel());
    replaceSelSkill(pInfo);
}

void DLGSkill::OnEnChangeSkillcastmp()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CSkillInfo* pInfo = getSkillInfo();
    pInfo->m_iCastMP = GetDlgItemInt(IDC_SkillCastMP);
}

void DLGSkill::OnBnClickedSkilldel()
{
   CListBox* pLB = (CListBox*) GetDlgItem(IDC_SkillList);
   if(pLB->GetCurSel() > -1) {
      CSkill::delInfo(pLB->GetCurSel());
      upDate();
   }
}

void DLGSkill::OnBnClickedSkillweapon()
{
	// TODO: 在此加入控制項告知處理常式程式碼
   CSkillInfo *pInfo = getSkillInfo();
   if(pInfo == NULL)
      return;

   CButton* pB = (CButton*) GetDlgItem(IDC_SkillWeapon);
   if(pB->GetCheck() == 1)
      pInfo->m_bRequireWeapon = true;
   else
      pInfo->m_bRequireWeapon = false;
}

void DLGSkill::OnBnClickedSkillshield()
{
	// TODO: 在此加入控制項告知處理常式程式碼
   CSkillInfo *pInfo = getSkillInfo();
   if(pInfo == NULL)
      return;

   CButton* pB = (CButton*) GetDlgItem(IDC_SkillShield);
   if(pB->GetCheck() == 1)
      pInfo->m_bRequireShield = true;
   else
      pInfo->m_bRequireShield = false;
}
