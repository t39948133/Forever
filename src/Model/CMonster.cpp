#include "CMonster.h"
#include "AttributeSet.h"
#include "CSkill.h"
#include "CScene.h"

CMonster::CMonster(std::string machineName, int kindID, long long uid, float fx, float fy) : CUnitObject(machineName, 
                                                                                                         MONSTER_INFO::getInfo(kindID)->getName(), uid, 
                                                                                                         MONSTER_INFO::getInfo(kindID)->getLevel()),
                                                                                             m_state(ESTABLISH)
{
   if(create(kindID))
   {
      setPosition(fx, fy);
      setTargetPosition(fx, fy);
      m_state = IDLE;
		m_bornPosition.fX = fx;
		m_bornPosition.fY = fy;
      m_anchorPosition.fX = 0.0f;
      m_anchorPosition.fY = 0.0f;

      //srand((unsigned int)time(NULL));

      // 讀取動作檔
      std::string actionFile = MONSTER_INFO::getInfo(kindID)->getActionSystemFile();
      if(m_actionSystem.read("../" + actionFile) == false)
         m_actionSystem.read(actionFile);
   }
}

CMonster::~CMonster()
{
}

void CMonster::initMonster()
{
   //if(MONSTER_INFO::read("../Monster.fla") == false)
   //   MONSTER_INFO::read("Monster.fla");

   if(MONSTER_INFO::read("Monster.fla"))
   {
   }
   else
   {
      AdvancedAttribute advAttr;
      AttributeSet(advAttr);
      advAttr.iATK = 50;
      advAttr.iHP = 300;
      advAttr.iHPMax = advAttr.iHP;
      advAttr.iDEF = 70;

      CMonsterInfo* pm = new CMonsterInfo();
      std::vector<int> reware;
      reware.push_back(12);
      reware.push_back(13);
      reware.push_back(14);
      reware.push_back(15);
      reware.push_back(16);
      reware.push_back(29);
      reware.push_back(34);

      std::vector<int> skill;
      skill.push_back(11);
      pm->initMonsterInfo("圖爾辛暴徒", "普通怪", "KrallWarriorMT.mesh", "KrallWarriorMT.acs", 1, 1, 350, MONSTER_ACTIVE,
                          REGULAR_GRADE, 50, 100, advAttr, 100, reware, skill);
      addInfo(pm);

      //-------------------------------------------------------------------------------

      pm = new CMonsterInfo();
      std::vector<int> reware1;
      reware1.push_back(17);
      reware1.push_back(18);
      reware1.push_back(19);
      reware1.push_back(20);
      reware1.push_back(21);
      reware1.push_back(30);
      reware1.push_back(35);

      std::vector<int> skill1;
      skill1.push_back(12);
      skill1.push_back(13);
      pm->initMonsterInfo("偵察隊長塔卡塔", "菁英怪", "KrallScoutMT.mesh", "KrallScoutMT.acs", 1, 2, 50000, MONSTER_ACTIVE,
                          ELITE_GRADE, 50, 100, advAttr, 50000, reware1, skill1);
      addInfo(pm);

      //-------------------------------------------------------------------------------

      pm = new CMonsterInfo();
      std::vector<int> reware2;
      reware2.push_back(22);
      reware2.push_back(23);
      reware2.push_back(24);
      reware2.push_back(25);
      reware2.push_back(26);
      reware2.push_back(31);
      reware2.push_back(36);

      std::vector<int> skill2;
      skill2.push_back(14);
      skill2.push_back(15);
      skill2.push_back(16);
      pm->initMonsterInfo("大族長山杜卡", "王怪", "OrcShandura.mesh", "OrcShandura.acs", 1, 3, 500000, MONSTER_ACTIVE,
                          HERO_GRADE, 100, 200, advAttr, 500000, reware2, skill2);
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
      setAdvAttr(pInfo->getAdvAttr());

      std::vector<int> vSkill = pInfo->getSkill();
      std::vector<int>::iterator itSkillID = vSkill.begin();
      while(itSkillID != vSkill.end()) {
         this->addSkill((*itSkillID));
         itSkillID++;
      }

      return true;
   }
   return false;
}

void CMonster::addHate(long long uid, int damage)
{
   if(RETURN == m_state)//回歸途中不計算仇恨值
   {
      return;
   }

   if(IDLE == m_state)//idle狀態 被攻擊切換取得目標
   {
      m_state = GOALS;
      m_anchorPosition.fX = getPosition().fX;
      m_anchorPosition.fY = getPosition().fY;
   }

   int iHatred =(int) abs(damage) / 20 ;
   if(0 == m_lHatred.size())
   {
      AngerValue anger;
      anger.uid = uid;
      anger.iHatred = iHatred;
      m_lHatred.push_back(anger);
      return;
   }

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
}

int CMonster::getReware()
{
    std::vector<int> reware = MONSTER_INFO::getInfo()->getReware();
    int offset = (rand() % reware.size());
	return reware[offset];
}

