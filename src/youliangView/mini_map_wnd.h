#ifndef _MINI_MAP_WND_H_
#define _MINI_MAP_WND_H_

#include "scene.h"
#include "window.h"
#include "unit.h"
#include "image_button.h"
#include <list>

#ifdef _PROJECT_OGRE_3D_
	#include "overlayUI.h"
#endif

#ifdef _PROJECT_OGRE_3D_
class MiniIcon:public ImageButton
{
public:
	Unit* pUnit ;
} ;
#endif

class MiniMapWnd:public Window
{
private:
	Unit* pPlr ;
#ifdef _PROJECT_OGRE_3D_
	ImageButton* pBtn ;
#endif
	//Button* pBtnHPbar ;

public:
	enum {HALF_MAP_SIZE = 100 } ;
#ifdef _PROJECT_OGRE_3D_

	TextArea* pText ;
#endif
	float* camDir ;
	Scene* pScene ;

	enum {MAX_ICON = 50} ;
#ifdef _PROJECT_OGRE_3D_
	typedef std::list <MiniIcon> V_MINI_ICON ;
	V_MINI_ICON vMiniIcon ;
	enum {ICON_SIZE = 5 } ;
#endif

	~MiniMapWnd () {};

	void init (int _x, int _y, Unit* pPlr, Scene* pScene, float* camDir) ;

	//void draw (HDC hdc , int ox , int oy ) ;

	void update() ;
	void onAddUnit (Unit*) ;
	void onDelUnit (Unit*) ;

	bool canDrag (int tx, int ty) ;
	void onMove () ;
	void setZOrder (int z) ;
	void show (bool bs) ;

} ;
#endif