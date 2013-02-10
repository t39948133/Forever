// ActionEditorDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ActionEditor.h"
#include "ActionEditorDlg.h"
#include "CKeyActionEvent.h"
#include "CWASDKeyActionEvent.h"
#include "CCastSkillActionEvent.h"
#include "CNotifyActionEvent.h"
#include "CPlaySoundNotifyActionEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CActionEditorDlg 對話方塊




CActionEditorDlg::CActionEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CActionEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   m_pActionSystem = new CActionSystem("CActionEditor", 0);
   m_iActionListIdx = -1;
   m_iEventListIdx = -1;
}

void CActionEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CActionEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(BTN_NEWACTION, &CActionEditorDlg::OnBnClickedNewaction)
   ON_LBN_SELCHANGE(LST_ACTIONLIST, &CActionEditorDlg::OnLbnSelchangeActionlist)
   ON_BN_CLICKED(BTN_CANCELSELACTIONLIST, &CActionEditorDlg::OnBnClickedCancelselactionlist)
   ON_BN_CLICKED(BTN_DELACTION, &CActionEditorDlg::OnBnClickedDelaction)
   ON_BN_CLICKED(BTN_NEWEVENT, &CActionEditorDlg::OnBnClickedNewevent)
   ON_LBN_SELCHANGE(LST_EVENTLIST, &CActionEditorDlg::OnLbnSelchangeEventlist)
   ON_BN_CLICKED(BTN_CANCELSELEVENTLIST, &CActionEditorDlg::OnBnClickedCancelseleventlist)
   ON_BN_CLICKED(BTN_DELEVENT, &CActionEditorDlg::OnBnClickedDelevent)
   ON_BN_CLICKED(BTN_SAVE, &CActionEditorDlg::OnBnClickedSave)
   ON_BN_CLICKED(BTN_LOAD, &CActionEditorDlg::OnBnClickedLoad)
   ON_CBN_SELCHANGE(CMB_EVENT, &CActionEditorDlg::OnCbnSelchangeEvent)
END_MESSAGE_MAP()


// CActionEditorDlg 訊息處理常式

BOOL CActionEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

   CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
   pcmbMove->SetCurSel(1);

	CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
   pcmbEvent->SetCurSel(0);

   CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
   pbtnDelAction->EnableWindow(FALSE);

   CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
   pbtnNewEvent->EnableWindow(FALSE);

   CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
   pbtnDelEvent->EnableWindow(FALSE);

   CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
   pedtKey->EnableWindow(false);
   CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
   pedtKeyDown->EnableWindow(false);
   CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
   pedtKeyUp->EnableWindow(false);
   CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
   pedtBeginTime->EnableWindow(false);
   CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
   pedtEndTime->EnableWindow(false);
   CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
   pedtSoundFile->EnableWindow(false);

   SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
   CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
   pedtEventNextActionID->EnableWindow(true);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CActionEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CActionEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CActionEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CActionEditorDlg::updateActionList()
{
   CListBox *pActionList = (CListBox*)GetDlgItem(LST_ACTIONLIST);
   pActionList->ResetContent();

   std::vector<CAction *>::iterator it = m_pActionSystem->m_pActionVector->begin();
   while(it != m_pActionSystem->m_pActionVector->end()) {
      CString str;
      char buf[256];
      memset(buf, 0, sizeof(buf));
      sprintf_s(buf, "[%d] %s", (*it)->getID(), (*it)->getName().c_str());
		str = buf;
		pActionList->AddString(str);

      it++;
   }

   pActionList->SetCurSel(m_iActionListIdx);
}

void CActionEditorDlg::clearActionData()
{
   SetDlgItemText(EDT_ACTIONID, "");
   SetDlgItemText(EDT_ACTIONNAME, "");
   SetDlgItemText(EDT_ANINAME, "");
   SetDlgItemText(EDT_ANITIME, "");
   CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
   pcmbMove->SetCurSel(1);
   SetDlgItemText(EDT_NEXTACTIONID, "");
}

