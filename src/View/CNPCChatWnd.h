#ifndef _CNPCCHATWND_H_
#define _CNPCCHATWND_H_

#include "CWindow.h"
#include "CNPC.h"
#include "CPlayer.h"
#include <network\gp_socket.h>

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

using namespace GP ;

class CNPC ;
class CNPCChatWnd:public CWindow
{
private:
	enum {BUTTON_COUNT = 8, TEXT_COUNT = 8, CELL_SIZE = 20} ;
	enum {TYPE_CHAT, TYPE_REWARD} ;
	int type ;
	int selQuestID ;//目前選的任務編號

	CNPC* m_pNPC;
    CPlayer       *m_pPlayer;
    NetStream *m_pNetStream;

#ifdef _GAMEENGINE_3D_	
	CImageButton   *m_vpBtn[BUTTON_COUNT];
    CTextAreaOgre  *m_vpText[TEXT_COUNT];
    COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	CTextButton    *m_vpBtn[BUTTON_COUNT];
    CTextArea      *m_vpText[TEXT_COUNT];
#endif

public:
	CNPCChatWnd () ;
	~CNPCChatWnd () ;

	void init (int _x, int _y, CPlayer* pb, NetStream *pNetStream) ;
	void setNPC (CNPC*) ;

	// CWindow
	/* virtual */ bool canDrag(int tx, int ty);  
	/* virtual */ void onLCommand(int btnID);
	/* virtual */ void show(bool bShow);
#ifdef _GAMEENGINE_3D_
	/* virtual */ void onDrag();
	/* virtual */ void setZOrder(int order);
#endif
//	draw (HDC hdc, int ox, int oy) ;

} ;

#endif