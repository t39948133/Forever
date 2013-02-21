#ifndef _CPACKETNPCDATA_H_
#define _CPACKETNPCDATA_H_

#include "CBasePacket.h"
#include "CNPC.h"

#ifdef _GAMEENGINE_3D_
#include "CNPC3D.h"
#endif

class CPacketNPCData : public CBasePacket
{
public:
	CPacketNPCData();

	long long getUID();
   int getKindID();

   void pack(CNPC *pNPC);
   void unpack(CNPC *pNPC);
#ifdef _GAMEENGINE_3D_
   void unpack(CNPC3D *pNPC);
#endif
private:
	long long             m_uid;             //唯一編號
   int                   m_kindID;          //npc種類id
   FPOS                  m_position;        //角色X,Y座標 (2D)
   float                 m_fDirection;      //角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下
};

#endif