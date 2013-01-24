#include "CUnitObject.h"
#include "AttributeSet.h"
#include "CMonster.h"

CUnitObject::CUnitObject(std::string strName, long long uid, char level) : m_strName(strName),m_uid(uid),m_level(level)
{
   AttributeClear(m_basAttr);
	AttributeSet(m_advAttr);
   AttributeClear(m_obsAttr);
   AttributeClear(m_comAttr);
   AttributeClear(m_preAttr);

   // Add by Darren Chen on 2012/12/22 {
   m_fDirection = -3.1415926f;  // 角色方向朝上(-Z軸)
   m_position.fX = 450.0f;
   m_position.fY = 450.0f;
   m_targetPosition.fX = 450.0f;
   m_targetPosition.fY = 450.0f;

   m_bCastSkill = false;
   m_pTargetObject = NULL;
   m_iCastSkillID = 0;
   m_fCastSkillTime = 0.0f;

   m_pActionSystem = new CActionSystem(uid);

#ifdef _GAMEENGINE_2D_
   m_bFaceTarget = false;
#endif
   // } Add by Darren Chen on 2012/12/22
}

// Add by Darren Chen on 2012/12/22 {
CUnitObject::~CUnitObject()
{
   if(m_pActionSystem) {
      delete m_pActionSystem;
      m_pActionSystem = NULL;
   }

   std::vector<CSkill *>::iterator itSkill = m_vSkill.begin();
   while(itSkill != m_vSkill.end()) {
      delete (*itSkill);
      itSkill++;
   }
   m_vSkill.clear();

   m_pTargetObject = NULL;
}

bool CUnitObject::canUseSkill(unsigned int skillID)
{
   CSkill *pUseSkill = NULL;
   std::vector<CSkill *>::iterator itSkill = m_vSkill.begin();
   while(itSkill != m_vSkill.end()) {
      if((*itSkill)->getID() == skillID) {
         pUseSkill = (*itSkill);
         break;
      }

      itSkill++;
   }

   if(pUseSkill != NULL) {
      if(pUseSkill->getAvailable() == true) {  // 確定該項技能因裝備關係而可以使用
         if(pUseSkill->isReady() == true) {    // 確定該項技能的冷卻時間已經完成
            CSkillInfo *pUseSkillInfo = pUseSkill->getInfo();
            if(getMP() >= pUseSkillInfo->getCastMP()) {      // 確定角色的MP足夠使用該項技能
               if((pUseSkillInfo->getTarget() == ENEMY) ||   // 技能目標是怪物
                  (pUseSkillInfo->getTarget() == GROUND)) {  // 技能目標是範圍
                  if(m_pTargetObject != NULL) {
                     float distance = getDistance(m_position.fX, m_position.fY,
                                                  m_pTargetObject->getPosition().fX, m_pTargetObject->getPosition().fY);
                     if(distance > pUseSkillInfo->getCastRange())
                        return false;  // 離目標物距離遠過技能施展距離
                     else
                        return true;
                  }
                  else
                     return false;  // 沒有指定怪物
               }
               else if((pUseSkillInfo->getTarget() == SELF) ||  // 技能目標是自己
                       (pUseSkillInfo->getTarget() == TEAM)) {  // 技能目標是自己含隊友
                  return true;
               }
               else
                  return false;
            }
            else
               return false;
         }
         else
            return false;
      }
      else
         return false;
   }
   else
      return false;
}

void CUnitObject::startCastSkill(unsigned int skillID)
{
   CSkill *pUseSkill = NULL;
   std::vector<CSkill *>::iterator itSkill = m_vSkill.begin();
   while(itSkill != m_vSkill.end()) {
      if((*itSkill)->getID() == skillID) {
         pUseSkill = (*itSkill);
         break;
      }

      itSkill++;
   }

   if(pUseSkill != NULL) {
      CSkillInfo *pUseSkillInfo = pUseSkill->getInfo();
      if(pUseSkillInfo != NULL) {
         m_iCastSkillID = skillID;
         m_fCastSkillTime = pUseSkillInfo->getCastTime();
         m_bCastSkill = true;
      }
   }
}