void CActionEditorDlg::updateEventList()
{
   CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
   pEventList->ResetContent();

   CString str;
   char buf[256];

   CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
   std::vector<CActionEventHandler *>::iterator it = pAction->m_pvtEventHandlerSet->begin();
   while(it != pAction->m_pvtEventHandlerSet->end()) {
      switch((*it)->m_pTriggerEvent->m_event) {
         case AET_NULL: {     
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NULL => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_REACH: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_REACH => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_NOT_REACH: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NOT_REACH => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_KEY: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_KEY => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_KEY_WASD: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_KEY_WASD => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_CAST_SKILL: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_CAST_SKILL => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_NOTIFY_DRAW_WEAPON: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NOTIFY_DRAW_WEAPON => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_NOTIFY_PUTIN_WEAPON: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NOTIFY_PUTIN_WEAPON => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_NOTIFY_PLAY_SOUND: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NOTIFY_PLAY_SOUND => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }
      }

      it++;
   }

   pEventList->SetCurSel(m_iEventListIdx);
}

void CActionEditorDlg::clearEventData()
{
   CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
   pcmbEvent->SetCurSel(0);
   SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
   SetDlgItemText(EDT_KEY, "");
   SetDlgItemText(EDT_KEYDOWN, "");
   SetDlgItemText(EDT_KEYUP, "");
   SetDlgItemText(EDT_BEGINTIME, "");
   SetDlgItemText(EDT_ENDTIME, "");
   SetDlgItemText(EDT_SOUNDFILE, "");
}

