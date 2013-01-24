// onsumablePage.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "ConsumablePage.h"


// ConsumablePage 對話方塊

IMPLEMENT_DYNAMIC(ConsumablePage, CDialog)

ConsumablePage::ConsumablePage(CWnd* pParent /*=NULL*/)
	: CDialog(ConsumablePage::IDD, pParent)
{

}

ConsumablePage::~ConsumablePage()
{
}

void ConsumablePage::initPage(CConsumableInfo* pInfo)
{
	m_pCC = pInfo;
	SetDlgItemText(IDC_Desc, m_pCC->getDesc().c_str());

	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Effect);
	pTB->SetCurSel(m_pCC->getEffect());

	SetDlgItemInt(IDC_Much, m_pCC->getMuch());
}

void ConsumablePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConsumablePage, CDialog)
	ON_EN_CHANGE(IDC_Desc, &ConsumablePage::OnEnChangeDesc)
	ON_CBN_SELCHANGE(IDC_Effect, &ConsumablePage::OnCbnSelchangeEffect)
	ON_EN_CHANGE(IDC_Much, &ConsumablePage::OnEnChangeMuch)
END_MESSAGE_MAP()


// ConsumablePage 訊息處理常式

void ConsumablePage::OnEnChangeDesc()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CString str;
	GetDlgItemText(IDC_Desc, str);
	m_pCC->m_strDesc = ((LPCTSTR) str);
}

void ConsumablePage::OnCbnSelchangeEffect()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Effect);
	m_pCC->m_effect = ((EdibleEffectType) pTB->GetCurSel());
}

void ConsumablePage::OnEnChangeMuch()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	m_pCC->m_iMuch = GetDlgItemInt(IDC_Much);
}
