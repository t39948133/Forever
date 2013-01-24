// DLGBuff.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "DLGBuff.h"
#include "AttributeSet.h"


// DLGBuff 對話方塊

IMPLEMENT_DYNAMIC(DLGBuff, CDialog)

DLGBuff::DLGBuff(CWnd* pParent /*=NULL*/)
	: CDialog(DLGBuff::IDD, pParent)
{

}

DLGBuff::~DLGBuff()
{
}

void DLGBuff::initDlg()
{
    upDate();
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    pLB->SetCurSel(0);
    CBuffInfo* pInfo = CBuff::getInfo(0);
    replaceSelBuff(pInfo);
}

void DLGBuff::upDate()
{
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    int oriSel = pLB->GetCurSel();
    pLB->ResetContent();

    char buf[256];
    for(int i = 0; CBuff::getInfoCount() > i; i++)
    {
        CBuffInfo* pBuff = CBuff::getInfo(i);
        sprintf_s(buf, sizeof(buf), "[%d] %s", i, pBuff->getName().c_str());
        CString str;
        str = buf;

        pLB->AddString(str);
    }

    pLB->SetCurSel(oriSel);
}

void DLGBuff::replaceSelBuff(CBuffInfo* pInfo)
{
    if(NULL == pInfo)
    {
        return;
    }
    SetDlgItemText(IDC_BuffName, pInfo->getName().c_str());

    SetDlgItemText(IDC_BufficonName, pInfo->getIconName().c_str());

    SetDlgItemInt(IDC_BuffContinued, (int) pInfo->getContinued());

    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_BuffHarmful);
    if(pInfo->isHarmful())
    {
        pCB->SetCurSel(0);
    }
    else
    {
        pCB->SetCurSel(1);
    }

    SetDlgItemText(IDC_BuffDesc, pInfo->getDesc().c_str());

    pCB = (CComboBox*) GetDlgItem(IDC_BuffAttrType);
    AttrType = BASE_ATTR;
    pCB->SetCurSel(AttrType);
    attrShow(pInfo->getAttr());
    //attrShow(pInfo->getPercentAttr());


}

void DLGBuff::attrShow(ComplexAttribute com)
{
    SetDlgItemInt(IDC_BuffAttrHP, com.AdvAttr.iHP);
    SetDlgItemInt(IDC_BuffAttrMP, com.AdvAttr.iMP);
    SetDlgItemInt(IDC_BuffAttrHPMax, com.AdvAttr.iHPMax);
    SetDlgItemInt(IDC_BuffAttrMPMax, com.AdvAttr.iMPMax);
    SetDlgItemInt(IDC_BuffAttrATK, com.AdvAttr.iATK);
    SetDlgItemInt(IDC_BuffAttrDEF, com.AdvAttr.iDEF);
    SetDlgItemInt(IDC_BuffAttrHIT, com.AdvAttr.iHIT);
    SetDlgItemInt(IDC_BuffAttrCRI, com.AdvAttr.iCRI);
    SetDlgItemInt(IDC_BuffAttrSDEF, com.AdvAttr.iSDEF);
    SetDlgItemInt(IDC_BuffAttrFlee, com.AdvAttr.iFlee);
    SetDlgItemInt(IDC_BuffAttrMATK, com.AdvAttr.iMATK);
    SetDlgItemInt(IDC_BuffAttrMDEF, com.AdvAttr.iMDEF);
    SetDlgItemInt(IDC_BuffAttrMHIT, com.AdvAttr.iMHIT);
    SetDlgItemInt(IDC_BuffAttrMCRI, com.AdvAttr.iMCRI);
    SetDlgItemInt(IDC_BuffAttrWDEF, com.AdvAttr.iWDEF);
    SetDlgItemInt(IDC_BuffAttrHPR, com.ObsAttr.iHPR);
    SetDlgItemInt(IDC_BuffAttrMPR, com.ObsAttr.iMPR);
    //---------------------------------------------------
    CString str;
    str.Format("%f", com.AdvAttr.fATKSpeed);
    SetDlgItemText(IDC_BuffAttrATKSpeed, str);
    
    str.Format("%f", com.AdvAttr.fCasting);
    SetDlgItemText(IDC_BuffAttrCasting, str);
    
    str.Format("%f", com.AdvAttr.fMove);
    SetDlgItemText(IDC_BuffAttrMove, str);
}

