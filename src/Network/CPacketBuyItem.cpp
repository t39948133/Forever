/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketUseItem.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#include "CPacketBuyItem.h"
#include "CPlayer.h"

long long CPacketBuyItem::getUID()
{
   return m_uid;
}
/*
int CPacketBuyItem::getBackpackGrid()
{
   return m_backpackGrid;
}
*/
int CPacketBuyItem::getItemID()
{
   return m_itemID;
}

void CPacketBuyItem::pack(CUnitObject *pUnitObject, int buyItem)
{
   m_uid = pUnitObject->getUID();
//   m_backpackGrid = backpackGrid;
   m_itemID = buyItem;
}