void CActionEditorDlg::OnBnClickedNewaction()
{
   CString str;
   ACTION_DATA actData;

   actData.iID           = GetDlgItemInt(EDT_ACTIONID);
   
   str.Empty();
   GetDlgItemText(EDT_ACTIONNAME, str);
   actData.name          = str.GetBuffer(0);
   
   str.Empty();
   GetDlgItemText(EDT_ANINAME, str);
   actData.animationName = str.GetBuffer(0);

   str.Empty();
   GetDlgItemText(EDT_ANITIME, str);
   std::string strFTime = str.GetBuffer(0);
   actData.fTime = fromString<float>(strFTime);

   CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
   int iMoveIdx = pcmbMove->GetCurSel();
   if(iMoveIdx == 0)
      actData.bMove      = true;
   else if(iMoveIdx == 1)
      actData.bMove      = false;

   actData.iNextActID    = GetDlgItemInt(EDT_NEXTACTIONID);

   if(m_iActionListIdx == -1) {
      CAction *pAction = new CAction();
      pAction->init(actData);
      m_pActionSystem->addAction(pAction);
   }
   else {
      CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
      pAction->m_iID = actData.iID;
      pAction->m_name = actData.name;
      pAction->m_animationName = actData.animationName;
      pAction->m_fTime = actData.fTime;
      pAction->m_bMove = actData.bMove;
      pAction->m_iNextActID = actData.iNextActID;
   }

   //---此筆資料顯示於List
   updateActionList();

   clearActionData();

   if(m_iActionListIdx == -1) {
      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(FALSE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(FALSE);

      CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
      pbtnDelEvent->EnableWindow(FALSE);
   }
   else {
      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(TRUE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(TRUE);
   }
}

void CActionEditorDlg::OnLbnSelchangeActionlist()
{
   CListBox *pActionList = (CListBox*)GetDlgItem(LST_ACTIONLIST);
   m_iActionListIdx = pActionList->GetCurSel();

   if(m_iActionListIdx > -1) {
      CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);

      SetDlgItemText(EDT_ACTIONID, toString<int>(pAction->m_iID).c_str());
      SetDlgItemText(EDT_ACTIONNAME, pAction->m_name.c_str());
      SetDlgItemText(EDT_ANINAME, pAction->m_animationName.c_str());
      SetDlgItemText(EDT_ANITIME, toString<float>(pAction->m_fTime).c_str());

      CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
      if(pAction->m_bMove == true)
         pcmbMove->SetCurSel(0);
      else if(pAction->m_bMove == false)
         pcmbMove->SetCurSel(1);

      SetDlgItemText(EDT_NEXTACTIONID, toString<int>(pAction->m_iNextActID).c_str());

      OnBnClickedCancelseleventlist();

      // 顯示Action內的所有Event
      updateEventList();

      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(TRUE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(TRUE);
   }
   else {
      clearActionData();

      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(FALSE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(FALSE);

      CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
      pbtnDelEvent->EnableWindow(FALSE);
   }
}

void CActionEditorDlg::OnBnClickedCancelselactionlist()
{
   CListBox *pActionList = (CListBox*)GetDlgItem(LST_ACTIONLIST);
   m_iActionListIdx = -1;
   pActionList->SetCurSel(m_iActionListIdx);

   //---清除
   clearActionData();

   // 取消EventList的選擇
   OnBnClickedCancelseleventlist();

   // 清除EventList
   CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
   pEventList->ResetContent();

   CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
   pbtnDelAction->EnableWindow(FALSE);

   CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
   pbtnNewEvent->EnableWindow(FALSE);

   CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
   pbtnDelEvent->EnableWindow(FALSE);
}

void CActionEditorDlg::OnBnClickedDelaction()
{
   if(m_iActionListIdx > -1) {
      CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
      std::vector<CAction *>::iterator it = m_pActionSystem->m_pActionVector->begin();
      while(it != m_pActionSystem->m_pActionVector->end()) {
         if((*it) == pAction) {
            m_pActionSystem->m_pActionVector->erase(it);
            break;
         }

         it++;
      }

      if(m_iActionListIdx >= (int)m_pActionSystem->m_pActionVector->size())
         m_iActionListIdx--;

      updateActionList();
      OnLbnSelchangeActionlist();
   }
}

void CActionEditorDlg::OnBnClickedNewevent()
{
   if(m_iActionListIdx > -1) {
      CActionEvent *pActionEvent = NULL;
      CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);

      if(pcmbEvent->GetCurSel() == 0) {
         pActionEvent = new CActionEvent();
         pActionEvent->m_event = AET_NULL;
      }
      else if(pcmbEvent->GetCurSel() == 1) {
         pActionEvent = new CActionEvent();
         pActionEvent->m_event = AET_REACH;
      }
      else if(pcmbEvent->GetCurSel() == 2) {
         pActionEvent = new CActionEvent();
         pActionEvent->m_event = AET_NOT_REACH;
      }
      else if(pcmbEvent->GetCurSel() == 3) {
         CKeyActionEvent *pEvent = new CKeyActionEvent();
         pEvent->m_event = AET_KEY;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_KEY, str);
         std::string strKey = str.GetBuffer(0);
         pEvent->m_iKeyID = int(*(strKey.c_str()));

         pActionEvent = pEvent;
      }
      else if(pcmbEvent->GetCurSel() == 4) {
         CWASDKeyActionEvent *pEvent = new CWASDKeyActionEvent();
         pEvent->m_event = AET_KEY_WASD;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_KEYDOWN, str);
         std::string strKeyDown = str.GetBuffer(0);
         pEvent->m_iKeyDownID = int(*(strKeyDown.c_str()));

         str.Empty();
         GetDlgItemText(EDT_KEYUP, str);
         std::string strKeyUp = str.GetBuffer(0);
         pEvent->m_iKeyUpID = int(*(strKeyUp.c_str()));

         pActionEvent = pEvent;
      }
      else if(pcmbEvent->GetCurSel() == 5) {
         CCastSkillActionEvent *pEvent = new CCastSkillActionEvent();
         pEvent->m_event = AET_CAST_SKILL;

         pActionEvent = pEvent;
      }
      else if(pcmbEvent->GetCurSel() == 6) {
         CNotifyActionEvent *pEvent = new CNotifyActionEvent();
         pEvent->m_event = AET_NOTIFY_DRAW_WEAPON;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_BEGINTIME, str);
         std::string strFTime = str.GetBuffer(0);
         pEvent->m_fBeginTime = fromString<float>(strFTime);

         str.Empty();
         strFTime.clear();
         GetDlgItemText(EDT_ENDTIME, str);
         strFTime = str.GetBuffer(0);
         pEvent->m_fEndTime = fromString<float>(strFTime);

         pActionEvent = pEvent;
      }
      else if(pcmbEvent->GetCurSel() == 7) {
         CNotifyActionEvent *pEvent = new CNotifyActionEvent();
         pEvent->m_event = AET_NOTIFY_PUTIN_WEAPON;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_BEGINTIME, str);
         std::string strFTime = str.GetBuffer(0);
         pEvent->m_fBeginTime = fromString<float>(strFTime);

         str.Empty();
         strFTime.clear();
         GetDlgItemText(EDT_ENDTIME, str);
         strFTime = str.GetBuffer(0);
         pEvent->m_fEndTime = fromString<float>(strFTime);

         pActionEvent = pEvent;
      }
      else if(pcmbEvent->GetCurSel() == 8) {
         CPlaySoundNotifyActionEvent *pEvent = new CPlaySoundNotifyActionEvent();
         pEvent->m_event = AET_NOTIFY_PLAY_SOUND;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_BEGINTIME, str);
         std::string strFTime = str.GetBuffer(0);
         pEvent->m_fBeginTime = fromString<float>(strFTime);

         str.Empty();
         strFTime.clear();
         GetDlgItemText(EDT_ENDTIME, str);
         strFTime = str.GetBuffer(0);
         pEvent->m_fEndTime = fromString<float>(strFTime);

         str.Empty();
         GetDlgItemText(EDT_SOUNDFILE, str);
         pEvent->m_soundFile = str.GetBuffer(0);

         pActionEvent = pEvent;
      }

      if(m_iEventListIdx == -1) {
         CActionEventHandler *pActionEventHandler = new CActionEventHandler();
         pActionEventHandler->init(pActionEvent, GetDlgItemInt(EDT_EVENTNEXTACTIONID));

         CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
         pAction->addEventHandler(pActionEventHandler);
      }
      else {
         CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
         CActionEventHandler *pActionEventHandler = pAction->m_pvtEventHandlerSet->at(m_iEventListIdx);

         pActionEventHandler->m_pTriggerEvent = pActionEvent;
         pActionEventHandler->m_iNextActionID = GetDlgItemInt(EDT_EVENTNEXTACTIONID);
      }

      updateEventList();

      OnBnClickedCancelseleventlist();
   }
}