void DLGBuff::attrShow(FloatPrecentAttribute pre)
{
    SetDlgItemInt(IDC_BuffAttrHP, (int) pre.fHP);
    SetDlgItemInt(IDC_BuffAttrMP, (int) pre.fMP);
    SetDlgItemInt(IDC_BuffAttrHPMax, (int) pre.fHPMax);
    SetDlgItemInt(IDC_BuffAttrMPMax, (int) pre.fMPMax);
    SetDlgItemInt(IDC_BuffAttrATK, (int) pre.fATK);
    SetDlgItemInt(IDC_BuffAttrDEF, (int) pre.fDEF);
    SetDlgItemInt(IDC_BuffAttrHIT, (int) pre.fHIT);
    SetDlgItemInt(IDC_BuffAttrCRI, (int) pre.fCRI);
    SetDlgItemInt(IDC_BuffAttrSDEF, (int) pre.fSDEF);
    SetDlgItemInt(IDC_BuffAttrFlee, (int) pre.fFlee);
    SetDlgItemInt(IDC_BuffAttrMATK, (int) pre.fMATK);
    SetDlgItemInt(IDC_BuffAttrMDEF, (int) pre.fMDEF);
    SetDlgItemInt(IDC_BuffAttrMHIT, (int) pre.fMHIT);
    SetDlgItemInt(IDC_BuffAttrMCRI, (int) pre.fMCRI);
    SetDlgItemInt(IDC_BuffAttrWDEF, (int) pre.fWDEF);
    SetDlgItemInt(IDC_BuffAttrHPR, (int) pre.fHPR);
    SetDlgItemInt(IDC_BuffAttrMPR, (int) pre.fMPR);
    //---------------------------------------------------
    SetDlgItemInt(IDC_BuffAttrATKSpeed, (int) pre.fATKSpeed);
    SetDlgItemInt(IDC_BuffAttrCasting, (int) pre.fCasting);
    SetDlgItemInt(IDC_BuffAttrMove, (int) pre.fMove);
}

void DLGBuff::attrSave(ComplexAttribute& com)
{
    com.AdvAttr.iHP = GetDlgItemInt(IDC_BuffAttrHP);
    com.AdvAttr.iMP = GetDlgItemInt(IDC_BuffAttrMP);
    com.AdvAttr.iHPMax = GetDlgItemInt(IDC_BuffAttrHPMax);
    com.AdvAttr.iMPMax = GetDlgItemInt(IDC_BuffAttrMPMax);
    com.AdvAttr.iATK = GetDlgItemInt(IDC_BuffAttrATK);
    com.AdvAttr.iDEF = GetDlgItemInt(IDC_BuffAttrDEF);
    com.AdvAttr.iHIT = GetDlgItemInt(IDC_BuffAttrHIT);
    com.AdvAttr.iCRI = GetDlgItemInt(IDC_BuffAttrCRI);
    com.AdvAttr.iSDEF = GetDlgItemInt(IDC_BuffAttrSDEF);
    com.AdvAttr.iFlee = GetDlgItemInt(IDC_BuffAttrFlee);
    com.AdvAttr.iMATK = GetDlgItemInt(IDC_BuffAttrMATK);
    com.AdvAttr.iMDEF = GetDlgItemInt(IDC_BuffAttrMDEF);
    com.AdvAttr.iMHIT = GetDlgItemInt(IDC_BuffAttrMHIT);
    com.AdvAttr.iMCRI = GetDlgItemInt(IDC_BuffAttrMCRI);
    com.AdvAttr.iWDEF = GetDlgItemInt(IDC_BuffAttrWDEF);
    com.ObsAttr.iHPR = GetDlgItemInt(IDC_BuffAttrHPR);
    com.ObsAttr.iMPR = GetDlgItemInt(IDC_BuffAttrMPR);
    //------------------------------------------------
    CString str;
    GetDlgItemText(IDC_BuffAttrATKSpeed, str);
    com.AdvAttr.fATKSpeed = (float) atof(str);

    GetDlgItemText(IDC_BuffAttrCasting, str);
    com.AdvAttr.fCasting = (float) atof(str);
    
    GetDlgItemText(IDC_BuffAttrMove, str);
    com.AdvAttr.fMove = (float) atof(str);
}

void DLGBuff::attrSave(FloatPrecentAttribute& pre)
{
    pre.fHP = (float) GetDlgItemInt(IDC_BuffAttrHP);
    pre.fMP = (float) GetDlgItemInt(IDC_BuffAttrMP);
    pre.fHPMax = (float) GetDlgItemInt(IDC_BuffAttrHPMax);
    pre.fMPMax = (float) GetDlgItemInt(IDC_BuffAttrMPMax);
    pre.fATK = (float) GetDlgItemInt(IDC_BuffAttrATK);
    pre.fDEF = (float) GetDlgItemInt(IDC_BuffAttrDEF);
    pre.fHIT = (float) GetDlgItemInt(IDC_BuffAttrHIT);
    pre.fCRI = (float) GetDlgItemInt(IDC_BuffAttrCRI);
    pre.fSDEF = (float) GetDlgItemInt(IDC_BuffAttrSDEF);
    pre.fFlee = (float) GetDlgItemInt(IDC_BuffAttrFlee);
    pre.fMATK = (float) GetDlgItemInt(IDC_BuffAttrMATK);
    pre.fMDEF = (float) GetDlgItemInt(IDC_BuffAttrMDEF);
    pre.fMHIT = (float) GetDlgItemInt(IDC_BuffAttrMHIT);
    pre.fMCRI = (float) GetDlgItemInt(IDC_BuffAttrMCRI);
    pre.fWDEF = (float) GetDlgItemInt(IDC_BuffAttrWDEF);
    pre.fHPR = (float) GetDlgItemInt(IDC_BuffAttrHPR);
    pre.fMPR = (float) GetDlgItemInt(IDC_BuffAttrMPR);
    pre.fATKSpeed = (float) GetDlgItemInt(IDC_BuffAttrATKSpeed);
    pre.fCasting = (float) GetDlgItemInt(IDC_BuffAttrCasting);
    pre.fMove = (float) GetDlgItemInt(IDC_BuffAttrMove);
}

