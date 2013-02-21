/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketUseItem.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#include "CPacketUseItem.h"
#include "CPlayer.h"

long long CPacketUseItem::getUID()
{
   return m_uid;
}

int CPacketUseItem::getBackpackGrid()
{
   return m_backpackGrid;
}

int CPacketUseItem::getItemID()
{
   return m_itemID;
}

void CPacketUseItem::pack(CUnitObject *pUnitObject, int backpackGrid, CItem *pItem)
{
   m_uid = pUnitObject->getUID();
   m_backpackGrid = backpackGrid;
   m_itemID = pItem->getID();
}