void CActionEditorDlg::OnLbnSelchangeEventlist()
{
   if(m_iActionListIdx > -1) {
      CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
      m_iEventListIdx = pEventList->GetCurSel();

      if(m_iEventListIdx > -1) {
         clearEventData();
         CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
         CActionEventHandler *pActionEventHandler = pAction->m_pvtEventHandlerSet->at(m_iEventListIdx);

         CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
         switch(pActionEventHandler->m_pTriggerEvent->m_event) {
            case AET_NULL:
               pcmbEvent->SetCurSel(0);
               OnCbnSelchangeEvent();
               break;

            case AET_REACH:
               pcmbEvent->SetCurSel(1);
               OnCbnSelchangeEvent();
               break;

            case AET_NOT_REACH:
               pcmbEvent->SetCurSel(2);
               OnCbnSelchangeEvent();
               break;

            case AET_KEY: {
               pcmbEvent->SetCurSel(3);
               OnCbnSelchangeEvent();

               CKeyActionEvent *pKeyActionEvent = (CKeyActionEvent *)pActionEventHandler->m_pTriggerEvent;
               std::string strKey;
               strKey.clear();
               strKey = (char)pKeyActionEvent->m_iKeyID;
               SetDlgItemText(EDT_KEY, strKey.c_str());
               break;
            }

            case AET_KEY_WASD: {
               pcmbEvent->SetCurSel(4);
               OnCbnSelchangeEvent();

               CWASDKeyActionEvent *pWASDKeyActionEvent = (CWASDKeyActionEvent *)pActionEventHandler->m_pTriggerEvent;

               std::string strKey;
               strKey.clear();
               strKey = (char)pWASDKeyActionEvent->m_iKeyDownID;
               SetDlgItemText(EDT_KEYDOWN, strKey.c_str());

               strKey.clear();
               strKey = (char)pWASDKeyActionEvent->m_iKeyUpID;
               SetDlgItemText(EDT_KEYUP, strKey.c_str());
               break;
            }

            case AET_CAST_SKILL:
               pcmbEvent->SetCurSel(5);
               OnCbnSelchangeEvent();
               break;

            case AET_NOTIFY_DRAW_WEAPON: {
               pcmbEvent->SetCurSel(6);
               OnCbnSelchangeEvent();

               CNotifyActionEvent *pNotifyActionEvent = (CNotifyActionEvent *)pActionEventHandler->m_pTriggerEvent;

               SetDlgItemText(EDT_BEGINTIME, toString<float>(pNotifyActionEvent->m_fBeginTime).c_str());
               SetDlgItemText(EDT_ENDTIME, toString<float>(pNotifyActionEvent->m_fEndTime).c_str());
               break;
            }

            case AET_NOTIFY_PUTIN_WEAPON: {
               pcmbEvent->SetCurSel(7);
               OnCbnSelchangeEvent();

               CNotifyActionEvent *pNotifyActionEvent = (CNotifyActionEvent *)pActionEventHandler->m_pTriggerEvent;

               SetDlgItemText(EDT_BEGINTIME, toString<float>(pNotifyActionEvent->m_fBeginTime).c_str());
               SetDlgItemText(EDT_ENDTIME, toString<float>(pNotifyActionEvent->m_fEndTime).c_str());
               break;
            }

            case AET_NOTIFY_PLAY_SOUND: {
               pcmbEvent->SetCurSel(8);
               OnCbnSelchangeEvent();

               CPlaySoundNotifyActionEvent *pPlaySoundNotifyActionEvent = (CPlaySoundNotifyActionEvent *)pActionEventHandler->m_pTriggerEvent;

               SetDlgItemText(EDT_BEGINTIME, toString<float>(pPlaySoundNotifyActionEvent->m_fBeginTime).c_str());
               SetDlgItemText(EDT_ENDTIME, toString<float>(pPlaySoundNotifyActionEvent->m_fEndTime).c_str());
               SetDlgItemText(EDT_SOUNDFILE, pPlaySoundNotifyActionEvent->m_soundFile.c_str());
               break;
            }
         }

         SetDlgItemText(EDT_EVENTNEXTACTIONID, toString<int>(pActionEventHandler->getNextActionID()).c_str());

         CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
         pbtnDelEvent->EnableWindow(TRUE);
      }
      else {
         clearEventData();

         CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
         pbtnDelEvent->EnableWindow(FALSE);
      }
   }
}

