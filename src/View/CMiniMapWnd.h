#ifndef _CMINIMAPWND_H_
#define _CMINIMAPWND_H_

#include "CWindow.h"
#include "CPlayer.h"
#include "ISkillEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

#ifdef _GAMEENGINE_3D_
class CMiniIcon:public CImageButton
{
public:
	CUnitObject* pUnit ;
} ;
#endif

class CScene;
class CMiniMapWnd:public CWindow
{
private:
	CUnitObject* pPlr ;
#ifdef _GAMEENGINE_3D_
	CImageButton* pBtn ;
#endif
	//Button* pBtnHPbar ;

public:
	enum {HALF_MAP_SIZE = 100 } ;
#ifdef _GAMEENGINE_3D_

	CTextAreaOgre* pText ;
	COverlayUI      m_overlay;  //ºÞ²zoverlay
#endif
	float* camDir ;
	CScene* pScene ;

	enum {MAX_ICON = 50} ;
#ifdef _GAMEENGINE_3D_
	typedef std::list <CMiniIcon> V_MINI_ICON ;
	V_MINI_ICON vMiniIcon ;
	enum {ICON_SIZE = 5 } ;
#endif

	~CMiniMapWnd () {};

	void init (int _x, int _y, CUnitObject* pPlr, CScene* pScene, float* camDir) ;

	//void draw (HDC hdc , int ox , int oy ) ;

	void update() ;
	void onAddUnit (CUnitObject*) ;
	void onAddNPCUnit (CUnitObject* pu) ;
	void onDelUnit (CUnitObject*) ;

	bool canDrag (int tx, int ty) ;
	void onDrag();
	void setZOrder (int order) ;
	void show (bool bShow) ;

} ;
#endif