long long CMonster::getMoney()
{
    long long money = MONSTER_INFO::getInfo()->getMoney();
    money -= (int) (money * (rand() % 10) * 0.1f);
	return money;
}

unsigned int CMonster::getXP()
{
   CMonsterInfo* pInfo = MONSTER_INFO::getInfo();
    return pInfo->getxp();
}

void CMonster::work(float timePass)
{
   size_t idx = this->getMachineName().find("Server");
   if(idx != std::string::npos) {
      // 依據仇恨表更新鎖定的玩家
      long long newTargetObjectUID = updateTargetObjectUID();
      std::set<IMonsterAIEventListener *>::iterator it = m_monsterAIListeners.begin();
      while(it != m_monsterAIListeners.end()) {
         (*it)->updateMonsterTargetObject(this, newTargetObjectUID);
         it++;
      }
   }

   CUnitObject::work(timePass);

   if(idx != std::string::npos) {
      // 執行怪物AI運算
      std::set<IMonsterAIEventListener *>::iterator it = m_monsterAIListeners.begin();
      while(it != m_monsterAIListeners.end()) {
         (*it)->updateMonsterAI(this);
         it++;
      }
   }
}

bool CMonster::isDead()
{
	return 0 >= getAdvAttr().iHP;
}

void CMonster::setState(MonsterState state)
{
   m_state = state;
}

MonsterState CMonster::getState()
{
   return m_state;
}

FPOS CMonster::getBornPosition()
{
   return m_bornPosition;
}

FPOS CMonster::getAnchorPosition()
{
   return m_anchorPosition;
}

bool CMonster::isMonsterTargetTooFarAway()
{
   if(m_lHatred.size() == 0)
      return false;

   CMonsterInfo* pMonsterInfo = MONSTER_INFO::getInfo();
   if(pMonsterInfo == NULL)
      return false;

   float range = pMonsterInfo->getRegress() * 0.6f;
   float fx = getTargetPosition().fX;
   float fy = getTargetPosition().fY;
   float fbx = m_anchorPosition.fX;
   float fby = m_anchorPosition.fY;
   float distance = getDistance(fbx, fby, fx, fy);
   if(distance > range) {
        //預備做   轉換追擊在範圍內的仇恨玩家
      m_state = RETURN;
      m_lHatred.clear();
      return true;
   }

   return false;
}

void CMonster::addMonsterAIEventListener(IMonsterAIEventListener *pListener)
{
   std::set<IMonsterAIEventListener *>::iterator it = m_monsterAIListeners.find(pListener);
   if(it == m_monsterAIListeners.end())
      m_monsterAIListeners.insert(pListener);
}

void CMonster::removeMonsterAIEventListener(IMonsterAIEventListener *pListener)
{
   std::set<IMonsterAIEventListener *>::iterator it = m_monsterAIListeners.find(pListener);
   if(it != m_monsterAIListeners.end())
      m_monsterAIListeners.erase(it);
}

long long CMonster::updateTargetObjectUID()
{
   if(m_lHatred.size() == 0) 
      return -1;

   AngerValue hate;    // 最高仇恨值
   AngerValue hateSec; // 第二高仇恨值
   hate.iHatred = -1;
   hate.uid = -1;
   hateSec.iHatred = -1;
   hateSec.uid = -1;

   // 由仇恨表中取得最高仇恨與第二仇恨
   std::list<AngerValue>::iterator pi = m_lHatred.begin();
	while(pi != m_lHatred.end()) {
		if(pi->iHatred > hate.iHatred) {
         hateSec = hate;
         hate = (*pi);
		}
		pi++;
	}

   if(hateSec.uid == -1)
      return hate.uid;
   else if(this->getTargetObject()->getUID() == hateSec.uid)
   {
      int compare = hateSec.iHatred + ((int) (hateSec.iHatred * 0.05f));
      if(hate.iHatred > compare)//用%數比較不會跳
         return hate.uid;
      else
         return hateSec.uid;
   }
   else if(this->getTargetObject()->getUID() != hate.uid)
      return hate.uid;

   return hate.uid;
}

#ifdef _GAMEENGINE_2D_
void CMonster::draw(HDC hdc)
{
   CUnitObject::draw(hdc);

   int size = 20;
   char buf[128];
   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));

   if(this->getTargetObject() != NULL) {
      memset(buf, 0, sizeof(buf));
      sprintf_s(buf, sizeof(buf), "發現目標:%s", this->getTargetObject()->getName().c_str());
      TextOut(hdc, (int)getPosition().fX + size + 5, (int)getPosition().fY, buf, strlen(buf));
   }

   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "目標位置: x = %.0f, y = %.0f", this->getTargetPosition().fX, this->getTargetPosition().fY);
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY - size * 2, buf, strlen(buf));
}
#endif  // #ifdef _GAMEENGINE_2D_