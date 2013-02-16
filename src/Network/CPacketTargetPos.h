#ifndef _CPACKETTARGETPOS_H_
#define _CPACKETTARGETPOS_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#include "CMonster3D.h"
#endif

class CPacketTargetPos : public CBasePacket
{
   public:
      CPacketTargetPos() : CBasePacket(PACKET_TARGET_POS)
      {
      }

      long long getUID();

#ifdef _GAMEENGINE_3D_
      void pack(CUnitObject *pUnitObject);
#elif _GAMEENGINE_2D_
      void pack(CUnitObject *pUnitObject, bool bFaceTarget);
#endif
      
      void unpack(CUnitObject *pUnitObject);
#ifdef _GAMEENGINE_3D_
      void unpack(CPlayer3D *pPlayer);
      void unpack(CMonster3D *pMonster);
#endif

   private:
      long long m_uid;
      FPOS      m_targetPosition; //目標點X,Y座標 (2D)
      
#ifdef _GAMEENGINE_2D_
      bool      m_bFaceTarget;
#endif
};

#endif  // #ifndef _CPACKETTARGETPOS_H_