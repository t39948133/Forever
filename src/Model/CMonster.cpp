#include "CMonster.h"
#include "AttributeSet.h"

/*CMonster::CMonster(int kindID, long long uid, char level, float dx, float dy,
                   std::vector<CSkill *> vSkill, std::list<AngerValue> lHatred,
                   std::vector<int> vReware, long long money) :
                   CUnitObject(MONSTER_INFO::getInfo(id)->getName(), uid, level)*/
CMonster::CMonster(int kindID, long long uid, char level, float dx, float dy, long long money) :
                   CUnitObject(MONSTER_INFO::getInfo(kindID)->getName(), uid, level)
{
   if(create(kindID))
   {
     setPosition(dx, dy);
     setTargetPosition(dx, dy);
     //m_vSkill = vSkill;
     //m_lHatred = lHatred;
     //m_vReware = vReware;
     m_Money = money;
   }

   ACTION_DATA actData;
   CActionEvent actEvent;
   CAction *pAction = NULL;
   CActionEventHandler *pActionEventHandler = NULL;

   actData.iID           = 101;
   actData.name          = "等待";
   actData.fTime         = 4.33333f;
   actData.animationName = "lm_nidle_001";
   actData.iNextActID    = 0;  // 沒有下一個動作
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event      = AET_NOT_REACH;
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 102);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   //----------------------------------------------------------

   actData.iID           = 102;
   actData.name          = "跑步";
   actData.fTime         = 1.46667f;
   actData.animationName = "lm_nrun_001";
   actData.iNextActID    = 0;  // 沒有下一個動作
   actData.bMove         = true;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event    = AET_REACH;
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 101);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);
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
        BasicAttribute basAttr;
        AttributeClear(basAttr);
        basAttr.iSTR = 100;
        basAttr.iVIT = 100;
        basAttr.iINT = 0;
        basAttr.iDEX = 100;
        basAttr.iAGI = 100;
        basAttr.iWIL = 0;

        CMonsterInfo* pm = new CMonsterInfo();
        pm->initMonsterInfo("斑紋凱魯賓", "普通怪", "", "", 1, 350, MONSTER_ACTIVE,
            REGULAR_GRADE, 100, 500, basAttr);
        addInfo(pm);
    }
}

bool CMonster::create(unsigned int kindID)
{
    if(false == MONSTER_INFO::checkID(kindID))
    {
        return false;
    }
    MONSTER_INFO::create(kindID);
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

void CMonster::addHate(long long uid, int damage)
{
   int iHatred =(int) abs(damage) / 20 ;
	std::list<AngerValue>::iterator pi = m_lHatred.begin();
	while(m_lHatred.end() != pi)
	{
		if(pi->uid == uid)
		{
			pi->iHatred += iHatred;
			break;
		}
		pi++;
	}
    targetUpdate();
}

long long CMonster::getTarget()
{
	return m_Target;
}

int CMonster::getReware()
{
    int offset = (rand() % m_vReware.size());
	return m_vReware[offset];
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

void CMonster::work(float timePass)
{
    //AI
    //仇恨值表內玩家攻擊外行為造成仇恨
    CUnitObject::work(timePass);
}

void CMonster::targetUpdate()
{
   std::list<AngerValue>::iterator pi = m_lHatred.begin();
   AngerValue hate;
   AngerValue hateSec;
   hate.iHatred = -1;
   hate.uid = -1;
   hateSec.iHatred = -1;
   hateSec.uid = -1;
	while(m_lHatred.end() != pi)
	{
		if(hate.iHatred < pi->iHatred)
		{
         hateSec = hate;
         hate = (*pi);
		}
		pi++;
	}
   if((-1) == hateSec.uid)
   {
     m_Target = hate.uid;
   }
   else if(hateSec.uid == m_Target)
   {
     if(hate.iHatred > (hateSec.iHatred + 15))
     {
         m_Target = hate.uid;
     }
   }
   else if(hate.uid != m_Target)
   {
     m_Target = hate.uid;
   }
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
#endif  // #ifdef _GAMEENGINE_2D_