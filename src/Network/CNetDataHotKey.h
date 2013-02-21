#ifndef _CNETDATAHOTKEY_H_
#define _CNETDATAHOTKEY_H_
#include "Common.h"

class CNetDataHotKey
{
   public:
      CNetDataHotKey() : m_field(-1), m_itemID(-1), m_backpackGrid(-1), m_skillID(-1) {
      }

      int m_field;
      int m_itemID;
      int m_backpackGrid;
      int m_skillID;
};

#endif  // #ifndef _CNETDATAHOTKEY_H_