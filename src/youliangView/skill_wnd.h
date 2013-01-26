#ifndef _SKILL_WND_H_
#define _SKILL_WND_H_

#include <windows.h>
#include <network\\gp_socket.h>
#include "window.h"
#include "skill_info_wnd.h"


class TargetInfoWnd ;
class HotKeyWnd ;
class Scene ;
class Player ;
class SkillWnd:public Window
{
public:
	enum {BUTTON_COUNT = 7, TEXT_COUNT = 33, ICON_SIZE = 50} ;

#ifdef _PROJECT_OGRE_3D_	
	ImageButton* vpBtn[BUTTON_COUNT] ;
#else _PROJECT_GDI_
	TextButton* vpBtn[BUTTON_COUNT] ;
#endif
	TextArea* vpText[TEXT_COUNT];

	SkillInfoWnd* pSkillInfoWnd ;
	WindowMan windowMan ;

	TargetInfoWnd* pTargetInfoWnd ;
	Player* pPlayer ;
	GP::NetStream* pStream ;
	Scene* pScene ;
	HotKeyWnd* phkWnd ;

	bool bPickGround ;
	int groudSkillOffset ;//對地板使用的技能

	~SkillWnd () {};

	void init (int _x, int _y, GP::NetStream*, Player* pb,
				TargetInfoWnd*, Scene*, HotKeyWnd* pw) ;

	bool canDrag (int tx, int ty) ;
	void onCommand (int) ;
	void onCommandFocus (int id) ;

#ifdef _PROJECT_OGRE_3D_
	void onMove () ;

	void setZOrder (int z) ;

	void onSwitch () ;
#endif
} ;

#endif