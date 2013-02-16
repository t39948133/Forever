#include "CSkillWnd.h"
#include "CSkill.h"

CSkillWnd::~CSkillWnd()
{
   if(m_pPlayer != NULL)
      m_pPlayer->removeSkillEventListener(this);
}

void CSkillWnd::init(int _x, int _y, CPlayer *pPlayer)
{
	m_pPlayer = pPlayer;
   if(m_pPlayer != NULL)
      m_pPlayer->addSkillEventListener(this);
	
	x = _x;
	y = _y;
	w = 408;
	h = 531;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
   m_overlay.setBackImage("UI/BG/SkillWnd");

	for(int i = 0; i < BUTTON_COUNT; i++) {	
		m_vpBtn[i] = new CImageButton();
		m_vpBtn[i]->init(&m_overlay, 13, 61 + i * ICON_SIZE + 4 * i, ICON_SIZE, ICON_SIZE, i);
		addChild(m_vpBtn[i]);
	}

   for(int i = TEXT_TITLE; i < TEXT_FIELD_START; i++) {
      switch(i) {
         case TEXT_TITLE:
            m_vpText[i] = new CTextAreaOgre();
		      m_vpText[i]->init(&m_overlay, 0, 0, w, 25);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
			   m_vpText[i]->setText("技能", 1, 1, 1);
            break;

         case TEXT_SKILL_NAME:
            m_vpText[i] = new CTextAreaOgre();
		      m_vpText[i]->init(&m_overlay, 14, 39, 288, 16);
            m_vpText[i]->setFont(10, true);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
			   m_vpText[i]->setText("技能名稱", 1, 1, 1);
            break;

         case TEXT_SKILL_KIND:
            m_vpText[i] = new CTextAreaOgre();
		      m_vpText[i]->init(&m_overlay, 310, 39, 62, 16);
            m_vpText[i]->setFont(10, true);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
			   m_vpText[i]->setText("種類", 1, 1, 1);
            break;
      }

		addChild(m_vpText[i]);
   }

   for(int i = 0; i < BUTTON_COUNT; i++) {
		m_vpText[i * 2 + TEXT_FIELD_START] = new CTextAreaOgre();
		m_vpText[i * 2 + TEXT_FIELD_START]->init(&m_overlay, 60, 64 + i * 34 + 10 * i, 241, 34);
      m_vpText[i * 2 + TEXT_FIELD_START]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
		addChild(m_vpText[i * 2 + TEXT_FIELD_START]);

      m_vpText[i * 2 + TEXT_FIELD_START + 1] = new CTextAreaOgre();
		m_vpText[i * 2 + TEXT_FIELD_START + 1]->init(&m_overlay, 311, 64 + i * 34 + 10 * i, 60, 34);
      m_vpText[i * 2 + TEXT_FIELD_START + 1]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
      m_vpText[i * 2 + TEXT_FIELD_START + 1]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
		addChild(m_vpText[i * 2 + TEXT_FIELD_START + 1]);
	}
#else _GAMEENGINE_2D_	
   for(int i = 0; i < BUTTON_COUNT; i++) {	
		m_vpBtn[i] = new CTextButton();
		m_vpBtn[i]->init(13, 61 + i * ICON_SIZE + 4 * i, ICON_SIZE, ICON_SIZE, i);
		addChild(m_vpBtn[i]);
	}

   for(int i = TEXT_TITLE; i < TEXT_FIELD_START; i++) {
      switch(i) {
         case TEXT_TITLE:
            m_vpText[i] = new CTextArea();
		      m_vpText[i]->init(0, 0, w, 25);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
			   m_vpText[i]->setText("技能", 1, 1, 1);
            break;

         case TEXT_SKILL_NAME:
            m_vpText[i] = new CTextArea();
		      m_vpText[i]->init(14, 39, 288, 16);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
			   m_vpText[i]->setText("技能名稱", 1, 1, 1);
            break;

         case TEXT_SKILL_KIND:
            m_vpText[i] = new CTextArea();
		      m_vpText[i]->init(310, 39, 62, 16);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
			   m_vpText[i]->setText("種類", 1, 1, 1);
            break;
      }

		addChild(m_vpText[i]);
   }

   for(int i = 0; i < BUTTON_COUNT; i++) {
		m_vpText[i * 2 + TEXT_FIELD_START] = new CTextArea();
		m_vpText[i * 2 + TEXT_FIELD_START]->init(60, 64 + i * 34 + 10 * i, 241, 34);
		addChild(m_vpText[i * 2 + TEXT_FIELD_START]);

      m_vpText[i * 2 + TEXT_FIELD_START + 1] = new CTextArea();
		m_vpText[i * 2 + TEXT_FIELD_START + 1]->init(311, 64 + i * 34 + 10 * i, 60, 34);
      m_vpText[i * 2 + TEXT_FIELD_START + 1]->setAlignment(CTextArea::CENTER);
		addChild(m_vpText[i * 2 + TEXT_FIELD_START + 1]);
	}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   updateSkill(m_pPlayer);
   show(false);
}

bool CSkillWnd::canDrag(int tx, int ty)
{
	return ty < 25;
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
                  newHotKeyItem.iField = i;
                  newHotKeyItem.pSkill = pSkill;
                  newHotKeyItem.pItem = NULL;
                  m_pPlayer->addHotKeyItem(newHotKeyItem);

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
   m_overlay.setPosition(x, y);
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CSkillWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

void CSkillWnd::updateSkill(CUnitObject *pUnitObject)
{
   std::vector<CSkill *> vtSkill = pUnitObject->getSkill();

   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(i < (int)vtSkill.size()) {
         CSkillInfo *pSkillInfo = vtSkill.at(i)->getInfo();
         
         if(pSkillInfo != NULL) {
#ifdef _GAMEENGINE_3D_
            m_vpBtn[i]->setImage(pSkillInfo->geticonName());
#elif _GAMEENGINE_2D_
            m_vpBtn[i]->str = pSkillInfo->getName();
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

            m_vpText[i * 2 + TEXT_FIELD_START]->setText(pSkillInfo->getName(), 1, 1, 1);
            if(pSkillInfo->getType() == TYPE_ACTIVE)
               m_vpText[i * 2 + TEXT_FIELD_START + 1]->setText("主動", 1, 1, 1);
            else
               m_vpText[i * 2 + TEXT_FIELD_START + 1]->setText("被動", 1, 1, 1);
         }
      }
      else {
#ifdef _GAMEENGINE_3D_
         m_vpBtn[i]->setImage("UI/Icon/NullBackpack");
#elif _GAMEENGINE_2D_
         m_vpBtn[i]->str = "";
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
         m_vpText[i * 2 + TEXT_FIELD_START]->setText("", 1, 1, 1);
         m_vpText[i * 2 + TEXT_FIELD_START + 1]->setText("", 1, 1, 1);
      }
   }
}

void CSkillWnd::updateSkillCoolDown(CSkill *pSkill)
{
}