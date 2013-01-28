// ..\..\src\Editor\DLGItem.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "DLGItem.h"

#include "CItemInfoLoader.h"
#include "AttributeSet.h"


// DLGItem 對話方塊

IMPLEMENT_DYNAMIC(DLGItem, CDialog)

DLGItem::DLGItem(CWnd* pParent /*=NULL*/)
	: CDialog(DLGItem::IDD, pParent)
{

}

DLGItem::~DLGItem()
{
}

void DLGItem::initDlg()
{
	createPage () ;
	upDate();

	CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList);
	pLB->SetCurSel(0);
	CItemInfo* pInfo = CItem::getInfo(0);
	CComboBox* pTB = (CComboBox*)GetDlgItem (IDC_addClass);
	pTB->SetCurSel(0);
	replaceSelItem(pInfo);
	
}

void DLGItem::upDate()
{
	char buf[256] ;

	CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList) ;
	int oriSel = pLB->GetCurSel () ;
	pLB->ResetContent () ;
	for (int i = 0; i< CItem::getInfoCount (); i++)
	{
		CItemInfo* pInfo = CItem::getInfo (i) ;

		CString str ;
		sprintf_s (buf, sizeof(buf), "[%d] %s", i, (const char*)pInfo->getName().c_str()) ;
		str = buf ;

		pLB->AddString (str) ;
	}

	pLB->SetCurSel (oriSel) ;

}

void DLGItem::createPage()
{
	m_page1.Create(IDD_ItemTypeWeapon, &m_tab);
	m_page2.Create(IDD_ItemTypeArmor, &m_tab);
	m_page3.Create(IDD_ItemTypeConsumable, &m_tab);
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 2;
	rc.bottom -= 10;
	rc.left += 2;
	rc.right -= 10;
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);
	pDialog[WAEPON] = &m_page1;
	pDialog[ARMOR] = &m_page2;
	pDialog[CONSUMABLE] = &m_page3;
	m_CurSelTab = WAEPON;
}

void DLGItem::replaceSelItem(CItemInfo* pInfo)
{
	if(pInfo != NULL)
	{
		SetDlgItemText(IDC_ItemName, pInfo->getName().c_str());		//顯示名字

		CComboBox* pTB = (CComboBox*) GetDlgItem (IDC_ItemType);	//宣告ComboBox變數
		pTB->SetCurSel(pInfo->getItemType());						//顯示物品型態

		CButton* pChB = (CButton*) GetDlgItem (IDC_ItemSoulBind);	//宣告CheckBox變數
		pChB->SetCheck(pInfo->getSoulBind());						//顯示是否綁定

		SetDlgItemInt(IDC_ItemLevel,pInfo->getLevel());				//顯示使用等級
		
		SetDlgItemInt(IDC_ItemStackLimit,pInfo->getStackLimit());	//顯示堆疊上限
		
		SetDlgItemInt(IDC_ItemSellPrice,pInfo->getSellPrice());		//顯示賣價
		
		SetDlgItemInt(IDC_ItemBuyPrice,pInfo->getBuyPrice());		//顯示買價

		SetDlgItemText(IDC_iconName, pInfo->geticonName().c_str());	//顯示圖示名稱

		pageShow(pInfo);											//切換顯示頁面

	}

}

void DLGItem::pageShow(CItemInfo* pInfo)
{
	if(pInfo->getClassType() == WEAPON)
		{
			pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
			m_CurSelTab = WAEPON;
			pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

			CWeaponInfo* pWInfo;
			pWInfo = ((CWeaponInfo*) pInfo);

			m_page1.initPage(pWInfo);

		}
	else if(pInfo->getClassType() == ARMOR)
		{	
			pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
			m_CurSelTab = ARMOR;
			pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

			CArmorInfo* pAInfo;
			pAInfo = ((CArmorInfo*) pInfo);

			m_page2.initPage(pAInfo);
		}
	else if(pInfo->getClassType() == CONSUMABLE)
		{
			pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
			m_CurSelTab = CONSUMABLE;
			pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

			CConsumableInfo* pCInfo;
			pCInfo = ((CConsumableInfo*) pInfo);

			m_page3.initPage(pCInfo);
		}
}

void DLGItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_ItemTypeMenu,m_tab);

}

void DLGItem::OnClose () 
{
}

void DLGItem::OnOK () 
{
}

void DLGItem::OnCancel () 
{
}

BEGIN_MESSAGE_MAP(DLGItem, CDialog)
	ON_LBN_SELCHANGE(IDC_ItemList, &DLGItem::OnLbnSelchangeItemlist)
	ON_EN_CHANGE(IDC_ItemName, &DLGItem::OnEnChangeItemname)
	ON_CBN_SELCHANGE(IDC_ItemType, &DLGItem::OnCbnSelchangeItemtype)
	ON_BN_CLICKED(IDC_ItemSoulBind, &DLGItem::OnBnClickedItemsoulbind)
	ON_EN_CHANGE(IDC_ItemLevel, &DLGItem::OnEnChangeItemlevel)
	ON_EN_CHANGE(IDC_ItemStackLimit, &DLGItem::OnEnChangeItemstacklimit)
	ON_EN_CHANGE(IDC_ItemSellPrice, &DLGItem::OnEnChangeItemsellprice)
	ON_EN_CHANGE(IDC_ItemBuyPrice, &DLGItem::OnEnChangeItembuyprice)
	ON_BN_CLICKED(IDC_SaveList, &DLGItem::OnBnClickedSavelist)
	ON_BN_CLICKED(IDC_LoadList, &DLGItem::OnBnClickedLoadlist)
	ON_BN_CLICKED(IDC_AddItem, &DLGItem::OnBnClickedAdditem)
	ON_EN_CHANGE(IDC_iconName, &DLGItem::OnEnChangeiconname)
   ON_BN_CLICKED(IDC_DelItem, &DLGItem::OnBnClickedDelitem)
