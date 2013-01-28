#pragma once

#include "CBuff.h"

// DLGBuff 對話方塊

class DLGBuff : public CDialog
{
	DECLARE_DYNAMIC(DLGBuff)

public:
	DLGBuff(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~DLGBuff();

// 對話方塊資料
	enum { IDD = IDD_BuffEdit };

    void initDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
   
    void OnClose () ;
	void OnOK () ;
	void OnCancel () ;

    void upDate();
    void replaceSelBuff(CBuffInfo* pInfo);
    void attrShow(ComplexAttribute com);
    void attrShow(FloatPrecentAttribute pre);
    void attrSave(ComplexAttribute& com);
    void attrSave(FloatPrecentAttribute& pre);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLbnSelchangeBufflist();
    afx_msg void OnEnChangeBuffname();
    afx_msg void OnEnChangeBufficonname();
    afx_msg void OnCbnSelchangeBuffharmful();
    afx_msg void OnEnChangeBuffcontinued();
    afx_msg void OnEnChangeBuffdesc();
    afx_msg void OnBnClickedBuffattrsave();
    afx_msg void OnCbnSelchangeBuffattrtype();
private:
    enum{BASE_ATTR, PRECENT_ATTR};
    int AttrType;
public:
    afx_msg void OnBnClickedAddbuff();
    afx_msg void OnBnClickedSavebuff();
    afx_msg void OnBnClickedLoadbuff();
    afx_msg void OnBnClickedDelbuff();
};
