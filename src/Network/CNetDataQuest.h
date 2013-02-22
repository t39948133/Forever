#ifndef _CNETDATAQUEST_H_
#define _CNETDATAQUEST_H_

#include "CQuest.h"

class CNetDataQuest
{
public:
	CNetDataQuest() : m_kindID(-1), m_const(-1), m_finish(false){
	}
	int m_kindID;
	int m_const;
	bool m_finish;
};

#endif //#ifndef _CNETDATAQUEST_H_