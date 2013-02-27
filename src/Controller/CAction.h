/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CAction.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#ifndef _CACTION_H_
#define _CACTION_H_
#include "CActionEventHandler.h"

typedef struct tagACTION {
   int         iID;            // 動作編號
   std::string name;           // 動作名稱
   float       fTime;          // 動作時間
   std::string animationName;  // 動畫名稱
   int         iNextActID;     // 動作撥完後下一個動作
   bool        bMove;          // 是否可移動
} ACTION_DATA;

/** @brief 動作
  *        玩家動作  ():Event
  *          Idle動作->(座標更動)->跑步動作
  *          Idle動作->(拔出武器快捷鍵)->戰鬥姿態動作
  *          Idle動作->(被怪物打)->戰鬥姿態動作
  *          Idle動作->(距離過遠,施展技能)->戰鬥姿態動作
  *          Idle動作->(技能範圍內,施展技能)->戰鬥姿態動作
  *
  *          戰鬥姿態動作->(技能範圍內,施展技能)->技能動作->普通攻擊動作->戰鬥姿態動作
  *          戰鬥姿態動作->(座標更動)->戰鬥姿態的跑步動作
  *          戰鬥姿態動作->(非戰鬥狀態1分鐘後)->Idle動作
  *          戰鬥姿態動作->(非戰鬥狀態收武器快捷鍵)->Idle動作
  *
  *          跑步動作->(座標無更動)->Idle動作
  *          跑步動作->(被怪物打)->戰鬥姿態動作
  *
  *          戰鬥姿態的跑步動作->(座標無更動)->戰鬥姿態動作
  *          戰鬥姿態的跑步動作->(被怪物打)->戰鬥姿態動作
  *          戰鬥姿態的跑步動作->(非戰鬥狀態1分鐘後)->跑步動作 */
class CAction
{
   public:
      CAction();
      ~CAction();

      /** @brief 初始化
        * @param data 動作資料 */
      void init(ACTION_DATA &data);

      /** @brief 加入影響的事件
        * @param pHandler 動作事件 */
      void addEventHandler(CActionEventHandler *pHandler);

      /** @brief 取得動作編號
        * @return 動作編號 */
      int getID();

      /** @brief 動作更新
        * @param fPreTime    上一次時間
        * @param fCurTime    目前時間
        * @param pEvent      動作事件
        * @param pKeyDownSet 按鍵按下的列表
        * @return 下一個動作編號 (< 0 表示無動作) */
      int work(float fPreTime, float fCurTime, CActionEvent *pEvent, std::set<int> *pKeyDownSet);

      /** @brief 取得動畫名稱
        * @return 動畫名稱 */
      std::string getAnimationName();

      /** @brief 是否可移動
        * @return true - 可移動 / false - 不可移動 */
      bool isMove();

      /** @brief 取得動作名稱
        * @return 動作名稱 */
      std::string getName();

      void setUID(long long uid);

      void setMachineName(std::string machineName);

      /** @brief 取得播放下一個動作ID
        * @return  0    重複播放
        *         -1    只播放一次
        *         > 0   下一個動作ID */
      int getNextActionID();

      /** @brief 取得該動作的時間長度 */
      float getActionTimeLength();

      /** @brief 存檔
        * @param pFile 檔案 */
      void write(FILE *pFile);

      /** @brief 讀檔
        * @param pFile 檔案 */
      void read(FILE *pFile);

   private:
      friend class CActionEditorDlg; // 允許動作編輯器來存取此物件

      std::string m_machineName;    // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      int         m_iID;            // 動作編號
      std::string m_name;           // 動作名稱
      float       m_fTime;          // 動作時間
      std::string m_animationName;  // 動畫名稱
      int         m_iNextActID;     // 動作撥完後下一個動作
      bool        m_bMove;          // 是否可移動
      long long   m_uid;            // 玩家、怪物、NPC的唯一編號

      std::vector<CActionEventHandler *> m_eventHandlerSet;  // 該動作會受哪些事件影響而更換動作
};

#endif  // #ifndef _CACTION_H_