void CUnitObject::useSkill(unsigned int skillID)
{
   CSkill *pUseSkill = NULL;
   std::vector<CSkill *>::iterator itSkill = m_vSkill.begin();
   while(itSkill != m_vSkill.end()) {
      if((*itSkill)->getID() == skillID) {
         pUseSkill = (*itSkill);
         break;
      }

      itSkill++;
   }

   if(pUseSkill != NULL) {
      CSkillInfo *pUseSkillInfo = pUseSkill->getInfo();
      if(pUseSkillInfo != NULL) {
         if(pUseSkillInfo->getTarget() == ENEMY) {      // 技能目標是怪物
            if(m_pTargetObject != NULL) {
               AdvancedAttribute effectAttr = pUseSkillInfo->getEffectAttr();
               AdvancedAttribute targetAttr = m_pTargetObject->getAdvAttr();
               AttributeAdd(targetAttr, effectAttr);

               FloatPrecentAttribute effectPrecentAttr = pUseSkillInfo->getEffectAttrPercent();
               AttributeMulti(targetAttr, effectPrecentAttr);
               skillDamage(targetAttr);
            }
         }
         else if(pUseSkillInfo->getTarget() == SELF) {  // 技能目標是自己
            AdvancedAttribute effectAttr = pUseSkillInfo->getEffectAttr();
            AdvancedAttribute playerAttr = getAdvAttr();
            AttributeAdd(playerAttr, effectAttr);

            FloatPrecentAttribute effectPrecentAttr = pUseSkillInfo->getEffectAttrPercent();
            AttributeMulti(playerAttr, effectPrecentAttr);

            setAdvAttr(playerAttr);

            //Todo: 技能產生Buff問題還沒處理
         }

         // 扣除MP
         addMP(-pUseSkillInfo->getCastMP());

         // 技能冷卻時間開始
         pUseSkill->startCoolDown();
      }
   }
}

void CUnitObject::skillDamage(AdvancedAttribute targetAttr)
{
    m_pTargetObject->setAdvAttr(targetAttr);
}

bool CUnitObject::isCastSkill()
{
   return m_bCastSkill;
}

void CUnitObject::work(float timePass)
{
   SkillCoolDown(timePass);
   m_pActionSystem->work(timePass);

#ifdef _GAMEENGINE_2D_
   if(m_pActionSystem->isMove() == true)
      move(timePass, m_targetPosition.fX, m_targetPosition.fY, m_bFaceTarget);
#endif  // #ifdef _GAMEENGINE_2D_

   if(m_bCastSkill == true) {
      CAction *pAction = m_pActionSystem->getCurAction();
      if(pAction->getID() == 1) { // 等待
         CActionEvent actEvent;
         actEvent.m_event = AET_CAST_SKILL;
         actEvent.m_bCastSkill = true;
         actEvent.m_iCastSkillID = m_iCastSkillID;
         actEvent.m_fCastSkillTime = m_fCastSkillTime;
         CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);
      }
      else if(pAction->getID() == 2) {  // 跑步
         CActionEvent actEvent;
         actEvent.m_event = AET_REACH;
         CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);
      }
      else if(pAction->getID() == 4) {  // 戰鬥姿勢
         CActionEvent actEvent;
         actEvent.m_event = AET_CAST_SKILL;
         actEvent.m_bCastSkill = true;
         actEvent.m_iCastSkillID = m_iCastSkillID;
         actEvent.m_fCastSkillTime = m_fCastSkillTime;
         CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);

         useSkill(m_iCastSkillID);

         m_bCastSkill = false;
         m_iCastSkillID = 0;
         m_fCastSkillTime = 0.0f;
      }
   }
}

void CUnitObject::addDirection(float offsetDirection)
{
   m_fDirection += offsetDirection;
}

void CUnitObject::setDirection(float direction)
{
   m_fDirection = direction;
}

float CUnitObject::getDirection()
{
   return m_fDirection;
}

void CUnitObject::setPosition(float x, float y)
{
   m_position.fX = x;
   m_position.fY = y;
}

const FPOS& CUnitObject::getPosition()
{
   return m_position;
}

void CUnitObject::setTargetPosition(float x, float y)
{
   m_targetPosition.fX = x;
   m_targetPosition.fY = y;
}

#ifdef _GAMEENGINE_2D_
void CUnitObject::setTargetPosition(float x, float y, bool bFaceTarget)
{
   m_bFaceTarget = bFaceTarget;
   m_targetPosition.fX = x;
   m_targetPosition.fY = y;
}
#endif

const FPOS& CUnitObject::getTargetPosition()
{
   return m_targetPosition;
}

bool CUnitObject::isReachTarget()
{
#ifdef _GAMEENGINE_2D_
   return (m_position.fX == m_targetPosition.fX) && (m_position.fY == m_targetPosition.fY);
#elif _GAMEENGINE_3D_
   if((m_position.fX >= m_targetPosition.fX - 0.1f) && (m_position.fX <= m_targetPosition.fX + 0.1f) &&
      (m_position.fY >= m_targetPosition.fY - 0.1f) && (m_position.fY <= m_targetPosition.fY + 0.1f))
      return true;
   else
      return false;
#endif  // #ifdef _GAMEENGINE_2D_ && #elif _GAMEENGINE_3D_
}

