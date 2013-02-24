#include "CPacketQuestData.h"

CPacketQuestData::CPacketQuestData() : CBasePacket(PACKET_QUEST_DATA)
{
}

void CPacketQuestData::pack(CPlayer *pPlayer, CQuest *pQuest)
{
	m_uid = pPlayer->getUID();
	m_kindID = pQuest->getID();
	m_const = pQuest->getConst();
	m_finish = pQuest->canReply();
}

void CPacketQuestData::unpack(CPlayer *pPlayer)
{
	if(m_uid != pPlayer->getUID())
		return;
	CQuest *pquest = new CQuest();
	pquest->create(m_kindID);
	pquest->m_iConst = m_const;
	pquest->m_bFinish = m_finish;
	pPlayer->getQuestMap()->addQuest(pquest);
}