void CActionEditorDlg::OnBnClickedCancelseleventlist()
{
   CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
   m_iEventListIdx = -1;
   pEventList->SetCurSel(m_iEventListIdx);

   //---清除
   clearEventData();

   OnCbnSelchangeEvent();

   CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
   pbtnDelEvent->EnableWindow(FALSE);
}

void CActionEditorDlg::OnBnClickedDelevent()
{
   if(m_iActionListIdx > -1) {
      if(m_iEventListIdx > -1) {
         CAction *pAction = m_pActionSystem->m_pActionVector->at(m_iActionListIdx);
         CActionEventHandler *pActionEventHandler = pAction->m_pvtEventHandlerSet->at(m_iEventListIdx);

         std::vector<CActionEventHandler *>::iterator it = pAction->m_pvtEventHandlerSet->begin();
         while(it != pAction->m_pvtEventHandlerSet->end()) {
            if((*it) == pActionEventHandler) {
               pAction->m_pvtEventHandlerSet->erase(it);
               break;
            }

            it++;
         }

         if(m_iEventListIdx >= (int)pAction->m_pvtEventHandlerSet->size())
            m_iEventListIdx--;

         updateEventList();
         OnLbnSelchangeEventlist();
      }
   }
}

void CActionEditorDlg::OnBnClickedSave()
{
   TCHAR szFilters[]= "ActionSystem Files (*.acs)|*.acs||";
   CFileDialog fileDlg(FALSE, "acs", "*.acs", OFN_HIDEREADONLY, szFilters);
   if(fileDlg.DoModal() == IDOK) {
      CString fullPathFileName = fileDlg.GetPathName();
      m_pActionSystem->write(fullPathFileName.GetBuffer(0));

      fullPathFileName = CString("檔名：") + fullPathFileName;
      SetDlgItemText(TXT_FILENAME, fullPathFileName);
   }
}

