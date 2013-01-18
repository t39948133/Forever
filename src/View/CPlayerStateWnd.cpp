#include "CPlayerStateWnd.h"

CPlayerStateWnd::~CPlayerStateWnd()
{
   if(m_pPlayer != NULL)
      m_pPlayer->removeModelEventListener(this);
}

void CPlayerStateWnd::init(int _x, int _y, CPlayer *pPlr)
{
   m_pPlayer = pPlr;
   m_pPlayer->addModelEventListener(this);

   x = _x;
	y = _y;
	w = 230;
	h = 78;

#ifdef _GAMEENGINE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("KAMEN-stup") ;

	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayUI, 25, i*(CELL_SIZE+3)+3*(i+1), w-33, CELL_SIZE, i) ;
		if (i == 0)
		{
			pBtn->setImage ("ogreborder") ;
		}else if (i == 0)
		{
			pBtn->setImage ("ogreborder") ;
		}else 
		{
			pBtn->setImage ("ogreborder") ;
		}
		
		addChild (pBtn) ;
	}

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		pTA->init (overlayUI, 0, i*(CELL_SIZE+3)+3*(i+1), 30, 30) ;
		char buf[256] ;
		if (i == 0)
		{	
			sprintf_s (buf, sizeof (buf), "HP             %d/ %d", pPlayer->data.iHP, pPlayer->data.iHPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 1)
		{
			sprintf_s (buf, sizeof (buf), "MP             %d/ %d", pPlayer->data.iMP, pPlayer->data.iMPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else
		{
			sprintf_s (buf, sizeof (buf), "XP             %d/ %d", pPlayer->data.m_xp, pPlayer->data.m_xpMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}

		addChild (pTA) ;
	}
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
   CPlayer *pPlayer = dynamic_cast<CPlayer *>(pUnitObject);
   if(pPlayer != NULL) {
      char buf[50];
      for(int i = 0; i<TEXT_COUNT; i++) {
         memset(buf, 0, sizeof(buf));
         if(i == 0) {
            sprintf_s(buf, sizeof(buf), "%5d / %5d", pPlayer->getHP(), pPlayer->getHPMax());
            m_vpText[i]->setText(buf, 1, 1, 1);
         }
         else if(i == 1) {
            sprintf_s(buf, sizeof(buf), "%5d / %5d", pPlayer->getMP(), pPlayer->getMPMax());
            m_vpText[i]->setText(buf, 1, 1, 1);
         }
         else {	
            sprintf_s(buf, sizeof(buf), "%5d / %5d", pPlayer->getXP(), pPlayer->getXPMax());
            m_vpText[i]->setText(buf, 1, 1, 1) ;
         }
      }
   }
}

void CPlayerStateWnd::updateBackpack(CUnitObject *pUnitObject)
{
}

void CPlayerStateWnd::updateSkill(CUnitObject *pUnitObject)
{
}

void CPlayerStateWnd::updateHotKeyItem(int field, HotKeyItem *pHotKeyItem)
{
}

void CPlayerStateWnd::updateCoolDown(CSkill *pSkill)
{
}