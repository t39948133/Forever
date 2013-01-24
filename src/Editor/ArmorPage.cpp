// ArmorPage.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "ArmorPage.h"
#include "Common.h"


// ArmorPage 對話方塊

IMPLEMENT_DYNAMIC(ArmorPage, CDialog)

ArmorPage::ArmorPage(CWnd* pParent /*=NULL*/)
	: CDialog(ArmorPage::IDD, pParent)
{

}

ArmorPage::~ArmorPage()
{
}

void ArmorPage::initPage(CArmorInfo* pInfo)
{
	m_pCA = pInfo;
	CComboBox* pTB = (CComboBox*) GetDlgItem (IDC_Quality);	//宣告ComboBox變數
	pTB->SetCurSel(pInfo->getQuality());					//顯示品質

	pTB = (CComboBox*) GetDlgItem (IDC_Wear);				//宣告ComboBox變數
	pTB->SetCurSel(pInfo->getWear());						//顯示穿在哪個部位

	pTB = (CComboBox*) GetDlgItem (IDC_AttrType);			//宣告ComboBox變數
	AttrType = BASE_ATTR;
	pTB->SetCurSel(AttrType);								//預設顯示基本屬性

	SetDlgItemText(IDC_MeshName, pInfo->getMeshName().c_str());

	AttrTypeShow();
}

void ArmorPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void ArmorPage::AttrTypeShow()
{
	if(AttrType == BASE_ATTR)
	{
		AdvancedAttribute Attr = m_pCA->getBaseAttr();

		setAttrAll(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		AdvancedAttribute Attr = m_pCA->getExtendAttr();

		setAttrAll(Attr);
	}
}

void ArmorPage::setAttrAll(AdvancedAttribute Attr)
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

AdvancedAttribute ArmorPage::getAttrAll()
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

void ArmorPage::AttrSave()
{
	AdvancedAttribute Attr = getAttrAll();
	if(AttrType == BASE_ATTR)
	{
		m_pCA->setBaseAttr(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		m_pCA->setExtendAttr(Attr);
	}
}

BEGIN_MESSAGE_MAP(ArmorPage, CDialog)
	ON_BN_CLICKED(IDC_AttrSave, &ArmorPage::OnBnClickedAttrsave)
	ON_CBN_SELCHANGE(IDC_AttrType, &ArmorPage::OnCbnSelchangeAttrtype)
	ON_CBN_SELCHANGE(IDC_Quality, &ArmorPage::OnCbnSelchangeQuality)
	ON_CBN_SELCHANGE(IDC_Wear, &ArmorPage::OnCbnSelchangeWear)
	ON_EN_CHANGE(IDC_MeshName, &ArmorPage::OnEnChangeMeshname)
END_MESSAGE_MAP()


// ArmorPage 訊息處理常式

void ArmorPage::OnBnClickedAttrsave()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AttrSave();
}

void ArmorPage::OnCbnSelchangeAttrtype()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AttrSave();

	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_AttrType);

	AttrType = pTB->GetCurSel();

	AttrTypeShow();
}

void ArmorPage::OnCbnSelchangeQuality()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Quality);

	m_pCA->setQuality((EquipQuality) pTB->GetCurSel());
}

void ArmorPage::OnCbnSelchangeWear()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Wear);

	m_pCA->m_wear = ((ArmorWearType) pTB->GetCurSel());
}

void ArmorPage::OnEnChangeMeshname()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	CString str;
	GetDlgItemText(IDC_MeshName, str);
	m_pCA->setMeshName(str.GetBuffer());
}
