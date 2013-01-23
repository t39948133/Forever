#ifndef _CPLAYER_H_
#define _CPLAYER_H_
#include "CUnitObject.h"
#include "CBackPack.h"

// Add by Darren Chen on 2013/01/12 {
typedef struct tagHOTKEYITEM {
   CItem *pItem;    // 要放入HotKey列表內的物品
   CSkill *pSkill;  // 要放入HotKey列表內的技能
} HotKeyItem;
// } Add by Darren Chen on 2013/01/12

class CPlayer : public CUnitObject
{
public:
	CPlayer(std::string strName, long long uid, char level = 1);	//建立角色 傳入名字、等級(預設建立後為1級)
   virtual ~CPlayer();  // Add by Darren Chen on 2013/01/12

	void addXP(unsigned int xp);	//增加XP unsigned 不帶負數
	unsigned int getXP();			//讀取XP
	unsigned int getXPMax();		//讀取最大XP
	CBackPack getBackPack();		//取得背包

	void shedEquip(EquipSlot grid);	    //脫下 哪格裝備欄 裝備
	std::map<EquipSlot, int> getEquip(); //取得裝備map陣列
	int getEquip(EquipSlot equip);	    //取得哪一格裝備

   // Add by Darren Chen on 2012/12/26 {
   void addMoney(long long money);  // 增加金錢
   long long getMoney();            // 讀取金錢

   void useItem(unsigned int itemID);   // 使用id號物品(含武器/防具/消耗性道具)

   /** @brief 新增快捷鍵資料
     * @param field         哪個欄位快捷鍵
     * @param newHotKeyItem 快捷鍵資料 */
   void addHotKeyItem(int field, HotKeyItem &newHotKeyItem);

   /** @brief 取得快捷鍵資料
     * @param field 哪個欄位快捷鍵
     * @return 快捷鍵資料 */
   HotKeyItem* getHotKeyItem(int field);

   /** @brief 取得快捷鍵有幾個 */
   int getHotKeySize();

   void skillDamage(AdvancedAttribute targetAttr);

#ifdef _GAMEENGINE_2D_
   /** @brief Client端繪圖動作 
     * @param hdc 繪圖裝置 */
   /* virtual */ void draw(HDC hdc);
#endif
   // } Add by Darren Chen on 2012/12/26

private:
	void updateEquipAttr(); //更新裝備造成的角色屬性
        void updateSkillAvailable();

   /** @brief 穿到裝備欄上
     * @param es 裝備部位
     * @param id 新裝備編號
     * Modify by Darren Chen on 2013/01/07 */
	void wearToEquipSlot(EquipSlot es, unsigned int id);

   // Add by Darren Chen on 2013/01/17 {
   /** @brief 通知監聽者本物件的背包有更新 */
   void notifyUpdateBackpack();
   void notifyUpdateBackpack(CItem *pItem);

   /** @brief 通知監聽者本物件的HotKeyItem有更新
     * @param field       哪個欄位快捷鍵
     * @param pHotKeyItem 更新的項目 */
   void notifyUpdateHotKeyItem(int field, HotKeyItem *pHotKeyItem);
   // } Add by Darren Chen on 2013/01/17

   unsigned int               m_xp;	       //經驗值
	unsigned int               m_xpMax;	    //最大經驗值
	char                       m_levelMax;	 //最高等級 預設50
	std::map<EquipSlot, int>   m_mEquip;	 //裝備欄
	CBackPack                  m_backPack;  //背包

   // Add by Darren Chen on 2013/01/06 {
   long long                  m_money;     // 錢
   std::vector<HotKeyItem *> *m_pvtHotKey; // 快捷鍵資料
   // } Add by Darren Chen on 2013/01/06
};

#endif