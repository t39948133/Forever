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
		CMonsterAreaInfo* pInfo = new CMonsterAreaInfo();
		std::vector<int> viMonsterID;
		viMonsterID.push_back(0);
		pInfo->initMonsterAreaInfo(5, 400.0f, 400.0f, 50.0f, 1000, viMonsterID);
		MONSTERAREA_INFO::addInfo(pInfo);
	}
}

void CMonsterArea::create(int id)
{
	MONSTERAREA_INFO::create(id);
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

void CMonsterArea::work(CGameServer& gameServer, CScene& scene)
{
	if(NULL == MONSTERAREA_INFO::getInfo())
	{
		return;
	}
	if(MONSTERAREA_INFO::getInfo()->getMaxMonster() <= m_iMonsterCount)
	{
		return;
	}
	if(GetTickCount() > (unsigned) m_iConstTime)
	{
		CMonsterAreaInfo* pInfo = MONSTERAREA_INFO::getInfo();
		int mid = pInfo->getBornMonsterID()[rand() % pInfo->getBornMonsterID().size()];
		float fx = pInfo->getPosition().fX + (rand() % ((int) (pInfo->getBornSize()) * 2))
			- pInfo->getBornSize();
		float fy = pInfo->getPosition().fY + (rand() % ((int) (pInfo->getBornSize()) * 2))
			- pInfo->getBornSize();
		scene.addMonster(gameServer.generateUID(), mid, fx, fy);
		m_iMonsterCount++;
		m_iConstTime = GetTickCount() + pInfo->getAddTime();
	}
}

void CMonsterArea::draw(HDC hdc)
{
	float fx = MONSTERAREA_INFO::getInfo()->getPosition().fX;
	float fy = MONSTERAREA_INFO::getInfo()->getPosition().fY;
	float size = MONSTERAREA_INFO::getInfo()->getBornSize();
	Ellipse(hdc ,(int) (fx - size), (int) (fy - size), (int) (fx + size), (int) (fy + size));
}