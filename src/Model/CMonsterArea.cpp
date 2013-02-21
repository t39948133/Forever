#include "CMonsterArea.h"
#include "CScene.h"
#include "CGameServer.h"

void CMonsterArea::initMonsterArea()
{
	if(MONSTERAREA_INFO::read("../monsterArea.fla"))
	{
	}
	else
	{
      // 普通怪
		CMonsterAreaInfo *pInfo = new CMonsterAreaInfo();
		std::vector<int> viMonsterID;
		viMonsterID.push_back(0);
		pInfo->initMonsterAreaInfo(3, 300.0f, 300.0f, 50.0f, 1000, viMonsterID);
		MONSTERAREA_INFO::addInfo(pInfo);

      // 菁英怪
      pInfo = new CMonsterAreaInfo();
      std::vector<int> viMonsterID1;
		viMonsterID1.push_back(1);
		pInfo->initMonsterAreaInfo(3, 500.0f, 300.0f, 50.0f, 10000, viMonsterID1);
		MONSTERAREA_INFO::addInfo(pInfo);

      // 王怪
      pInfo = new CMonsterAreaInfo();
      std::vector<int> viMonsterID2;
		viMonsterID2.push_back(2);
		pInfo->initMonsterAreaInfo(1, 400.0f, 700.0f, 50.0f, 20000, viMonsterID2);
		MONSTERAREA_INFO::addInfo(pInfo);
	}
}

void CMonsterArea::create(int areaID)
{
	MONSTERAREA_INFO::create(areaID);
	m_iConstTime = GetTickCount() + MONSTERAREA_INFO::getInfo()->getAddTime();
}

int CMonsterArea::getMonsterCount()
{
	return m_iMonsterCount;
}

int CMonsterArea::getConstTime()
{
	return m_iConstTime;
}

bool CMonsterArea::isClick(float fx, float fy)
{
	CMonsterAreaInfo* pInfo = MONSTERAREA_INFO::getInfo();
	FPOS position = pInfo->getPosition();
	float dis = getDistance(position.fX, position.fY, fx, fy);
	return dis < pInfo->getBornSize();
}

CMonsterArea::CMonsterArea():m_iConstTime(0), m_iMonsterCount(0)
{
	srand((unsigned) time(NULL));
}

CMonsterArea::~CMonsterArea()
{
}

void CMonsterArea::work(CGameServer *pGameServer, CScene *pScene)
{
	if(MONSTERAREA_INFO::getInfo() == NULL)
		return;

	if(m_iMonsterCount >= MONSTERAREA_INFO::getInfo()->getMaxMonster())
		return;

   // 檢查怪物是否死亡
   std::vector<long long>::iterator it = m_vMonsterUID.begin();
   while(it != m_vMonsterUID.end()) {
      CMonster *pMonster = pScene->getMonster((*it));
      if(pMonster == NULL)
         --m_iMonsterCount;

      ++it;
   }

	if((unsigned) m_iConstTime < GetTickCount()) {
		CMonsterAreaInfo* pInfo = MONSTERAREA_INFO::getInfo();
		int mid = pInfo->getBornMonsterID()[rand() % pInfo->getBornMonsterID().size()];
		float fx = pInfo->getPosition().fX + (rand() % ((int) (pInfo->getBornSize()) * 2)) - pInfo->getBornSize();
		float fy = pInfo->getPosition().fY + (rand() % ((int) (pInfo->getBornSize()) * 2)) - pInfo->getBornSize();
		CMonster *pMonster = pScene->addMonster(pGameServer->generateUID(), mid, fx, fy);
      pMonster->addMonsterAIEventListener(pGameServer);
      m_vMonsterUID.push_back(pMonster->getUID());
		++m_iMonsterCount;
		m_iConstTime = GetTickCount() + pInfo->getAddTime();
	}
}

#ifdef _GAMEENGINE_2D_
void CMonsterArea::draw(HDC hdc)
{
	float fx = MONSTERAREA_INFO::getInfo()->getPosition().fX;
	float fy = MONSTERAREA_INFO::getInfo()->getPosition().fY;
	float size = MONSTERAREA_INFO::getInfo()->getBornSize();
	Ellipse(hdc ,(int) (fx - size), (int) (fy - size), (int) (fx + size), (int) (fy + size));
}
#endif