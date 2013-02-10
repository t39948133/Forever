#ifndef _CPLAYER_H_
#define _CPLAYER_H_
#include "CUnitObject.h"
#include "CBackpack.h"
#include "IPlayerAttrEventListener.h"
#include "IPlayerEquipEventListener.h"
#include "IPlayerBackpackEventListener.h"
#include "IPlayerHotKeyEventListener.h"

// Add by Darren Chen on 2013/01/12 {
typedef struct tagHOTKEYITEM {
   int     iField;  // 哪一個欄位的快捷鍵
   CItem  *pItem;   // 要放入HotKey列表內的物品
   CSkill *pSkill;  // 要放入HotKey列表內的技能
} HotKeyItem;
// } Add by Darren Chen on 2013/01/12

class CPlayer : public CUnitObject
{
public:
   CPlayer(std::string machineName, std::string strName, long long uid, char level = 1);	//建立角色 傳入名字、等級(預設建立後為1級)
   virtual ~CPlayer();  // Add by Darren Chen on 2013/01/12

	void addXP(unsigned int xp);	//增加XP unsigned 不帶負數
	unsigned int getXP();			//讀取XP
	unsigned int getXPMax();		//讀取最大XP
	CBackpack* getBackpack();		//取得背包

   /** @brief 穿到裝備欄上
     * @param es     裝備部位
     * @param itemID 物品編號 (某裝備)
     * Modify by Darren Chen on 2013/01/07 */
	void wearToEquipSlot(EquipSlot es, int itemID);
	void shedEquip(EquipSlot grid);	    //脫下 哪格裝備欄 裝備
	std::map<EquipSlot, int> getEquip(); //取得裝備map陣列
	int getEquip(EquipSlot equip);	    //取得哪一格裝備

   // Add by Darren Chen on 2012/12/26 {
   void addMoney(long long money);  // 增加金錢
   long long getMoney();            // 讀取金錢

   void useItem(int itemID);        // 使用id號物品(含武器/防具/消耗性道具)

   /** @brief 新增快捷鍵資料
     * @param newHotKeyItem 快捷鍵資料 */
   void addHotKeyItem(HotKeyItem &newHotKeyItem);

   /** @brief 取得快捷鍵資料
     * @param field 哪個欄位快捷鍵
     * @return 快捷鍵資料 */
   HotKeyItem* getHotKeyItem(int field);

   /** @brief 取得快捷鍵有幾個 */
   int getHotKeySize();

   void skillDamage(AdvancedAttribute targetAttr);

   /** @brief 加入監聽玩家屬性事件的物件
        * @param pListener 監聽者 */
   void addPlayerAttrEventListener(IPlayerAttrEventListener *pListener);

   /** @brief 移除監聽玩家屬性事件的物件
        * @param pListener 監聽者 */
   void removePlayerAttrEventListener(IPlayerAttrEventListener *pListener);

   /** @brief 加入監聽玩家裝備事件的物件
        * @param pListener 監聽者 */
   void addPlayerEquipEventListener(IPlayerEquipEventListener *pListener);

   /** @brief 移除監聽玩家裝備事件的物件
        * @param pListener 監聽者 */
   void removePlayerEquipEventListener(IPlayerEquipEventListener *pListener);

   /** @brief 加入監聽玩家背包事件的物件
        * @param pListener 監聽者 */
   void addPlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);

   /** @brief 移除監聽玩家背包事件的物件
        * @param pListener 監聽者 */
   void removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);

   /** @brief 加入監聽玩家快捷鍵事件的物件
        * @param pListener 監聽者 */
   void addPlayerHotKeyEventListener(IPlayerHotKeyEventListener *pListener);

   /** @brief 移除監聽玩家快捷鍵事件的物件
        * @param pListener 監聽者 */
   void removePlayerHotKeyEventListener(IPlayerHotKeyEventListener *pListener);

#ifdef _GAMEENGINE_2D_
   /** @brief Client端繪圖動作 
     * @param hdc 繪圖裝置 */
   /* virtual */ void draw(HDC hdc);
#endif
   // } Add by Darren Chen on 2012/12/26

private:
   friend class CWorldServer;         // 允許CWorldServer物件直接對private/protected成員做存取
   friend class CPacketPlayerDataWG;  // 允許CPacketPlayerDataWG物件直接對private/protected成員做存取
   friend class CPacketPlayerInit;    // 允許CPacketPlayerInit物件直接對private/protected成員做存取
   friend class CPacketPlayerData;

	void updateEquipAttr(); //更新裝備造成的角色屬性
   void updateSkillAvailable();

   // Add by Darren Chen on 2013/01/17 {
   /** @brief 通知玩家屬性(xp, money)有更新 */
   void notifyPlayerAttrUpdate();

   /** @brief 通知玩家裝備有更新
     * @param es     裝備部位
     * @param itemId 物品編號 (某裝備) */
   void notifyPlayerEquipUpdate(EquipSlot es, int itemID);

   /** @brief 通知玩家的快捷鍵有更新
     * @param pHotKeyItem 更新的快捷鍵 */
   void notifyPlayerHotKeyUpdate(HotKeyItem *pHotKeyItem);
   // } Add by Darren Chen on 2013/01/17

   unsigned int               m_xp;	        //經驗值
	unsigned int               m_xpMax;	     //最大經驗值
	char                       m_levelMax;	  //最高等級 預設50
	std::map<EquipSlot, int>   m_mEquip;	  //裝備欄
	CBackpack                 *m_pBackpack;  //背包

   // Add by Darren Chen on 2013/01/06 {
   long long                  m_money;     // 錢
   std::vector<HotKeyItem *> *m_pvtHotKey; // 快捷鍵資料

   std::set<IPlayerAttrEventListener *>     m_playerAttrEventListeners;     // 監聽玩家屬性改變的監聽者列表
   std::set<IPlayerEquipEventListener *>    m_playerEquipEventListeners;    // 監聽玩家裝備改變的監聽者列表
   std::set<IPlayerHotKeyEventListener *>   m_playerHotKeyEventListeners;   // 監聽玩家快捷鍵改變的監聽者列表
   // } Add by Darren Chen on 2013/01/06
};

#endif