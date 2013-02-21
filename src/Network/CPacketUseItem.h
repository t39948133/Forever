/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketUseItem.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#ifndef _CPACKETUSEITEM_H_
#define _CPACKETUSEITEM_H_
#include "CBasePacket.h"
#include "CUnitObject.h"
#include "CItem.h"

class CPacketUseItem : public CBasePacket
{
   public:
      CPacketUseItem() : CBasePacket(PACKET_USE_ITEM)
      {
      }

      long long getUID();
      int getBackpackGrid();
      int getItemID();

      void pack(CUnitObject *pUnitObject, int backpackGrid, CItem *pItem);

   private:
      long long m_uid;      // 誰
      int m_backpackGrid;   // 背包哪一格的物品
      int m_itemID;         // 哪個物品
};

#endif  // #ifndef _CPACKETUSESKILL_H_