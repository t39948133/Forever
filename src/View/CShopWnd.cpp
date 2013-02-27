#include "CShopWnd.h"
#include "CItem.h"
#include "CPacketBuyItem.h"

CShopWnd::CShopWnd()
{
   m_bBtnClose = false;

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

CShopWnd::~CShopWnd()
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

void CShopWnd::init (int _x, int _y, CPlayer* pb, CBackpackWnd *pBackpackWnd, GP::NetStream *pNetStream)
{
	m_pPlayer = pb;
   m_pNetStream = pNetStream;
   m_pBackpackWnd = pBackpackWnd;
	x = _x;
	y = _y;
#ifdef _GAMEENGINE_3D_
	w = 408;
	h = 316;
#elif _GAMEENGINE_2D_
   w = 410;
	h = 351;
#endif

#ifdef _GAMEENGINE_3D_
   m_overlay.init(x, y, w, h);
   m_overlay.setBackImage("UI/BG/ShopWnd");	

   m_vpBtn[BUTTON_CLOSE] = new CImageButton();
	m_vpBtn[BUTTON_CLOSE]->init(&m_overlay, 383, 0, 25, 25, BUTTON_CLOSE);
   m_vpBtn[BUTTON_CLOSE]->setImage("UI/CloseButton");
	addChild(m_vpBtn[BUTTON_CLOSE]);

   int offsetX = 0;
   for(int i = BUTTON_ICON_START; i < BUTTON_COUNT; ++i) {
      if(i >= (BUTTON_ICON_START + 5))
         offsetX = 193;
		m_vpBtn[i] = new CImageButton();
		m_vpBtn[i]->init(&m_overlay, 13 + offsetX, 57 + ((i - BUTTON_ICON_START) % 5) * ICON_SIZE + 4 * ((i - BUTTON_ICON_START) % 5), ICON_SIZE, ICON_SIZE, i);
		addChild(m_vpBtn[i]);
	}

   for(int i = TEXT_TITLE; i < TEXT_FIELD_START; i++) {
      switch(i) {
         case TEXT_TITLE:
            m_vpText[i] = new CTextAreaOgre();
		      m_vpText[i]->init(&m_overlay, 0, 0, w, 25);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            break;
      }

		addChild(m_vpText[i]);
   }

   offsetX = 0;
   for(int i = TEXT_FIELD_START; i < TEXT_COUNT; ++i) {
      if(i >= (TEXT_FIELD_START + 5))
         offsetX = 193;
		m_vpText[i] = new CTextAreaOgre();
		m_vpText[i]->init(&m_overlay, 59 + offsetX, 59 + ((i - TEXT_FIELD_START) % 5) * 38 + 7 * ((i - TEXT_FIELD_START) % 5), 144, 38);
      m_vpText[i]->setFont(10);
		addChild(m_vpText[i]);
	}
#elif _GAMEENGINE_2D_
	//icon欄
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			m_vpBtn[i*2+m] = new CTextButton ;
			m_vpBtn[i*2+m]->init (m*205+4, i*60+55, ICON_SIZE, ICON_SIZE, i*2+m) ;
			CItemInfo *pItemInfo = CItem::getInfo (i*2+m) ;
			m_vpBtn[i*2+m]->str = pItemInfo->getName () ;
			addChild (m_vpBtn[i*2+m]) ;
		}

	//道具內容
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			m_vpText[i*2+m] = new CTextArea ;
			m_vpText[i*2+m]->init (m*205+64, i*60+55, 180, 60) ;
			CItemInfo *pItemInfo = CItem::getInfo (i*2+m) ;
			m_vpText[i*2+m]->setText (pItemInfo->getName (), 0, 0, 1) ;
			addChild (m_vpText[i*2+m]) ;
		}

	//close button
	m_vpBtn[CLOSE_BUTTON] = new CTextButton ;
	m_vpBtn[CLOSE_BUTTON]->init (390, 5, 20, 20, CLOSE_BUTTON) ;
	m_vpBtn[CLOSE_BUTTON]->str = " X" ;
	addChild (m_vpBtn[CLOSE_BUTTON]) ;

	//介面名稱
	m_vpText[SHOP_TEXT] = new CTextArea ;
	m_vpText[SHOP_TEXT]->init (185, 15, 40, 20) ;
	m_vpText[SHOP_TEXT]->setText ("商店", 1, 1, 1) ;
	addChild (m_vpText[SHOP_TEXT]) ;

#endif
	show(false);
}

void CShopWnd::setTitle(std::string title)
{
   m_vpText[TEXT_TITLE]->setText(title, 1, 1, 1);
}

void CShopWnd::setSellItem(std::vector<int> vSellItem)
{
   m_vSellItem = vSellItem;
   clear();
   for(int i = 0; i < (int)m_vSellItem.size(); ++i) {
      CItemInfo *pItemInfo = CItem::getInfo(m_vSellItem.at(i));
#ifdef _GAMEENGINE_3D_
      m_vpBtn[i + BUTTON_ICON_START]->setImage(pItemInfo->geticonName());
#elif _GAMEENGINE_2D_
      m_vpBtn[i + BUTTON_ICON_START]->str = pItemInfo->getName();
#endif
      char buf[256];
      memset(buf, 0, sizeof(buf));
		sprintf_s(buf, sizeof (buf), "%s\n價格:%d", pItemInfo->getName().c_str(), pItemInfo->getBuyPrice());
		m_vpText[i + TEXT_FIELD_START]->setText(buf, 1, 1, 1);
   }
}

void CShopWnd::clear()
{
   for(int i = BUTTON_ICON_START; i < BUTTON_COUNT; ++i) {
#ifdef _GAMEENGINE_3D_
		m_vpBtn[i]->setImage("");
#elif _GAMEENGINE_2D_
		m_vpBtn[i]->str = "";
#endif
	}

   for(int i = TEXT_FIELD_START; i < TEXT_COUNT; ++i)
      m_vpText[i]->setText("", 1, 1, 1);
}

bool CShopWnd::canDrag (int tx, int ty)
{
   return ty < 25 && tx < 383;
}

void CShopWnd::onLCommand(int btnID)
{
   if(btnID == BUTTON_CLOSE) {
		show(false);
      m_bBtnClose = true;
      m_pBackpackWnd->show(false);
   }
}

void CShopWnd::onRCommand(int btnID)
{
   CPacketBuyItem packet;
   packet.pack(m_pPlayer, m_vSellItem[btnID - BUTTON_ICON_START]);
   m_pNetStream->send(&packet, sizeof(packet));
}

void CShopWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

WindowClassType CShopWnd::getClassType()
{
   return WND_SHOP;
}

bool CShopWnd::isButtonClose()
{
   bool btnClose = m_bBtnClose;
   m_bBtnClose = false;
   return btnClose;
}

void CShopWnd::setPosition(int _x, int _y)
{
   CWindow::setPosition(_x, _y);
   m_overlay.setPosition(_x, _y);
}

#ifdef _GAMEENGINE_3D_
void CShopWnd::onDrag()
{
   m_overlay.setPosition(x, y);
}

void CShopWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_