bool CUnitObject::isChangeAction()
{
   return m_pActionSystem->isChangeAction();
}

CAction* CUnitObject::getCurAction()
{
   return m_pActionSystem->getCurAction();
}

bool CUnitObject::isMove()
{
   if(m_pActionSystem->isMove() == true) {
      if(isReachTarget() == false)
         return true;
      else
         return false;
   }
   else
      return false;
}

void CUnitObject::setTargetObject(CUnitObject *pUnitObject)
{
   m_pTargetObject = pUnitObject;
}

CUnitObject* CUnitObject::getTargetObject()
{
   return m_pTargetObject;
}

void CUnitObject::addAdvAttrEventListener(IAdvAttrEventListener *pListener)
{
   std::set<IAdvAttrEventListener *>::iterator it = m_advAttrEventListeners.find(pListener);
   if(it == m_advAttrEventListeners.end())
      m_advAttrEventListeners.insert(pListener);
}

void CUnitObject::removeAdvAttrEventListener(IAdvAttrEventListener *pListener)
{
   std::set<IAdvAttrEventListener *>::iterator it = m_advAttrEventListeners.find(pListener);
   if(it != m_advAttrEventListeners.end())
      m_advAttrEventListeners.erase(it);
}

void CUnitObject::addSkillEventListener(ISkillEventListener *pListener)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.find(pListener);
   if(it == m_skillEventListeners.end())
      m_skillEventListeners.insert(pListener);
}

void CUnitObject::removeSkillEventListener(ISkillEventListener *pListener)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.find(pListener);
   if(it != m_skillEventListeners.end())
      m_skillEventListeners.erase(it);
}

#ifdef _GAMEENGINE_2D_
bool CUnitObject::isClick(float x, float y)
{
   int size = 20;
   float L = getDistance(m_position.fX, m_position.fY, x, y);
	return L <= size;
}

void CUnitObject::draw(HDC hdc)
{
   int size = 20;
   Ellipse(hdc, (int)m_position.fX - size, (int)m_position.fY - size, (int)m_position.fX + size, (int)m_position.fY + size);

   // 畫方向線
   MoveToEx(hdc, (int)m_position.fX, (int)m_position.fY, NULL);
   float tx = m_position.fX + size * sin(m_fDirection);
	float ty = m_position.fY + size * cos(m_fDirection);
   LineTo(hdc, (int)tx, (int)ty);

   // 畫動作系統
   m_pActionSystem->draw(hdc, (int)m_position.fX - size, (int)m_position.fY + size + 22);
}
#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2012/12/22

long long CUnitObject::getUID()
{
	return m_uid;
}

std::string CUnitObject::getName()
{
	return m_strName;
}

char CUnitObject::getLevel()
{
	return m_level;
}

void CUnitObject::addHP(int hp)
{
	m_advAttr.iHP += hp;
	if(m_advAttr.iHP < 0 || m_advAttr.iHP == 0)	//沒血了 死亡
	{
		m_advAttr.iHP = 0;
		//死亡程式
	}
	else if(m_advAttr.iHP > getHPMax())	//補血超過最大血量 保持最大血量
	{
		m_advAttr.iHP = getHPMax();
	}

   notifyAdvAttrUpdate();
}

int CUnitObject::getHP()
{
	return m_advAttr.iHP;
}

int CUnitObject::getHPMax()
{
    int hpMax = m_advAttr.iHPMax;

    hpMax += m_comAttr.AdvAttr.iHPMax;
    if(0.0f > m_preAttr.fHPMax)
    {
        hpMax =(int) (hpMax * m_preAttr.fHPMax);
    }

	return hpMax;
}

void CUnitObject::addMP(int mp)
{
	m_advAttr.iMP += mp;
	if(m_advAttr.iMP < 0 || m_advAttr.iMP == 0)	//沒魔力了
	{
		m_advAttr.iMP = 0;
	}
	else if(m_advAttr.iMP > getMPMax())	//魔力超過最大魔力 保持最大魔力
	{
		m_advAttr.iMP = getMPMax();
	}

   notifyAdvAttrUpdate();
}

int CUnitObject::getMP()
{
	return m_advAttr.iMP;
}

int CUnitObject::getMPMax()
{
    int mpMax = m_advAttr.iMPMax;

    mpMax += m_comAttr.AdvAttr.iMPMax;

    if(0.0f > m_preAttr.fMPMax)
    {
        mpMax = (int) (mpMax * m_preAttr.fMPMax);
}
  
	return mpMax;
}

