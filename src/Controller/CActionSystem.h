/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionSystem.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#ifndef _CACTIONSYSTEM_H_
#define _CACTIONSYSTEM_H_
#include "CAction.h"
#include "CActionEvent.h"
#include "CNotifyActionEvent.h"
#include "IDrawWeaponNotifyListener.h"
#include "IPutinWeaponNotifyListener.h"
#include "IPlaySoundNotifyListener.h"

/** @brief 動作系統 
  *        可用於玩家、怪物、NPC */
class CActionSystem
{
   public:
      CActionSystem(std::string machineName, long long uid);
      ~CActionSystem();
   
      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒 */
      void work(float timePass);

      /** @brief 是否改變動作
        * @return true - 改變 / false - 沒改變 */
      bool isChangeAction();

      /** @brief 取得目前的動作資訊
        * @return 動作資訊 */
      CAction* getCurAction();

      /** @brief 新增動作資訊
        * @param pAction 動作資訊 */
      void addAction(CAction *pAction);

      /** @brief 是否可移動
        * @return true - 可移動 / false - 不可移動 */
      bool isMove();

      /** @brief 取得所有動畫名稱
        * @return 所有動畫名稱 */
      std::vector<std::string> getAllAnimationName();

#ifdef _GAMEENGINE_2D_
      /** @brief Client端繪圖動作 
        * @param hdc 繪圖裝置
        * @param x   要畫在哪裡的X座標
        * @param y   要畫在哪裡的Y座標 */
      void draw(HDC hdc, int x, int y);
#endif

      /** @brief 存檔
        * @param fileName 檔案名稱 */
      void write(std::string fileName);

      /** @brief 讀檔
        * @param fileName 檔案名稱 */
      bool read(std::string fileName);

      void addDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);
      void removeDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);

      void addPutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);
      void removePutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);

      void addPlaySoundNotifyListener(IPlaySoundNotifyListener *pListener);
      void removePlaySoundNotifyListener(IPlaySoundNotifyListener *pListener);

   private:
      /** @brief 切換動作
        * @param newActionID 新動作編號 */
      void changeAction(int newActionID);

      /** @brief 寄送動作訊息
        * @param actEvent 動作訊息 */
      void sendEvent(CActionEvent &actEvent);

      /** @brief 寄送通知訊息
        * @param pNotifyActionEvent 通知訊息 */
      void sendNotify(CNotifyActionEvent *pNotifyActionEvent);

      /** @brief 處理通知訊息 */
      void procNotify();

      friend class CActionDispatch;  // 允許CActionDispatch來存取此物件的private成員
      friend class CActionEditorDlg; // 允許動作編輯器來存取此物件
      friend class CUnitObject;

      std::string m_machineName;   // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      std::string m_actionFile;    // 動作系統是使用哪個檔案
      float       m_fCurTime;      // 目前的時間
      int         m_iCurAction;    // 目前動作
      long long   m_uid;           // 玩家、怪物、NPC的唯一編號
      bool        m_bChangeAction; // 動作是否改變
      
      std::vector<CActionEvent *>       *m_pEventQueue;   // Action Event Queue
      std::vector<CNotifyActionEvent *> *m_pNotifyQueue;  // Action Notify Queue
      std::vector<CAction *>            *m_pActionVector; // 動作集合
      std::set<int>                     *m_pKeyDownSet;   // 記錄按鍵按下

      std::set<IDrawWeaponNotifyListener *>  m_drawWeaponNotifyListeners;
      std::set<IPutinWeaponNotifyListener *> m_putinWeaponNotifyListeners;
      std::set<IPlaySoundNotifyListener *>   m_playSoundNotifyListeners;
};

#endif  // #ifndef _CACTIONSYSTEM_H_