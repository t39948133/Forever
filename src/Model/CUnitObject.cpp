#include "CUnitObject.h"
#include "AttributeSet.h"

CUnitObject::CUnitObject(std::string strName, long long uid, char level) : m_strName(strName),m_uid(uid),m_level(level)
{
   AttributeClear(m_basAttr);
	AttributeSet(m_advAttr);
   AttributeClear(m_obsAttr);
   AttributeClear(m_comAttr);
   AttributeClear(m_preAttr);

   // Add by Darren Chen on 2012/12/22 {
   m_fDirection = -3.1415926f;  // à︹よ绰(-Z禸)
   m_position.fX = 450.0f;
   m_position.fY = 450.0f;
   m_targetPosition.fX = 450.0f;
   m_targetPosition.fY = 450.0f;
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
}

void CUnitObject::work(float timePass)
{
   m_pActionSystem->work(timePass);

#ifdef _GAMEENGINE_2D_
   if(m_pActionSystem->isMove() == true)
      move(timePass, m_targetPosition.fX, m_targetPosition.fY, m_bFaceTarget);
#endif  // #ifdef _GAMEENGINE_2D_
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

#ifdef _GAMEENGINE_2D_
void CUnitObject::draw(HDC hdc)
{
   int size = 20;
   Ellipse(hdc, (int)m_position.fX - size, (int)m_position.fY - size, (int)m_position.fX + size, (int)m_position.fY + size);

   // 礶よ絬
   MoveToEx(hdc, (int)m_position.fX, (int)m_position.fY, NULL);
   float tx = m_position.fX + size * sin(m_fDirection);
	float ty = m_position.fY + size * cos(m_fDirection);
   LineTo(hdc, (int)tx, (int)ty);

   // 礶笆╰参
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
	if(m_advAttr.iHP < 0 || m_advAttr.iHP == 0)	//⊿﹀ 
	{
		m_advAttr.iHP = 0;
		//祘Α
	}
	else if(m_advAttr.iHP > getHPMax())	//干﹀禬筁程﹀秖 玂程﹀秖
	{
		m_advAttr.iHP = getHPMax();
	}
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
	if(m_advAttr.iMP < 0 || m_advAttr.iMP == 0)	//⊿臸
	{
		m_advAttr.iMP = 0;
	}
	else if(m_advAttr.iMP > getMPMax())	//臸禬筁程臸 玂程臸
	{
		m_advAttr.iMP = getMPMax();
	}
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
  
void CUnitObject::setBasAttr(BasisAttribute basAttr)
{
    m_basAttr = basAttr;
    BasisAttributeSet(m_level, basAttr, m_advAttr, m_obsAttr);
}
  
void CUnitObject::setAdvAttr(AdvancedAttribute advattr)
{
   m_advAttr = advattr;	//砞﹚妮┦戈
   if(getHPMax() < m_advAttr.iHP)
   {
      m_advAttr.iHP = getHPMax();
   }
   if(getMPMax() < m_advAttr.iMP)
   {
      m_advAttr.iMP = getMPMax();
   }
}

AdvancedAttribute CUnitObject::getAdvAttr()
{
   AdvancedAttribute attr = m_advAttr;

   AttributeAdd(attr, m_comAttr.AdvAttr);
   AttributeMulti(attr, m_preAttr);

   return attr;
}

BasisAttribute CUnitObject::getBasAttr()
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

std::vector<CSkill> CUnitObject::getSkill()
{
   return m_vSkill;
}

void CUnitObject::SkillCoolDown(float timepass)
{
    std::vector<CSkill>::iterator pi = m_vSkill.begin();
   while(m_vSkill.end() != pi)
   {
      pi->afterTime(timepass);
      pi++;
   }
}

bool CUnitObject::addSkill(unsigned int id)
{
    CSkill st ;
   st.create(id);
   if(st.canLearn(m_level))
   {
      m_vSkill.push_back(st);
      return true;
   }
   return false;
}

// Add by Darren Chen on 2013/01/01 {
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