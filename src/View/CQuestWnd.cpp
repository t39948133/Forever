#include "CQuestWnd.h"

CQuestWnd::CQuestWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) 
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#endif
}

CQuestWnd::~CQuestWnd()
{
#ifdef _GAMEENGINE_3D_
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
#elif _GAMEENGINE_2D_
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
#endif
}
void CQuestWnd::init (int _x, int _y, CPlayer* pb)
{	
	m_pPlayer = pb ;
	x = _x ;
	y = _y ;
	w = 200 ;
	h = TEXT_COUNT*CELL_SIZE ;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
    m_overlay.setBackImage("chat");
	
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextAreaOgre ;
		m_vpText[i]->init (&m_overlay, 0, i*CELL_SIZE, w, CELL_SIZE) ;
		if (i == 0)
		{	
			m_vpText[i]->setText ("任務名稱", 1, 1, 1) ;
		}else if (i == 1)
		{
			m_vpText[i]->setText ("任務內容", 1, 1, 1) ;
		}else
		{
			m_vpText[i]->setText ("", 1, 1, 1) ;
		}
		addChild (m_vpText[i]) ;
	}
#elif _GAMEENGINE_2D_

	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		m_vpBtn[i] = new CTextButton ;
		m_vpBtn[i]->init (0, i*CELL_SIZE, w, CELL_SIZE, i) ;
		addChild (m_vpBtn[i]) ;
	}

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextArea ;
		m_vpText[i]->init (0, i*CELL_SIZE, w, CELL_SIZE) ;
		if (i == 0)
		{	
			m_vpText[i]->setText ("任務名稱", 1, 1, 1) ;
		}else if (i == 1)
		{
			m_vpText[i]->setText ("任務內容", 1, 1, 1) ;
		}else
		{
			m_vpText[i]->setText ("", 1, 1, 1) ;
		}
		addChild (m_vpText[i]) ;
	}
#endif
}

bool CQuestWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CQuestWnd::show(bool bShow)
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
void CQuestWnd::onDrag()
{
   m_overlay.setPosition(x, y);
}

void CQuestWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

/*
void CQuestWnd::draw (HDC hdc, int ox, int oy)
{
	CWindow::draw (hdc, ox, oy) ;

	int i = 0 ;
	V_QUEST::iterator pi = pPlayer->questMap.vQuest.begin () ;
	while (pi != pPlayer->questMap.vQuest.end ())
	{
		QuestInfo* pinfo = pi->getInfo () ;

		TextOut (hdc, 2+x, 2+y+(i+1)*CELL_SIZE, pinfo->name,
					pinfo->name.length ()) ;

		++ pi ;
		i ++ ;
	}
}
*/


