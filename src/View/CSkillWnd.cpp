#include "CSkillWnd.h"
#include "CSkill.h"
#include "CWindowMan.h"

CSkillWnd::~CSkillWnd()
{
   if(m_pPlayer != NULL)
      m_pPlayer->removeModelEventListener(this);
}

void CSkillWnd::init(int _x, int _y, CPlayer *pb)
{
	m_pPlayer = pb;
   m_pPlayer->addModelEventListener(this);
	
	x = _x ;
	y = _y ;
	w = CELL_SIZE*BUTTON_COUNT ;
	h = CELL_SIZE*(BUTTON_COUNT+1) ;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);

	for(int i = 0; i < BUTTON_COUNT; i++)
	{	
		m_vpBtn[i] = new CImageButton();
		m_vpBtn[i]->init(m_overlay, 0, (i+1)*CELL_SIZE, CELL_SIZE, CELL_SIZE, i);
		addChild(m_vpBtn[i]);
	}

   for(int i = 0; i < BUTTON_COUNT; i++)
	{		
		CImageButton *pBtn = new CImageButton();
		pBtn->init(m_overlay, CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE, i);
		addChild(pBtn);
	}

	CTextAreaOgre *pTA = new CTextAreaOgre();
	pTA->init(m_overlay, w/2, 0, w, CELL_SIZE);
	pTA->setText("技能表", 1, 1, 1);
	addChild(pTA);

	for(int i = 0; i < TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextAreaOgre();
		m_vpText[i]->init(m_overlay, CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE);
		addChild(m_vpText[i]);
	}

#else _GAMEENGINE_2D_	
	for(int i = 0; i < BUTTON_COUNT; i++)
	{		
		m_vpBtn[i] = new CTextButton();
		m_vpBtn[i]->init(0, (i+1)*CELL_SIZE, CELL_SIZE, CELL_SIZE, i);
		addChild(m_vpBtn[i]);
	}

   for(int i = 0; i < BUTTON_COUNT; i++)
	{		
		CTextButton *pBtn = new CTextButton();
		pBtn->init(CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE, i);
		addChild(pBtn);
	}

	CTextArea *pTA = new CTextArea();
	pTA->init(w/2, 0, w, CELL_SIZE);
	pTA->setText("技能表", 1, 1, 1);
	addChild(pTA);

	for(int i = 0; i < TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextArea();
		m_vpText[i]->init(CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE);
		addChild(m_vpText[i]);
	}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   updateSkill(m_pPlayer);
   show(false);
}

bool CSkillWnd::canDrag(int tx, int ty)
{
	return ty < CELL_SIZE ;
}

void CSkillWnd::onLCommand(int btnID)
{
   // 把技能放於HotKey上
   std::vector<CSkill *> vtPlayerSkill = m_pPlayer->getSkill();
   if(btnID >= 0 && btnID < (int)vtPlayerSkill.size()) {
      CSkill *pSkill = vtPlayerSkill.at(btnID);
      if(pSkill != NULL) {
         for(int i = 0; i < m_pPlayer->getHotKeySize(); i++) {
            HotKeyItem *pHotKeyItem = m_pPlayer->getHotKeyItem(i);
            if(pHotKeyItem != NULL) {
               if((pHotKeyItem->pItem == NULL) && (pHotKeyItem->pSkill == NULL)) {
                  HotKeyItem newHotKeyItem;
                  newHotKeyItem.pSkill = pSkill;
                  newHotKeyItem.pItem = NULL;
                  m_pPlayer->addHotKeyItem(i, newHotKeyItem);

                  break;
               }
            }
         }
      }
   }
}

WindowClassType CSkillWnd::getClassType()
{
   return WND_SKILL;
}

void CSkillWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

void CSkillWnd::onDrag()
{
#ifdef _GAMEENGINE_3D_
	m_overlay.setPos(x, y);
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CSkillWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

void CSkillWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
}

void CSkillWnd::updateBackpack(CUnitObject *pUnitObject)
{
}

void CSkillWnd::updateSkill(CUnitObject *pUnitObject)
{
   CPlayer *pPlayer = dynamic_cast<CPlayer *>(pUnitObject);
   if(pPlayer != NULL) {
      std::vector<CSkill *> vtSkill = pPlayer->getSkill();
      for(int i = 0; i < TEXT_COUNT; i++) {
         if(i < (int)vtSkill.size()) {
            CSkillInfo *pSkillInfo = vtSkill.at(i)->getInfo();
            
            if(pSkillInfo != NULL) {
#ifdef _GAMEENGINE_3D_
               m_vpBtn[i]->setImage(pSkillInfo->geticonName());
#elif _GAMEENGINE_2D_
               m_vpBtn[i]->str = pSkillInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

               m_vpText[i]->setText(pSkillInfo->getName() + "\n" + pSkillInfo->getDesc(), 1, 1, 1);
            }
         }
         else {
#ifdef _GAMEENGINE_3D_
            m_vpBtn[i]->setImage("Examples/ogreborder");
#elif _GAMEENGINE_2D_
            m_vpBtn[i]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
            m_vpText[i]->setText("", 1, 1, 1);
         }
      }
   }
}

void CSkillWnd::updateHotKeyItem(int field, HotKeyItem *pHotKeyItem)
{
}

void CSkillWnd::updateCoolDown(CSkill *pSkill)
{
}