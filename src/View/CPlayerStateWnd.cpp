#include "CPlayerStateWnd.h"

CPlayerStateWnd::CPlayerStateWnd()
{
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
}

CPlayerStateWnd::~CPlayerStateWnd()
{
   if(m_pPlayer != NULL) {
      m_pPlayer->removeAdvAttrEventListener(this);
      m_pPlayer->removePlayerAttrEventListener(this);
   }

   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
      }
   }
}

void CPlayerStateWnd::init(int _x, int _y, CPlayer *pPlr)
{
   m_pPlayer = pPlr;
   if(m_pPlayer != NULL) {
      m_pPlayer->addAdvAttrEventListener(this);
      m_pPlayer->addPlayerAttrEventListener(this);
   }

   x = _x;
	y = _y;
#ifdef _GAMEENGINE_3D_
   w = 242;
   h = 56;
#elif _GAMEENGINE_2D_
	w = 230;
	h = 78;
#endif

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);

   for(int i = 0; i < BUTTON_COUNT; i++) {
		m_vpBtn[i] = new CImageButton();

      switch(i) {
         case BUTTON_HP:
		      m_vpBtn[i]->init(&m_overlay, 55, 5 + i * 13 + 4 * i, 181, 13, i);
            m_vpBtn[i]->setImage("UI/BG/HPBar");
            break;

         case BUTTON_MP:
            m_vpBtn[i]->init(&m_overlay, 55, 5 + i * 13 + 4 * i, 181, 13, i);
            m_vpBtn[i]->setImage("UI/BG/MPBar");
            break;

         case BUTTON_XP:
            m_vpBtn[i]->init(&m_overlay, 55, 5 + i * 13 + 4 * i + 1, 181, 13, i);
            m_vpBtn[i]->setImage("UI/BG/XPBar");
            break;
      }
		
		addChild(m_vpBtn[i]);
	}

	for(int i = 0; i <= TEXT_XP; i++) {
		m_vpText[i] = new CTextAreaOgre();
		m_vpText[i]->init(&m_overlay, 23, 3 + i * 15 + 3 * i, 31, 15);
      m_vpText[i]->setFont(10, true);
      m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_RIGHT);
      m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);

      switch(i) {
         case TEXT_HP:      
            m_vpText[i]->setText("HP", 1, 1, 1);
            break;

         case TEXT_MP:
            m_vpText[i]->setText("MP", 1, 1, 1);
            break;

         case TEXT_XP:
            m_vpText[i]->setText("XP", 1, 1, 1);
            break;
      }

		addChild(m_vpText[i]);
	}

   for(int i = 0, j = TEXT_HP_VALUE; i < 3; i++, j++) {
      m_vpText[j] = new CTextAreaOgre();
		m_vpText[j]->init(&m_overlay, 55, 5 + i * 13 + 4 * i, 181, 13);
      m_vpText[j]->setFont(10, true);
      m_vpText[j]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
      m_vpText[j]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
      addChild(m_vpText[j]);
   }

   m_vpText[TEXT_LV_VALUE] = new CTextAreaOgre();
	m_vpText[TEXT_LV_VALUE]->init(&m_overlay, 5, 29, 21, 21);
   m_vpText[TEXT_LV_VALUE]->setFont(10, true);
   m_vpText[TEXT_LV_VALUE]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
   m_vpText[TEXT_LV_VALUE]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
   addChild(m_vpText[TEXT_LV_VALUE]);
#elif _GAMEENGINE_2D_
   for(int i = 0; i<BUTTON_COUNT; i++)
   {
      m_vpBtn[i] = new CTextButton();
      m_vpBtn[i]->init(25, i*(CELL_SIZE+3)+3*(i+1), 200, CELL_SIZE, i);
      addChild(m_vpBtn[i]);
   }

   for(int i = 0; i<TEXT_COUNT; i++)
   {
      CTextArea *pTA = new CTextArea();
      pTA->init(0, i*(CELL_SIZE+3)+3*(i+1), 30, 30);

      if(i == 0)
         pTA->setText("HP", 1, 1, 1);
      else if(i == 1)	
         pTA->setText("MP", 1, 1, 1);
      else	
         pTA->setText("XP", 1, 1, 1);

      addChild(pTA);
   }

	for(int i = 0; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextArea();
      m_vpText[i]->init(25, i*(CELL_SIZE+3)+3*(i+1), 200, CELL_SIZE);
		addChild(m_vpText[i]);
	}
#endif

   updateAdvAttr(m_pPlayer);
   updatePlayerAttr(m_pPlayer);
   show(true);
}

bool CPlayerStateWnd::canDrag(int tx, int ty)
{
   return false;
}

WindowClassType CPlayerStateWnd::getClassType()
{
   return WND_PLAYERSTATE;
}

void CPlayerStateWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CPlayerStateWnd::setZOrder(int order)
{
   m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

void CPlayerStateWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
   char buf[50];

   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%d / %d", pUnitObject->getHP(), pUnitObject->getHPMax());
#ifdef _GAMEENGINE_3D_
   float diffHP = (float)m_vpBtn[BUTTON_HP]->w / (float)pUnitObject->getHPMax();
   m_vpBtn[BUTTON_HP]->setWidth(diffHP * (float)pUnitObject->getHP());
   m_vpText[TEXT_HP_VALUE]->setText(buf, 1, 1, 1);
#elif _GAMEENGINE_2D_
   m_vpText[0]->setText(buf, 1, 1, 1);
#endif

   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%d / %d", pUnitObject->getMP(), pUnitObject->getMPMax());
#ifdef _GAMEENGINE_3D_
   float diffMP = (float)m_vpBtn[BUTTON_MP]->w / (float)pUnitObject->getMPMax();
   m_vpBtn[BUTTON_MP]->setWidth(diffMP * (float)pUnitObject->getMP());
   m_vpText[TEXT_MP_VALUE]->setText(buf, 1, 1, 1);
#elif _GAMEENGINE_2D_
   m_vpText[1]->setText(buf, 1, 1, 1);
#endif
}

void CPlayerStateWnd::updatePlayerAttr(CPlayer *pPlayer)
{
   char buf[50];

   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%d / %d", pPlayer->getXP(), pPlayer->getXPMax());
#ifdef _GAMEENGINE_3D_
   float diffXP = (float)m_vpBtn[BUTTON_XP]->w / (float)pPlayer->getXPMax();
   m_vpBtn[BUTTON_XP]->setWidth(diffXP * (float)pPlayer->getXP());
   m_vpText[TEXT_XP_VALUE]->setText(buf, 1, 1, 1) ;
#elif _GAMEENGINE_2D_
   m_vpText[2]->setText(buf, 1, 1, 1) ;
#endif

#ifdef _GAMEENGINE_3D_
   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%d", pPlayer->getLevel());
   m_vpText[TEXT_LV_VALUE]->setText(buf, 1, 1, 1) ;
#endif
}