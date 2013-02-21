#include "CUnitObject.h"
#include "AttributeSet.h"
#include "CMonster.h"

#ifdef _GAMESOUND_
#include "CSoundManager.h"
#endif  // #ifdef _GAMESOUND_

CUnitObject::CUnitObject(std::string machineName, std::string strName, long long uid, char level) : m_machineName(machineName),
                                                                                                    m_strName(strName),
                                                                                                    m_uid(uid),
                                                                                                    m_level(level)
{
   memset(&m_basAttr, 0, sizeof(m_basAttr));
	AttributeSet(m_advAttr);
   AttributeClear(m_obsAttr);
   AttributeClear(m_comAttr);
   AttributeClear(m_preAttr);

   // Add by Darren Chen on 2012/12/22 {
   m_fDirection = -3.1415926f;  // 角色方向朝上(-Z軸)
   m_position.fX = 0.0f;
   m_position.fY = 0.0f;
   m_targetPosition.fX = 0.0f;
   m_targetPosition.fY = 0.0f;

   m_pTargetObject = NULL;
   m_bKeyMoveEnabled = false;
   m_castSkillID = -1;

   m_actionSystem.init(m_machineName, m_uid);
   m_actionSystem.addPlaySoundNotifyListener(this);
   m_actionSystem.addAttackNotifyListener(this);  // 有攻擊扣血時，請告知

   m_fightSystem.init(m_machineName, m_uid);

#ifdef _GAMEENGINE_2D_
   m_bFaceTarget = false;
#endif
   // } Add by Darren Chen on 2012/12/22
}

// Add by Darren Chen on 2012/12/22 {
CUnitObject::~CUnitObject()
{
   m_actionSystem.removePlaySoundNotifyListener(this);
   m_actionSystem.removeAttackNotifyListener(this);

   std::vector<CSkill *>::iterator itSkill = m_vSkill.begin();
   while(itSkill != m_vSkill.end()) {
      delete (*itSkill);
      ++itSkill;
   }
   m_vSkill.clear();

   m_pTargetObject = NULL;
}