void CActionEditorDlg::OnBnClickedLoad()
{
   TCHAR szFilters[]= "ActionSystem Files (*.acs)|*.acs||";
   CFileDialog fileDlg(TRUE, "acs", "*.acs", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
   if(fileDlg.DoModal() == IDOK) {
      CString fullPathFileName = fileDlg.GetPathName();
      m_pActionSystem->read(fullPathFileName.GetBuffer(0));

      fullPathFileName = CString("檔名：") + fullPathFileName;
      SetDlgItemText(TXT_FILENAME, fullPathFileName);

      updateActionList();
   }
}

void CActionEditorDlg::OnCbnSelchangeEvent()
{
   CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
   switch(pcmbEvent->GetCurSel()) {
      case 0:    // AET_NULL
      case 1:    // AET_REACH
      case 2: {  // AET_NOT_REACH
         CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
         pedtKey->EnableWindow(false);
         CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
         pedtKeyDown->EnableWindow(false);
         CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
         pedtKeyUp->EnableWindow(false);
         CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
         pedtBeginTime->EnableWindow(false);
         CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
         pedtEndTime->EnableWindow(false);
         CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
         pedtSoundFile->EnableWindow(false);

         SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
         CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
         pedtEventNextActionID->EnableWindow(true);
         break;
      }

      case 3: {  // AET_KEY
         CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
         pedtKey->EnableWindow(true);
         CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
         pedtKeyDown->EnableWindow(false);
         CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
         pedtKeyUp->EnableWindow(false);
         CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
         pedtBeginTime->EnableWindow(false);
         CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
         pedtEndTime->EnableWindow(false);
         CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
         pedtSoundFile->EnableWindow(false);

         SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
         CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
         pedtEventNextActionID->EnableWindow(true);
         break;
      }

      case 4: {  // AET_KEY_WASD
         CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
         pedtKey->EnableWindow(false);
         CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
         pedtKeyDown->EnableWindow(true);
         CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
         pedtKeyUp->EnableWindow(true);
         CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
         pedtBeginTime->EnableWindow(false);
         CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
         pedtEndTime->EnableWindow(false);
         CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
         pedtSoundFile->EnableWindow(false);

         SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
         CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
         pedtEventNextActionID->EnableWindow(true);
         break;
      }

      case 5: {  // AET_CAST_SKILL
         CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
         pedtKey->EnableWindow(false);
         CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
         pedtKeyDown->EnableWindow(false);
         CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
         pedtKeyUp->EnableWindow(false);
         CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
         pedtBeginTime->EnableWindow(false);
         CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
         pedtEndTime->EnableWindow(false);
         CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
         pedtSoundFile->EnableWindow(false);

         SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
         CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
         pedtEventNextActionID->EnableWindow(true);
         break;
      }

      case 6:    // AET_NOTIFY_DRAW_WEAPON
      case 7: {  // AET_NOTIFY_PUTIN_WEAPON
         CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
         pedtKey->EnableWindow(false);
         CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
         pedtKeyDown->EnableWindow(false);
         CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
         pedtKeyUp->EnableWindow(false);
         CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
         pedtBeginTime->EnableWindow(true);
         CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
         pedtEndTime->EnableWindow(true);
         CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
         pedtSoundFile->EnableWindow(false);

         SetDlgItemText(EDT_EVENTNEXTACTIONID, "-1");
         CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
         pedtEventNextActionID->EnableWindow(false);
         break;
      }

      case 8: {  // AET_NOTIFY_PLAY_SOUND
         CEdit *pedtKey = (CEdit*)GetDlgItem(EDT_KEY);
         pedtKey->EnableWindow(false);
         CEdit *pedtKeyDown = (CEdit*)GetDlgItem(EDT_KEYDOWN);
         pedtKeyDown->EnableWindow(false);
         CEdit *pedtKeyUp = (CEdit*)GetDlgItem(EDT_KEYUP);
         pedtKeyUp->EnableWindow(false);
         CEdit *pedtBeginTime = (CEdit*)GetDlgItem(EDT_BEGINTIME);
         pedtBeginTime->EnableWindow(true);
         CEdit *pedtEndTime = (CEdit*)GetDlgItem(EDT_ENDTIME);
         pedtEndTime->EnableWindow(true);
         CEdit *pedtSoundFile = (CEdit*)GetDlgItem(EDT_SOUNDFILE);
         pedtSoundFile->EnableWindow(true);

         SetDlgItemText(EDT_EVENTNEXTACTIONID, "-1");
         CEdit *pedtEventNextActionID = (CEdit*)GetDlgItem(EDT_EVENTNEXTACTIONID);
         pedtEventNextActionID->EnableWindow(false);
         break;
      }
   }
}
