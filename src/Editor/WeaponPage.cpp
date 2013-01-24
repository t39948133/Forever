// WeaponPage.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "WeaponPage.h"
#include "Common.h"


// WeaponPage 對話方塊

IMPLEMENT_DYNAMIC(WeaponPage, CDialog)

WeaponPage::WeaponPage(CWnd* pParent /*=NULL*/)
	: CDialog(WeaponPage::IDD, pParent)
{

}

WeaponPage::~WeaponPage()
{
}

void WeaponPage::initPage(CWeaponInfo* pInfo)
{
	m_pCW = pInfo;
	CComboBox* pTB = (CComboBox*) GetDlgItem (IDC_Quality);	//宣告ComboBox變數
	pTB->SetCurSel(pInfo->getQuality());					//顯示品質

	pTB = (CComboBox*) GetDlgItem (IDC_Wield);				//宣告ComboBox變數
	pTB->SetCurSel(pInfo->getWield());						//顯示哪手裝備

	pTB = (CComboBox*) GetDlgItem (IDC_AttrType);			//宣告ComboBox變數
	AttrType = BASE_ATTR;
	pTB->SetCurSel(AttrType);								//預設顯示基本屬性

	SetDlgItemText(IDC_MeshName, pInfo->getMeshName().c_str());

	AttrTypeShow();
}

void WeaponPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void WeaponPage::AttrTypeShow()
{
	if(AttrType == BASE_ATTR)
	{
		AdvancedAttribute Attr = m_pCW->getBaseAttr();

		setAttrAll(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		AdvancedAttribute Attr = m_pCW->getExtendAttr();

		setAttrAll(Attr);
	}
}

void WeaponPage::setAttrAll(AdvancedAttribute Attr)
{
		SetDlgItemInt(IDC_AttrHP, Attr.iHP);

		SetDlgItemInt(IDC_AttrMP, Attr.iMP);

		SetDlgItemInt(IDC_AttrHPMax, Attr.iHPMax);

		SetDlgItemInt(IDC_AttrMPMax, Attr.iMPMax);

		SetDlgItemInt(IDC_AttrATK, Attr.iATK);

		SetDlgItemInt(IDC_AttrDEF, Attr.iDEF);

		SetDlgItemInt(IDC_AttrHIT, Attr.iHIT);

		SetDlgItemInt(IDC_AttrCRI, Attr.iCRI);

		SetDlgItemInt(IDC_AttrMATK, Attr.iMATK);

		SetDlgItemInt(IDC_AttrMDEF, Attr.iMDEF);

		SetDlgItemInt(IDC_AttrMHIT, Attr.iMHIT);

		SetDlgItemInt(IDC_AttrMCRI, Attr.iMCRI);

		SetDlgItemInt(IDC_AttrSDEF, Attr.iSDEF);

		SetDlgItemInt(IDC_AttrWDEF, Attr.iWDEF);

		SetDlgItemInt(IDC_AttrFlee, Attr.iFlee);
//--------------------------------------------------------
		CString str;
		str.Format("%f", Attr.fMove);
		SetDlgItemText(IDC_AttrMove, str);

		str.Format("%f", Attr.fATKSpeed);
		SetDlgItemText(IDC_AttrATKSpeed, str);

		str.Format("%f", Attr.fCasting);
		SetDlgItemText(IDC_AttrCasting, str);

}

AdvancedAttribute WeaponPage::getAttrAll()
{
	AdvancedAttribute Attr;

	Attr.iHP = GetDlgItemInt(IDC_AttrHP);

	Attr.iMP = GetDlgItemInt(IDC_AttrMP);
	
	Attr.iHPMax = GetDlgItemInt(IDC_AttrHPMax);
	
	Attr.iMPMax = GetDlgItemInt(IDC_AttrMPMax);
	
	Attr.iATK = GetDlgItemInt(IDC_AttrATK);
	
	Attr.iDEF = GetDlgItemInt(IDC_AttrDEF);
	
	Attr.iHIT = GetDlgItemInt(IDC_AttrHIT);
	
	Attr.iCRI = GetDlgItemInt(IDC_AttrCRI);
	
	Attr.iMATK = GetDlgItemInt(IDC_AttrMATK);
	
	Attr.iMDEF = GetDlgItemInt(IDC_AttrMDEF);
	
	Attr.iMHIT = GetDlgItemInt(IDC_AttrMHIT);
	
	Attr.iMCRI = GetDlgItemInt(IDC_AttrMCRI);
	
	Attr.iSDEF = GetDlgItemInt(IDC_AttrSDEF);
	
	Attr.iWDEF = GetDlgItemInt(IDC_AttrWDEF);
	
	Attr.iFlee = GetDlgItemInt(IDC_AttrFlee);
//---------------------------------------------------
	CString str;
	
	GetDlgItemText(IDC_AttrMove, str);
	Attr.fMove = (float) atof(str);
	
	GetDlgItemText(IDC_AttrATKSpeed, str);
	Attr.fATKSpeed = (float) atof(str);

	GetDlgItemText(IDC_AttrCasting, str);
	Attr.fCasting = (float) atof(str);
	return Attr;
}

void WeaponPage::AttrSave()
{
	AdvancedAttribute Attr = getAttrAll();
	if(AttrType == BASE_ATTR)
	{
		m_pCW->setBaseAttr(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		m_pCW->setExtendAttr(Attr);
	}
}

BEGIN_MESSAGE_MAP(WeaponPage, CDialog)
	ON_BN_CLICKED(IDC_AttrSave, &WeaponPage::OnBnClickedAttrsave)
	ON_CBN_SELCHANGE(IDC_AttrType, &WeaponPage::OnCbnSelchangeAttrtype)
	ON_CBN_SELCHANGE(IDC_Quality, &WeaponPage::OnCbnSelchangeQuality)
	ON_CBN_SELCHANGE(IDC_Wield, &WeaponPage::OnCbnSelchangeWield)
	ON_EN_CHANGE(IDC_MeshName, &WeaponPage::OnEnChangeMeshname)
END_MESSAGE_MAP()


// WeaponPage 訊息處理常式


void WeaponPage::OnBnClickedAttrsave()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AttrSave();
}

void WeaponPage::OnCbnSelchangeAttrtype()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AttrSave();
		
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_AttrType);

	AttrType = pTB->GetCurSel();

	AttrTypeShow();
}

void WeaponPage::OnCbnSelchangeQuality()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Quality);

	m_pCW->setQuality((EquipQuality) pTB->GetCurSel());
}

void WeaponPage::OnCbnSelchangeWield()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Wield);

	m_pCW->m_wield = ((WeaponWieldType) pTB->GetCurSel());
}

void WeaponPage::OnEnChangeMeshname()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	CString str;
	GetDlgItemText(IDC_MeshName, str);
	m_pCW->setMeshName(str.GetBuffer());
}