int CUnitObject::getHPR()
{
   int hpr = m_obsAttr.iHPR;

   hpr += m_comAttr.ObsAttr.iHPR;

   if(0.0f > m_preAttr.fHPR)
   {
      hpr = (int) (hpr * m_preAttr.fHPR);
   }

   return hpr;
}

int CUnitObject::getMPR()
{
   int mpr = m_obsAttr.iMPR;

   mpr += m_comAttr.ObsAttr.iMPR;

   if(0.0f > m_preAttr.fMPR)
   {
      mpr = (int) (mpr * m_preAttr.fMPR);
   }

   return mpr;
}
  
void CUnitObject::setBasAttr(BasicAttribute basAttr)
{
    m_basAttr = basAttr;
    BasicAttributeSet(m_level, basAttr, m_advAttr, m_obsAttr);
}
  
void CUnitObject::setAdvAttr(AdvancedAttribute advattr)
{
   m_advAttr = advattr;	//設定屬性資料

   if(getHPMax() < m_advAttr.iHP)
      m_advAttr.iHP = getHPMax();
   else if(m_advAttr.iHP < 0)
      m_advAttr.iHP = 0;
   
   if(getMPMax() < m_advAttr.iMP)
      m_advAttr.iMP = getMPMax();
   else if(m_advAttr.iMP < 0)
      m_advAttr.iMP = 0;

   notifyAdvAttrUpdate();
}

AdvancedAttribute CUnitObject::getAdvAttr()
{
   AdvancedAttribute attr = m_advAttr;

   AttributeAdd(attr, m_comAttr.AdvAttr);
   AttributeMulti(attr, m_preAttr);

   return attr;
}

BasicAttribute CUnitObject::getBasAttr()
{
	return m_basAttr;
}

std::list<CBuff> CUnitObject::getBuff()
{
   return m_lBuff;
}

void CUnitObject::updateBuff(float timepass)
{
    std::list<CBuff>::iterator pi = m_lBuff.begin();

   while(m_lBuff.end() != pi)
   {
      if(pi->afterTime(timepass))
      {
         pi = m_lBuff.erase(pi);
      }
      else
      {
         pi++;
      }
   }

   pi = m_lBuff.begin();
	CBuffInfo* pBuff;

   while(m_lBuff.end() != pi)
   {
      pBuff = pi->getInfo();
      AttributeAdd(m_comAttr, pBuff->getAttr());
      AttributeMulti(m_preAttr, pBuff->getPercentAttr());
      pi++;
   }
}

void CUnitObject::addBuff(unsigned int id)
{
    CBuff bt;
   bt.create(id);
   m_lBuff.push_back(bt);
   updateBuff(0.0f);
}

std::vector<CSkill *> CUnitObject::getSkill()
{
   return m_vSkill;
}

void CUnitObject::SkillCoolDown(float timepass)
{
   std::vector<CSkill *>::iterator pi = m_vSkill.begin();
   while(m_vSkill.end() != pi)
   {
      (*pi)->updateCoolDown(timepass);
      pi++;
   }
}

bool CUnitObject::addSkill(unsigned int skillID)
{
   CSkill *pSkill = new CSkill();
   pSkill->create(skillID);
   if(pSkill->canLearn(m_level))
   {
      m_vSkill.push_back(pSkill);
      notifySkillUpdate();
      return true;
   }
   return false;
}

// Add by Darren Chen on 2013/01/01 {
void CUnitObject::notifyAdvAttrUpdate()
{
   std::set<IAdvAttrEventListener *>::iterator it = m_advAttrEventListeners.begin();
   while(it != m_advAttrEventListeners.end()) {
      (*it)->updateAdvAttr(this);
      it++;
   }
}

void CUnitObject::notifySkillUpdate()
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.begin();
   while(it != m_skillEventListeners.end()) {
      (*it)->updateSkill(this);
      it++;
   }
}

#ifdef _GAMEENGINE_2D_
void CUnitObject::move(float timePass, float targetX, float targetY, bool bFaceTarget)
{
   movePoint(m_position.fX, m_position.fY, targetX, targetY, m_advAttr.fMove * timePass);

   if(bFaceTarget == true) {
      if((m_position.fX != targetX) && (m_position.fY != targetY)) {
         float dx = targetX - m_position.fX;
		   float dy = targetY - m_position.fY;

         if(dy != 0)
		      m_fDirection = atan(dx / dy);

         if(dy < 0)
            m_fDirection -= 3.1415926f;
      }
   }
}
#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2013/01/01