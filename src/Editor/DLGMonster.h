#pragma once


// DLGMonster 對話方塊

class DLGMonster : public CDialog
{
	DECLARE_DYNAMIC(DLGMonster)

public:
	DLGMonster(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~DLGMonster();

// 對話方塊資料
	enum { IDD = IDD_MonsterEdit };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
};
