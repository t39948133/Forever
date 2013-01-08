#ifndef _SKILL_WND_H_
#define _SKILL_WND_H_

#include <windows.h>
#include <network\\gp_socket.h>
#include "window.h"

#ifdef _PROJECT_OGRE_3D_
	#include "overlayUI.h"
#endif
class TargetInfoWnd ;

class Scene ;
class Player ;
class SkillWnd:public Window
{
public:
	enum {BUTTON_COUNT = 7, CELL_SIZE = 40, TEXT_COUNT = 7} ;
	
	#ifdef _PROJECT_OGRE_3D_
		OverlayUI overlaySK ;//管理overlay
	#endif
	TargetInfoWnd* pTargetInfoWnd ;
	Player* pPlayer ;
	GP::NetStream* pStream ;
	Scene* pScene ;

	bool bPickGround ;
	int groudSkillOffset ;//對地板使用的技能

	~SkillWnd () {};

	void init (int _x, int _y, GP::NetStream*, Player* pb,
				TargetInfoWnd*, Scene*) ;

	bool canDrag (int tx, int ty) ;
	void onCommand (int) ;

#ifdef _PROJECT_OGRE_3D_
	void onMove () ;

	void setZOrder (int z) ;

#endif

//	void onClick (int tx, int ty) ;

//	void draw (HDC hdc) ;
} ;

#endif