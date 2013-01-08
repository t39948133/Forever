#include "CSkillWnd.h"
#include "CSkill.h"
#include "CTextButton.h"

void CSkillWnd::init (int _x, int _y, CPlayer* pb)
{
   bVisible = false;
	pPlayer = pb ;
	
	x = _x ;
	y = _y ;
	w = CELL_SIZE*BUTTON_COUNT ;
	h = CELL_SIZE*(BUTTON_COUNT+1) ;

#ifdef _GAMEENGINE_3D_
	overlaySK.init (x, y, w, h) ;

	for (int i = 0; i<BUTTON_COUNT; i++)
	{	
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlaySK, 0, (i+1)*CELL_SIZE, CELL_SIZE, CELL_SIZE, i) ;
		if (i == 0)
			{
				pBtn->setImage ("skill_5") ;
			}else if (i == 1)
			{
				pBtn->setImage ("skill_1") ;
			}else 
			{
				pBtn->setImage ("ogreborder") ;
			}
		addChild (pBtn) ;
	}

	for (int i = 0; i<BUTTON_COUNT; i++)
	{	
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlaySK, CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE, i) ;
		pBtn->setImage ("ogreborder") ;
		addChild (pBtn) ;
	}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (w-CELL_SIZE/2, 0, CELL_SIZE/2, CELL_SIZE/2, 14) ;
	pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	TextArea* pTA = new TextArea ;
	pTA->init (overlaySK, w/2, 0, w, CELL_SIZE) ;
	pTA->setText ("技能表", 1, 1, 1) ;
	addChild (pTA) ;

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		pTA = new TextArea ;
		pTA->init (overlaySK, CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE) ;

		if (i == 0)
		{			
			pTA->setText ("火球術    耗費10MP", 1, 0, 0) ;
		}else if (i == 1)
		{
			pTA->setText ("治癒術    耗費15MP", 1, 0, 0) ;
		}else
		{
		}

		addChild (pTA) ;
	}

#else _GAMEENGINE_2D_	
	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		CTextButton* pBtn = new CTextButton ;
		pBtn->init (0, (i+1)*CELL_SIZE, CELL_SIZE, CELL_SIZE, i) ;
		addChild (pBtn) ;
	}

	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		CTextButton* pBtn = new CTextButton ;
		pBtn->init (CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE, i) ;
		addChild (pBtn) ;
	}

	CTextArea* pTA = new CTextArea ;
	pTA->init (w/2, 0, w, CELL_SIZE) ;
	pTA->setText ("技能表", 1, 1, 1) ;
	addChild (pTA) ;

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		vpText[i] = new CTextArea ;
		vpText[i]->init (CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE) ;
		addChild (vpText[i]) ;
	}
#endif
}

bool CSkillWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE ;
}

void CSkillWnd::onCommand (int id)
{
}

#ifdef _GAMEENGINE_3D_
void CSkillWnd::onMove ()
{
	overlaySK.setPos (x, y) ;
}

void CSkillWnd::setZOrder (int z)
{
	overlaySK.setZOrder (z) ;
}
#endif

WindowClassType CSkillWnd::getClassType()
{
   return WND_SKILL;
}

#ifdef _GAMEENGINE_2D_
void CSkillWnd::draw(HDC hdc, int ox, int oy)
{
   std::vector<CSkill> vtSkill = pPlayer->getSkill();
   for(int i = 0; i < TEXT_COUNT; i++) {
      if(i < (int)vtSkill.size()) {
         CSkillInfo *pSkillInfo = vtSkill.at(i).getInfo();

         vpText[i]->setText(pSkillInfo->getName() + "\n" + pSkillInfo->getDesc(), 1, 1, 1);
      }
      else
         vpText[i]->setText("", 1, 1, 1);
   }

   CWindow::draw(hdc, ox, oy);
}
#endif