END_MESSAGE_MAP()


// DLGItem 訊息處理常式

void DLGItem::OnLbnSelchangeItemlist()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CListBox* pLB = (CListBox*) GetDlgItem (IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);

	replaceSelItem(pInfo);
	

}

void DLGItem::OnEnChangeItemname()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{
		CString str;
		GetDlgItemText(IDC_ItemName, str);		
		pInfo->setName((LPCTSTR) str);


		upDate();
	}
}

void DLGItem::OnCbnSelchangeItemtype()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{		
		CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_ItemType);

		int type = pTB->GetCurSel();
		CItemInfoLoader loader;
		if(WEAPON == pInfo->getClassType())
		{
			if(loader.isWeapon(type))
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
			else
			{
				pTB->SetCurSel(pInfo->getItemType());
			}
		}
		else if(ARMOR == pInfo->getClassType())
		{
			if(loader.isArmor(type))
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
			else
			{
				pTB->SetCurSel(pInfo->getItemType());
			}
		}
		else if(CONSUMABLE == pInfo->getClassType())
		{
			if(loader.isConsumable(type))
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
			else
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
		}


		pageShow(pInfo);

	}
}

void DLGItem::OnBnClickedItemsoulbind()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{		
		CButton* pCHB = (CButton*) GetDlgItem(IDC_ItemSoulBind);

		if(pCHB->GetCheck())
		{
			pInfo->setSoulBind(true);
		}
		else
		{
			pInfo->setSoulBind(false);
		}


	}
}

void DLGItem::OnEnChangeItemlevel()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setLevel(GetDlgItemInt(IDC_ItemLevel));


	}
}

void DLGItem::OnEnChangeItemstacklimit()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setStackLimit(GetDlgItemInt(IDC_ItemStackLimit));


	}
}

void DLGItem::OnEnChangeItemsellprice()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setSellPrice(GetDlgItemInt(IDC_ItemSellPrice));


	}
}

void DLGItem::OnEnChangeItembuyprice()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setBuyPrice(GetDlgItemInt(IDC_ItemBuyPrice));


	}
}

void DLGItem::OnBnClickedSavelist()
{
	// TODO: 在此加入控制項告知處理常式程式碼
    CItem::write ("Item.fla") ;
}

void DLGItem::OnBnClickedLoadlist()
{
	// TODO: Add your control notification handler code here
	CItem::read("Item.fla");
	upDate();
	CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList);
	pLB->SetCurSel(0);
	CItemInfo* pInfo = CItem::getInfo(0);
	replaceSelItem(pInfo);
}

void DLGItem::OnBnClickedAdditem()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CComboBox* pTB = (CComboBox*)GetDlgItem (IDC_addClass);
	if(WEAPON == (ItemClassType) pTB->GetCurSel())
	{
		CWeaponInfo* pWp = new CWeaponInfo();
		AdvancedAttribute baseAttr;
		AdvancedAttribute extendAttr;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);

		pWp->initWeaponInfo("武器", "", "", DAGGER, false, 0, 1, 0, 0, COMMON, baseAttr, extendAttr,
			ONE_HAND);

		CItem::addInfo(pWp);
	}
	else if(ARMOR == (ItemClassType) pTB->GetCurSel())
	{
		CArmorInfo* pAm = new CArmorInfo();
		AdvancedAttribute baseAttr;
		AdvancedAttribute extendAttr;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);

		pAm->initArmorInfo("防具", "", "", CLOTH, false, 0, 1, 0, 0, COMMON, baseAttr, extendAttr,
			CLOTHES);

		CItem::addInfo(pAm);
	}
	else if(CONSUMABLE == (ItemClassType) pTB->GetCurSel())
	{
		CConsumableInfo* pCs = new CConsumableInfo();
		
		pCs->initConsumableInfo("消耗物品", "", POTION, false, 0, 1, 0, 0, "文字說明", EDIBLE_HP, 0);

		CItem::addInfo(pCs);
	}
	upDate();
}

void DLGItem::OnEnChangeiconname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);

	if(NULL != pInfo)
	{
		CString str;
		GetDlgItemText(IDC_iconName,str);
		pInfo->seticonName((LPCTSTR) str);
	}
}

void DLGItem::OnBnClickedDelitem()
{
   CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList);
   if(pLB->GetCurSel() > -1) {
      int offset = pLB->GetCurSel();
      CItem::delInfo(offset);
      upDate();
   }
}
