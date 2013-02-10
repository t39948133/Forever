#ifndef _CNETDATAEQUIP_H_
#define _CNETDATAEQUIP_H_
#include "Common.h"

class CNetDataEquip
{
   public:
      CNetDataEquip() : m_slot(SLOT_NULL), m_itemID(-1) {
      }

      EquipSlot m_slot;
      int m_itemID;
};

#endif  // #ifndef _CNETDATAEQUIP_H_