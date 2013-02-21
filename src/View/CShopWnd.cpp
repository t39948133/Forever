#include "CShopWnd.h"
#include "CItem.h"

CShopWnd::CShopWnd()
{
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

void CShopWnd::init (int _x, int _y, CPlayer* pb)
{
	m_pPlayer = pb ;
	x = _x ;
	y = _y ;
	w = 410 ;
	h = 351 ;	

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
    m_overlay.setBackImage("shop");	
	  
	//icon欄
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			m_vpBtn[i*2+m] = new CImageButton ;
			m_vpBtn[i*2+m]->init (&m_overlay, m*205+4, i*60+55, ICON_SIZE, ICON_SIZE, i*2+m) ;
			CItemInfo *pItemInfo = CItem::getInfo (i*2+m) ;
			m_vpBtn[i*2+m]->setImage (pItemInfo->geticonName ()) ;
			addChild (m_vpBtn[i*2+m]) ;
		}

	//道具內容
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			m_vpText[i*2+m] = new CTextAreaOgre ;
			m_vpText[i*2+m]->init (&m_overlay, m*205+64, i*60+55, 180, 60) ;
			CItemInfo *pItemInfo = CItem::getInfo (i*2+m) ;
			m_vpText[i*2+m]->setText (pItemInfo->getName (), 0, 0, 1) ;
			addChild (m_vpText[i*2+m]) ;
		}

	//close button
	m_vpBtn[CLOSE_BUTTON] = new CImageButton ;
	m_vpBtn[CLOSE_BUTTON]->init (&m_overlay, 390, 5, 20, 20, CLOSE_BUTTON) ;
	m_vpBtn[CLOSE_BUTTON]->setImage ("x") ;
	addChild (m_vpBtn[CLOSE_BUTTON]) ;

	//介面名稱
	m_vpText[SHOP_TEXT] = new CTextAreaOgre ;
	m_vpText[SHOP_TEXT]->init (&m_overlay, 185, 15, 40, 20) ;
	m_vpText[SHOP_TEXT]->setText ("商店", 1, 1, 1) ;
	addChild (m_vpText[SHOP_TEXT]) ;

		
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

bool CShopWnd::canDrag (int tx, int ty)
{
	return ty < 55 && tx < 380;
}

void CShopWnd::onLCommand(int btnID)
{
	if (btnID == CLOSE_BUTTON)
	{
		CWindow::show(false);
#ifdef _GAMEENGINE_3D_
		m_overlay.getOverlay()->hide();
#endif
	}
}

void CShopWnd::onRCommand(int btnID)
{
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
