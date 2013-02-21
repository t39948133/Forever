#include "CPacketNPCData.h"

CPacketNPCData::CPacketNPCData() : CBasePacket(PACKET_NPC_DATA)
{
}

long long CPacketNPCData::getUID()
{
	return m_uid;
}

int CPacketNPCData::getKindID()
{
	return m_kindID;
}

void CPacketNPCData::pack(CNPC *pNPC)
{
	m_uid = pNPC->getUID();
	m_kindID = pNPC->getID();
	m_position = pNPC->getPosition();
	m_fDirection = pNPC->getDirection();
}

void CPacketNPCData::unpack(CNPC *pNPC)
{
	pNPC->setUID(m_uid);
	pNPC->setPosition(m_position.fX, m_position.fY);
	pNPC->setDirection(m_fDirection);
}

#ifdef _GAMEENGINE_3D_
void CPacketNPCData::unpack(CNPC3D *pNPC)
{
   this->unpack(pNPC->getNPC2D());
}
#endif