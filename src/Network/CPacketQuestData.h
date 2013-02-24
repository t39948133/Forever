#ifndef _CPACKETQUESTDATA_H_
#define _CPACKETQUESTDATA_H_

#include "CBasePacket.h"
#include "CPlayer.h"

class CPacketQuestData : public CBasePacket
{
public:
	CPacketQuestData();
	void pack(CPlayer *pPlayer, CQuest *pQuest);
	void unpack(CPlayer *pPlayer);
private:
	long long m_uid;
	int m_kindID;
	int m_const;
	bool m_finish;
};

#endif //#ifndef _CPACKETQUESTDATA_H_