void DLGBuff::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void DLGBuff::OnCancel()
{
}

void DLGBuff::OnOK()
{
}

void DLGBuff::OnClose()
{
}

BEGIN_MESSAGE_MAP(DLGBuff, CDialog)
    ON_LBN_SELCHANGE(IDC_BuffList, &DLGBuff::OnLbnSelchangeBufflist)
    ON_EN_CHANGE(IDC_BuffName, &DLGBuff::OnEnChangeBuffname)
    ON_EN_CHANGE(IDC_BufficonName, &DLGBuff::OnEnChangeBufficonname)
    ON_CBN_SELCHANGE(IDC_BuffHarmful, &DLGBuff::OnCbnSelchangeBuffharmful)
    ON_EN_CHANGE(IDC_BuffContinued, &DLGBuff::OnEnChangeBuffcontinued)
    ON_EN_CHANGE(IDC_BuffDesc, &DLGBuff::OnEnChangeBuffdesc)
    ON_BN_CLICKED(IDC_BuffAttrSave, &DLGBuff::OnBnClickedBuffattrsave)
    ON_CBN_SELCHANGE(IDC_BuffAttrType, &DLGBuff::OnCbnSelchangeBuffattrtype)
    ON_BN_CLICKED(IDC_AddBuff, &DLGBuff::OnBnClickedAddbuff)
    ON_BN_CLICKED(IDC_SaveBuff, &DLGBuff::OnBnClickedSavebuff)
    ON_BN_CLICKED(IDC_LoadBuff, &DLGBuff::OnBnClickedLoadbuff)
END_MESSAGE_MAP()


// DLGBuff 訊息處理常式

void DLGBuff::OnLbnSelchangeBufflist()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);

    replaceSelBuff(pInfo);
}

void DLGBuff::OnEnChangeBuffname()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffName);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_BuffName, str);
    pInfo->m_strName = str;

    upDate();
}

void DLGBuff::OnEnChangeBufficonname()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffName);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_BufficonName, str);
    pInfo->m_iconName = str;
}

void DLGBuff::OnCbnSelchangeBuffharmful()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffName);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_BuffHarmful);
    offset = pCB->GetCurSel();
    if(0 == offset)
    {
        pInfo->m_bHarmful = true;
    }
    else
    {
        pInfo->m_bHarmful = false;
    }
}

void DLGBuff::OnEnChangeBuffcontinued()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    pInfo->m_fContinued =(float) GetDlgItemInt(IDC_BuffContinued);
}

void DLGBuff::OnEnChangeBuffdesc()
{
    // TODO:  如果這是 RICHEDIT 控制項，控制項將不會
    // 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
    // 函式和呼叫 CRichEditCtrl().SetEventMask()
    // 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

    // TODO:  在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    CString str;
    GetDlgItemText(IDC_BuffDesc,str);
    pInfo->m_strDesc = str;
}

void DLGBuff::OnBnClickedBuffattrsave()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    if(BASE_ATTR == AttrType)
    {
        attrSave(pInfo->m_Attr);
    }
    else if(PRECENT_ATTR == AttrType)
    {
        attrSave(pInfo->m_AttrPercent);
    }
}

void DLGBuff::OnCbnSelchangeBuffattrtype()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    int offset = pLB->GetCurSel();
    CBuffInfo* pInfo = CBuff::getInfo(offset);
    if(NULL == pInfo)
    {
        return;
    }
    CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_BuffAttrType);
    offset = pCB->GetCurSel();
    if(AttrType != offset)
    {
        if(BASE_ATTR == offset)
        {
            attrSave(pInfo->m_AttrPercent);
            attrShow(pInfo->getAttr());
        }
        else if(PRECENT_ATTR == offset)
        {
            attrSave(pInfo->m_Attr);
            attrShow(pInfo->getPercentAttr());
        }
    }
    AttrType = offset;
}

void DLGBuff::OnBnClickedAddbuff()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CBuffInfo* pBuff = new CBuffInfo();
    ComplexAttribute com;
    FloatPrecentAttribute pre;

    AttributeClear(com);
    AttributeClear(pre);

    pBuff->initBuffInfo("Buff", "說明", "", com, pre, 60,false);

    CBuff::addInfo(pBuff);
    upDate();
}

void DLGBuff::OnBnClickedSavebuff()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CBuff::write("Buff.la");
}

void DLGBuff::OnBnClickedLoadbuff()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    CBuff::read("Buff.la");
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_BuffList);
    pLB->SetCurSel(0);
    CBuffInfo* pInfo = CBuff::getInfo(0);
    replaceSelBuff(pInfo);
}
