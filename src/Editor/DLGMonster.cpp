// DLGMonster.cpp : 實作檔
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "DLGMonster.h"


// DLGMonster 對話方塊

IMPLEMENT_DYNAMIC(DLGMonster, CDialog)

DLGMonster::DLGMonster(CWnd* pParent /*=NULL*/)
	: CDialog(DLGMonster::IDD, pParent)
{

}

DLGMonster::~DLGMonster()
{
}

void DLGMonster::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DLGMonster, CDialog)
END_MESSAGE_MAP()


// DLGMonster 訊息處理常式
