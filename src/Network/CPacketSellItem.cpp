/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketSellItem.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#include "CPacketSellItem.h"
#include "CPlayer.h"

long long CPacketSellItem::getUID()
{
   return m_uid;
}

int CPacketSellItem::getBackpackGrid()
{
   return m_backpackGrid;
}

int CPacketSellItem::getItemID()
{
   return m_itemID;
}

void CPacketSellItem::pack(CUnitObject *pUnitObject, int backpackGrid, CItem *pItem)
{
   m_uid = pUnitObject->getUID();
   m_backpackGrid = backpackGrid;
   m_itemID = pItem->getID();
}