#include "skill_wnd.h"
#include "target_info_wnd.h"
#include "net_packet.h"
#include "player.h"
#include "image_button.h"

//背包視窗
void SkillWnd::init (int _x, int _y, GP::NetStream* pns, Player* pb,
					TargetInfoWnd* pti, Scene* psc)
{
	bPickGround = false ;
	pScene = psc ;
	pTargetInfoWnd = pti ;
	pPlayer = pb ;
	pStream = pns ;
	x = _x ;
	y = _y ;
	w = CELL_SIZE*BUTTON_COUNT ;
	h = CELL_SIZE*(BUTTON_COUNT+1) ;

#ifdef _PROJECT_OGRE_3D_
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

#else _PROJECT_GDI_	
	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		TextButton* pBtn = new TextButton ;
		pBtn->init (0, (i+1)*CELL_SIZE, CELL_SIZE, CELL_SIZE, i) ;
		addChild (pBtn) ;
	}

	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		TextButton* pBtn = new TextButton ;
		pBtn->init (CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE, i) ;
		addChild (pBtn) ;
	}
/*
	TextButton* pBtn = new TextButton ;
	pBtn->init (w-CELL_SIZE/2, 0, CELL_SIZE/2, CELL_SIZE/2, 14) ;
	pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	TextArea* pTA = new TextArea ;
	pTA->init (w/2, 0, w, CELL_SIZE) ;
	pTA->setText ("技能表", 1, 1, 1) ;
	addChild (pTA) ;

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		pTA = new TextArea ;
		pTA->init (CELL_SIZE, (i+1)*CELL_SIZE, w-CELL_SIZE, CELL_SIZE) ;
//		char buf[256] ;

		if (i == 0)
		{			
			pTA->setText ("火球術    耗費???MP", 1, 1, 1) ;
		}else if (i == 1)
		{
//			sprintf_s (buf, sizeof (buf), "金幣         %d元", pPlayer->money) ;
			pTA->setText ("治癒術    耗費???MP", 1, 1, 1) ;
		}

		addChild (pTA) ;
	}
#endif
}

bool SkillWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE ;
}

void SkillWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_
void SkillWnd::onMove ()
{
	overlaySK.setPos (x, y) ;
}

void SkillWnd::setZOrder (int z)
{
	overlaySK.setZOrder (z) ;
}
#endif


/*
void SkillWnd::onClick (int tx, int ty)
{
	int offset = (ty-CELL_SIZE)/CELL_SIZE ;

	Unit* pTarget = pTargetInfoWnd->getTarget () ;
	if (pPlayer->canUseSkill (offset, pTarget))
	{

		Skill* pSkill = pPlayer->getSkill (offset) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			if (pInfo->target == SkillInfo::TARGET_GROUND)
			{
				//點地板的技能
				groudSkillOffset = offset ;//對地板使用的技能
				bPickGround = true ;
			}else
			{
				long long targetUID = -1 ;

				if (pInfo->target == SkillInfo::TARGET_SELF)
				{
					//對自己用
					targetUID = -1 ;
				}else
				{
					//對其他目標用
					if (pTarget != NULL)
					{
//						Unit* pTarget = pTargetInfoWnd->pMonster ;
						if (pTarget == NULL)
							targetUID = -1 ;
						else
							targetUID = pTarget->UID ;
					}
				}

				PacketUseSkill pkg ;
				pkg.pack (offset, targetUID) ;

				pStream->send (&pkg, sizeof (pkg)) ;
			}
		}
	}
}
*/

/*
	void SkillWnd::draw (HDC hdc)
	{
		Window::draw (hdc, 0, 0) ;

		Rectangle (hdc, x, y, x+w, y+CELL_SIZE) ;

		char buf[256] ;
		for (int i = 0; (size_t) i<pPlayer->vSkill.size (); i++)
		{
			Skill& skill = pPlayer->vSkill[i] ;
			SkillInfo* pInfo = skill.getInfo () ;
			if (pInfo != NULL)
			{
				if (i == pPlayer->castSkillID && 
						pPlayer->castTime > 0)
				{
					sprintf_s (buf, sizeof(buf), "[%.2f][%.2f] %s", 
						pPlayer->castTime, skill.coolDown, (const char*)(pInfo->name)) ;
				}else
				{
					sprintf_s (buf, sizeof(buf), "[%.2f] %s", skill.coolDown, (const char*)(pInfo->name)) ;
				}
				TextOut (hdc, x+3, y+(i+1)*CELL_SIZE, buf, strlen (buf)) ;
			}
		}
	}
	*/
