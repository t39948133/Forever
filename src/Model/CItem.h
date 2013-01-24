#ifndef _CITEM_H_
#define _CITEM_H_
#include "obj_mTable.h"
#include "CItemInfoLoader.h"
#include "IItemEventListener.h"

typedef ObjTable <CItemInfo*, CItemInfoLoader> ITEM_INFO;

class CItem : public ITEM_INFO
{
public:	
	static void initItem ();
	CItem ();
	~CItem();
	bool addStack (int id, int& st);
	int getStack ();
	void create (int id, int st);

   /** @brief 物品堆疊減一, 減到0後會自動消滅物品 */
	void taken();

   // Add by Darren Chen on 2013/01/21 {
   /** @brief 加入監聽物品欄事件的物件
     * @param pListener 監聽者 */
   void addItemEventListener(IItemEventListener *pListener);

   /** @brief 移除監聽物品欄事件的物件
     * @param pListener 監聽者 */
   void removeItemEventListener(IItemEventListener *pListener);
   // } Add by Darren Chen on 2013/01/21

private:
	int m_iStack;

   // Add by Darren Chen on 2013/01/21 {
   /** @brief 通知物品欄有更新 */
   void notifyItemUpdate();

   std::set<IItemEventListener *> m_itemEventListeners;   // 監聽物品欄改變的監聽者列表
   // } Add by Darren Chen on 2013/01/21
};

#endif  // #ifndef _CITEM_H_