bool CUnitObject::canUseSkill(int skillID)
{
   CSkill *pUseSkill = getSkill(skillID);

   if(pUseSkill != NULL) {
      if(pUseSkill->getAvailable() == true) {  // 確定該項技能因裝備關係而可以使用
         if(pUseSkill->isReady() == true) {    // 確定該項技能的冷卻時間已經完成
            CSkillInfo *pUseSkillInfo = pUseSkill->getInfo();
            if(getMP() >= pUseSkillInfo->getCastMP()) {      // 確定角色的MP足夠使用該項技能
               if((pUseSkillInfo->getTarget() == ENEMY) ||   // 技能目標是怪物
                  (pUseSkillInfo->getTarget() == GROUND)) {  // 技能目標是範圍
                  if(m_pTargetObject != NULL) {
                     if(m_pTargetObject == this)
                        return false;   // 目標是自己

                     /*float distance = getDistance(m_position.fX, m_position.fY,
                                                  m_pTargetObject->getPosition().fX, m_pTargetObject->getPosition().fY);
                     if(distance > pUseSkillInfo->getCastRange() + 100)
                        return false;  // 離目標物距離遠過技能施展距離
                     else*/
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

void CUnitObject::startCastSkill(int skillID)
{
   CSkill *pUseSkill = getSkill(skillID);

   if(pUseSkill != NULL) {
      CSkillInfo *pUseSkillInfo = pUseSkill->getInfo();
      if(pUseSkillInfo != NULL) {
         m_fightSystem.useSkill(pUseSkill);
         m_castSkillID = skillID;
      }
   }
}

void CUnitObject::useSkill(int skillID)
{
   CSkill *pUseSkill = getSkill(skillID);

   if(pUseSkill != NULL) {
      CSkillInfo *pUseSkillInfo = pUseSkill->getInfo();
      if(pUseSkillInfo != NULL) {
         if(pUseSkillInfo->getTarget() == ENEMY) {      // 技能目標是怪物
            if(m_pTargetObject != NULL) {
               AdvancedAttribute effectAttr = pUseSkillInfo->getEffectAttr();
               AdvancedAttribute targetAttr = m_pTargetObject->getAdvAttr();
               
               //雙方攻擊防禦額外計算
               int targetDEF = targetAttr.iDEF;
               int basicDamage;
               basicDamage = getAdvAttr().iATK - targetDEF;
               if(basicDamage > 0)
                  effectAttr.iHP -= basicDamage;
               else
                  effectAttr.iHP -= 1;

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
   return m_fightSystem.isCastSkill();
}

void CUnitObject::cancelCastSkill()
{
   m_fightSystem.useSkill(NULL);
}

void CUnitObject::work(float timePass)
{
   SkillCoolDown(timePass);
   m_actionSystem.work(timePass);
   m_fightSystem.work(timePass, this, m_pTargetObject);

#ifdef _GAMEENGINE_3D_
   size_t idx = m_machineName.find("Server");
   if(idx != std::string::npos) {
      if(m_actionSystem.isMove() == true)
         move(timePass, m_targetPosition.fX, m_targetPosition.fY, true);
   }
#elif _GAMEENGINE_2D_
   if(m_actionSystem.isMove() == true)
      move(timePass, m_targetPosition.fX, m_targetPosition.fY, m_bFaceTarget);
#endif

   if((m_actionSystem.isMove() == true) && (m_bKeyMoveEnabled == true))
      ;
   else if((m_actionSystem.isMove() == true) && (isReachTarget() == true)) {
      CActionEvent actEvent;
      actEvent.m_event = AET_REACH;
      CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);
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
   return m_actionSystem.isChangeAction();
}

CAction* CUnitObject::getCurAction()
{
   return m_actionSystem.getCurAction();
}

bool CUnitObject::isMove()
{
   if(m_actionSystem.isMove() == true)
      return true;
   else
      return false;
}

void CUnitObject::setKeyMoveEnabled(bool bEnable)
{
   m_bKeyMoveEnabled = bEnable;
}

std::vector<std::string> CUnitObject::getAllAnimationName()
{
   return m_actionSystem.getAllAnimationName();
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

void CUnitObject::addFightEventListener(IFightEventListener *pListener)
{
   m_fightSystem.addFightEventListener(pListener);
}

void CUnitObject::removeFightEventListener(IFightEventListener *pListener)
{
   m_fightSystem.removeFightEventListener(pListener);
}

void CUnitObject::addDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener)
{
   m_actionSystem.addDrawWeaponNotifyListener(pListener);
}

void CUnitObject::removeDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener)
{
   m_actionSystem.removeDrawWeaponNotifyListener(pListener);
}

void CUnitObject::addPutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener)
{
   m_actionSystem.addPutinWeaponNotifyListener(pListener);
}

void CUnitObject::removePutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener)
{
   m_actionSystem.removePutinWeaponNotifyListener(pListener);
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
   m_actionSystem.draw(hdc, (int)m_position.fX - size, (int)m_position.fY + size + 22);
}
#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2012/12/22

std::string CUnitObject::getMachineName()
{
   return m_machineName;
}

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

CSkill* CUnitObject::getSkill(int skillID)
{
   CSkill *pFindSkill = NULL;
   std::vector<CSkill *>::iterator itSkill = m_vSkill.begin();
   while(itSkill != m_vSkill.end()) {
      if((*itSkill)->getID() == skillID) {
         pFindSkill = (*itSkill);
         break;
      }

      ++itSkill;
   }

   return pFindSkill;
}

void CUnitObject::SkillCoolDown(float timepass)
{
   std::vector<CSkill *>::iterator pi = m_vSkill.begin();
   while(m_vSkill.end() != pi) {
      (*pi)->updateCoolDown(timepass);
      ++pi;
   }
}

bool CUnitObject::addSkill(int skillID)
{
   CSkill *pSkill = new CSkill();
   pSkill->create(skillID);
   if(pSkill->canLearn(m_level)) {
      m_vSkill.push_back(pSkill);
      notifyAddSkillUpdate(skillID);
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
      ++it;
   }
}

void CUnitObject::notifyAddSkillUpdate(int skillID)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.begin();
   while(it != m_skillEventListeners.end()) {
      (*it)->updateAddSkill(this, skillID);
      ++it;
   }
}

void CUnitObject::notifyPlaySound(std::string soundFile)
{
#ifdef _GAMESOUND_
   size_t idx = m_machineName.find("Server");
   if(idx != std::string::npos)
      return;

   CSoundManager::getInstance()->playSound(SOUND_DIR + soundFile);
#endif  // #ifdef _GAMESOUND_
}

void CUnitObject::notifyAttack()
{
   // 動作系統通知要扣血計算
   useSkill(m_castSkillID);
}

void CUnitObject::setUID(long long uid)
{
   m_uid = uid;

   m_actionSystem.setUID(m_uid);
   m_fightSystem.setUID(m_uid);
}

//#ifdef _GAMEENGINE_2D_
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
//#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2013/01/01