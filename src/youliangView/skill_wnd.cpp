#include "skill_wnd.h"
#include "target_info_wnd.h"
#include "net_packet.h"
#include "player.h"
#include "image_button.h"
#include "hotkey_wnd.h"

//背包視窗
void SkillWnd::init (int _x, int _y, GP::NetStream* pns, Player* pb,
					TargetInfoWnd* pti, Scene* psc, HotKeyWnd* pw)
{
	bVisible = true ;
	bPickGround = false ;
	pScene = psc ;
	pTargetInfoWnd = pti ;
	pPlayer = pb ;
	pStream = pns ;
	phkWnd = pw ;
	x = _x ;
	y = _y ;
	w = 593 ;
	h = 485 ;

	pSkillInfoWnd = new SkillInfoWnd ;
	pSkillInfoWnd->init (x, y) ;
	windowMan.addWnd (pSkillInfoWnd) ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
//	overlayUI.getOverlay ()->hide () ;
	overlayUI.setImage ("skill") ;

	for (int i = 0; i<BUTTON_COUNT; i++)
	{	
		vpBtn[i] = new ImageButton ;
		vpBtn[i]->init (overlayUI, 4, i*58+83, ICON_SIZE, ICON_SIZE, i) ;
		Skill* pSkill = pPlayer->getSkill (i) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
			addChild (vpBtn[i]) ;
		}
	}	

	for (int i = 0; i<7; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, 65, i*57+102, 200, 50) ;
		Skill* pSkill = pPlayer->getSkill (i) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			vpText[i]->setText (pInfo->name, 1, 1, 1) ;	
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 7; i<14; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, 300, (i-7)*57+102, 80, 50) ;
		Skill* pSkill = pPlayer->getSkill (i-7) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			char buf[256] ;
			sprintf_s (buf, sizeof (buf), "costMP:%d", pInfo->costMP) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 14; i<21; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI,  400, (i-14)*57+102, 80, 50) ;
		Skill* pSkill = pPlayer->getSkill (i-14) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			char buf[256] ;
			sprintf_s (buf, sizeof (buf), "施法時間:%d", pInfo->castTime) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 21; i<28; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, 500, (i-21)*57+102, 80, 50) ;
		Skill* pSkill = pPlayer->getSkill (i-21) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			char buf[256] ;
			sprintf_s (buf, sizeof (buf), "冷卻時間:%d", pInfo->coolDown) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 28; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		if (i == 28)
		{
			vpText[i]->init (overlayUI, 264, 13, 60, 20) ;
			vpText[i]->setText ("技能表", 1, 1, 1) ;
		}else if (i == 29)
		{
			vpText[i]->init (overlayUI, 130, 55, 40, 20) ;
			vpText[i]->setText ("名稱", 1, 1, 1) ;
		}else if (i == 30)
		{
			vpText[i]->init (overlayUI, 315, 55, 60, 20) ;
			vpText[i]->setText ("消耗MP", 1, 1, 1) ;
		}else if (i == 31)
		{
			vpText[i]->init (overlayUI, 410, 55, 80, 20) ;
			vpText[i]->setText ("施法時間", 1, 1, 1) ;
		}else if (i == 32)
		{
			vpText[i]->init (overlayUI, 510, 55, 80, 20) ;
			vpText[i]->setText ("冷卻時間", 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
		
#else _PROJECT_GDI_	
	for (int i = 0; i<BUTTON_COUNT; i++)
	{	
		vpBtn[i] = new TextButton ;
		vpBtn[i]->init (4, i*58+83, ICON_SIZE, ICON_SIZE, i) ;
		Skill* pSkill = pPlayer->getSkill (i) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			vpBtn[i]->str = pInfo->name ;
			addChild (vpBtn[i]) ;
		}
	}	

	for (int i = 0; i<7; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (65, i*57+102, 200, 50) ;
		Skill* pSkill = pPlayer->getSkill (i) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			vpText[i]->setText (pInfo->name, 1, 1, 1) ;	
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 7; i<14; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (300, (i-7)*57+102, 80, 50) ;
		Skill* pSkill = pPlayer->getSkill (i-7) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			char buf[256] ;
			sprintf_s (buf, sizeof (buf), "costMP:%d", pInfo->costMP) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 14; i<21; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (400, (i-14)*57+102, 80, 50) ;
		Skill* pSkill = pPlayer->getSkill (i-14) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			char buf[256] ;
			sprintf_s (buf, sizeof (buf), "施法時間:%d", pInfo->castTime) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 21; i<28; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (500, (i-21)*57+102, 80, 50) ;
		Skill* pSkill = pPlayer->getSkill (i-21) ;
		if (pSkill != NULL)
		{
			SkillInfo* pInfo = pSkill->getInfo () ;
			char buf[256] ;
			sprintf_s (buf, sizeof (buf), "冷卻時間:%d", pInfo->coolDown) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
			addChild (vpText[i]) ;
		}		
	}

	for (int i = 28; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		if (i == 28)
		{
			vpText[i]->init (264, 13, 60, 20) ;
			vpText[i]->setText ("技能表", 1, 1, 1) ;
		}else if (i == 29)
		{
			vpText[i]->init (130, 55, 40, 20) ;
			vpText[i]->setText ("名稱", 1, 1, 1) ;
		}else if (i == 30)
		{
			vpText[i]->init (315, 55, 60, 20) ;
			vpText[i]->setText ("消耗MP", 1, 1, 1) ;
		}else if (i == 31)
		{
			vpText[i]->init (410, 55, 80, 20) ;
			vpText[i]->setText ("施法時間", 1, 1, 1) ;
		}else if (i == 32)
		{
			vpText[i]->init (510, 55, 80, 20) ;
			vpText[i]->setText ("冷卻時間", 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
#endif
}

bool SkillWnd::canDrag (int tx, int ty)
{
	return ty < 40 ;
}

void SkillWnd::onCommand (int id)
{
	Skill* pSkill = pPlayer->getSkill (id) ;
	if (pSkill != NULL)
	{
		SkillInfo* pInfo = pSkill->getInfo () ;		
		phkWnd->addSkillHotKey (id) ;	
	}
}

void SkillWnd::onCommandFocus (int id)
{
	Skill* pSkill = pPlayer->getSkill (id) ;
	if (pSkill != NULL)
	{
		SkillInfo* pInfo = pSkill->getInfo () ;	
		if (pInfo != NULL)
		{
			pSkillInfoWnd->setItem (pInfo->name) ;	
			pSkillInfoWnd->setPos (x+ICON_SIZE, y+(id%9)*ICON_SIZE+ICON_SIZE) ; 
			setInfoWnd (pSkillInfoWnd) ;
			pSkillInfoWnd->show (true) ;
		}else
		{
			pSkillInfoWnd->show (false) ;
		}
	}else
	{
		pSkillInfoWnd->show (false) ;
	}
}


#ifdef _PROJECT_OGRE_3D_
void SkillWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void SkillWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}
void SkillWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif
