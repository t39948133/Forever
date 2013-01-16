#include "CMonster.h"
#include "AttributeSet.h"

CMonster::CMonster(int id, long long uid, char level, float dx, float dy,
        std::vector<CSkill> vSkill, std::list<AngerValue> lHatred,
        std::vector<int> vReware, long long money) :
                    CUnitObject(MONSTER_INFO::getInfo(id)->getName(), uid, level)
{
    if(create(id))
    {
        setPosition(dx, dy);
        m_vSkill = vSkill;
        m_lHatred = lHatred;
        m_vReware = vReware;
        m_Money = money;
    }
}

CMonster::~CMonster()
{
}

void CMonster::initMonster()
{
    if(MONSTER_INFO::read("monster.la"))
    {
    }
    else
    {
        BasisAttribute basAttr;
        AttributeClear(basAttr);
        CMonsterInfo* pm = new CMonsterInfo();
        pm->initMonsterInfo("¤õÀs", "¤@°¦¤õÀs", "", "", 1, 350, MONSTER_ACTIVE,
            HERO_GRADE, 100, 500, basAttr);
        addInfo(pm);
    }
}

bool CMonster::create(unsigned int id)
{
    if(false == MONSTER_INFO::checkID(id))
    {
        return false;
    }
    MONSTER_INFO::create(id);
    CMonsterInfo* pInfo = getInfo();
    if(NULL != pInfo)
    {
        m_lHatred.clear();
        m_vReware.clear();
        m_Money = 0;
        setBasAttr(pInfo->getBasAttr());
        return true;
    }
    return false;
}

void CMonster::addHate(AngerValue hate)
{
	std::list<AngerValue>::iterator pi = m_lHatred.begin();
	while(m_lHatred.end() != pi)
	{
		if(pi->uid == hate.uid)
		{
			pi->iHatred += hate.iHatred;
			break;
		}
		pi++;
	}
}

long long CMonster::getTarget()
{
	std::list<AngerValue>::iterator pi = m_lHatred.begin();
	AngerValue hate;
	hate.iHatred = 0;
	hate.uid = -1;
	while(m_lHatred.end() != pi)
	{
		if(hate.iHatred < pi->iHatred)
		{
			hate = (*pi);
		}
		pi++;
	}
	return hate.uid;
}

int CMonster::getReware()
{
	return rand() % m_vReware.size();
}

long long CMonster::getMoney()
{
    long long money = m_Money;
    money -= (int) (money * (rand() % 10) * 0.1f);
	return money;
}

unsigned int CMonster::getXP()
{
    CMonsterInfo* pInfo = MONSTER_INFO::getInfo();
    return (pInfo->getxp() * getLevel());
}

#ifdef _GAMEENGINE_2D_
void CMonster::draw(HDC hdc)
{
    
   CUnitObject::draw(hdc);

   int size = 20;
   char buf[128];
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));
}
#endif