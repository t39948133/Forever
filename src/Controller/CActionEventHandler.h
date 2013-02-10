/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEventHandler.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#ifndef _CACTIONEVENTHANDLER_H_
#define _CACTIONEVENTHANDLER_H_
#include "Common.h"
#include "CActionEvent.h"

/** @brief 觸發動作改變的事件 */
class CActionEventHandler
{
   public:
      CActionEventHandler();
      ~CActionEventHandler();

      /** @brief 初始化
        * @param pTriggerEvent 觸發動作事件
        * @param nextActionID  下一個動作 */
      void init(CActionEvent *pTriggerEvent, int nextActionID);

      /** @brief 取得下一個動作編號
        * @return 動作編號 */
      int getNextActionID();

      /** @brief 檢查觸發的事件是否與Handler相符合
        * @param fPreTime    上一次時間
        * @param fCurTime    目前時間
        * @param pEvent      觸發的動作事件
        * @param pKeyDownSet 按鍵按下的列表
        * @return true  - 相符合換動作
        *         false - 不符合不換動作 */
      bool check(float fPreTime, float fCurTime, CActionEvent *pEvent, std::set<int> *pKeyDownSet);

      void setUID(long long uid);

      void setMachineName(std::string machineName);

      /** @brief 存檔
        * @param pFile 檔案 */
      void write(FILE *pFile);

      /** @brief 讀檔
        * @param pFile 檔案 */
      void read(FILE *pFile);

   private:
      friend class CActionEditorDlg;  // 允許動作編輯器來存取此物件

      std::string   m_machineName;    // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      CActionEvent *m_pTriggerEvent;  // 觸發訊息
      int           m_iNextActionID;  // 觸發後要執行某個動作
      long long     m_uid;            // 玩家、怪物、NPC的唯一編號
};

#endif  // #ifndef _CACTIONEVENTHANDLER_H_