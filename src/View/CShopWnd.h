#ifndef _CSHOPWND_H_
#define _CSHOPWND_H_

#include "CWindow.h"
#include "CPlayer.h"
#include "CBackpackWnd.h"

#include <network\gp_socket.h>

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CShopWnd : public CWindow
{
   public:
      /*enum {CLOSE_BUTTON = 10, BUTTON_COUNT = 11, 
		      SHOP_TEXT = 10, TEXT_COUNT = 11, ICON_SIZE = 50};*/

      enum {BUTTON_CLOSE, BUTTON_ICON_START, BUTTON_COUNT = 10 + BUTTON_ICON_START, ICON_SIZE = 40};
      enum {TEXT_TITLE, TEXT_FIELD_START, TEXT_COUNT = 10 + TEXT_FIELD_START};

	   CShopWnd();
	   ~CShopWnd();

	   void init(int _x, int _y, CPlayer* pb, CBackpackWnd *pBackpackWnd, GP::NetStream *pNetStream);

      void setTitle(std::string title);
      void setSellItem(std::vector<int> vSellItem);
      void clear();

	   // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
	   /* virtual */ void onLCommand(int btnID);
	   /* virtual */ void onRCommand(int btnID);
	   /* virtual */ void show(bool bShow);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ bool isButtonClose();
      /* virtual */ void setPosition(int _x, int _y);
   #ifdef _GAMEENGINE_3D_
	   /* virtual */ void onDrag();
	   /* virtual */ void setZOrder(int order);
   #endif

   private:
	   CPlayer          *m_pPlayer;
      std::vector<int>  m_vSellItem;
      GP::NetStream    *m_pNetStream;
      bool              m_bBtnClose;
      CBackpackWnd     *m_pBackpackWnd;

   #ifdef _GAMEENGINE_3D_	
	    CImageButton    *m_vpBtn[BUTTON_COUNT];
       CTextAreaOgre   *m_vpText[TEXT_COUNT];
       COverlayUI       m_overlay;  //ºÞ²zoverlay
   #elif _GAMEENGINE_2D_
	   CTextButton      *m_vpBtn[BUTTON_COUNT];
       CTextArea       *m_vpText[TEXT_COUNT];
   #endif
};

#endif
