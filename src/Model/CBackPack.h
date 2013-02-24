#ifndef _CBACKPACK_H_
#define _CBACKPACK_H_
#include "Common.h"
#include "CItem.h"
#include "IPlayerBackpackEventListener.h"

class CBackpack
{
   public:
	   void setGrid(int grid, CItem& itm);		           //設定格中內容是什麼(net pack使用)

	   CItem* getItem(int grid);					           //取得這格內容
      CItemInfo* getItemInfo(int grid);                 //取得這格內容

	   void addItem(int itemID, int &stack, int &grid);  //增加物品 id 物品編號 stack 數量
      void removeItem(int itemID);                      //移除物品(堆疊 - 1)
		void removeGrid(int grid);

      // Add by Darren Chen on 2013/01/13 {
      int getSize();                                     // 取得背包總格數

      /** @brief 加入監聽玩家背包事件的物件
        * @param pListener 監聽者 */
      void addPlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);

      /** @brief 移除監聽玩家背包事件的物件
           * @param pListener 監聽者 */
      void removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);
      // } Add by Darren Chen on 2013/01/13

	   void initBack();								          //預設角色建立有的物品

   private:
      /** @brief 通知玩家背包有更新 */
      void notifyPlayerBackpackUpdate();

	   CItem m_itemBack[BACK_MAX];

      std::set<IPlayerBackpackEventListener *> m_playerBackpackEventListeners; // 監聽玩家背包改變的監聽者列表
};

#endif