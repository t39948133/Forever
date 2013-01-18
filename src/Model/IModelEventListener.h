/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IModelEventListener.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/16 */
#ifndef _IMODELEVENTLISTENER_H_
#define _IMODELEVENTLISTENER_H_
#include "Common.h"

class CUnitObject;
class CSkill;
typedef struct tagHOTKEYITEM HotKeyItem;

/** @brief Model事件監聽, 可以通知需要知道的物件 */
class IModelEventListener
{
   public:
      /** @brief 更新進階屬性 
        * @param pUnitObject 更新的物件 */
      virtual void updateAdvAttr(CUnitObject *pUnitObject) = 0;

      /** @brief 更新背包
        * @param pUnitObject 更新的物件 */
      virtual void updateBackpack(CUnitObject *pUnitObject) = 0;

      /** @brief 更新技能
        * @param pUnitObject 更新的物件 */
      virtual void updateSkill(CUnitObject *pUnitObject) = 0;

      /** @brief 更新快捷鍵項目
        * @param field       哪個欄位快捷鍵
        * @param pHotKeyItem 更新的項目 */
      virtual void updateHotKeyItem(int field, HotKeyItem *pHotKeyItem) = 0;

      /** @brief 更新技能冷卻時間
        * @param pSkill 技能 */
      virtual void updateCoolDown(CSkill *pSkill) = 0;
};

#endif  // #ifndef _IMODELEVENTLISTENER_H_