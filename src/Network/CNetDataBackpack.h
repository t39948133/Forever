#ifndef _CNETDATABACKPACK_H_
#define _CNETDATABACKPACK_H_
#include "Common.h"

class CNetDataBackpack
{
   public:
      CNetDataBackpack() : m_grid(-1), m_itemID(-1), m_stack(-1) {
      }

      int m_grid;
      int m_itemID;
      int m_stack;
};

#endif  // #ifndef _CNETDATABACKPACK_H_