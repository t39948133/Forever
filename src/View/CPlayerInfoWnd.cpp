#include "CPlayerInfoWnd.h"

void CPlayerInfoWnd::init (int _x, int _y, CPlayer* pPlr)
{
   bVisible = false;
	pPlayer = pPlr ;
   
   x = _x;
   y = _y;
   w = CELL_SIZE * 24;
   h = CELL_SIZE * 20;

#ifdef _GAMEENGINE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.getOverlay ()->hide () ;
	overlayUI.setImage ("KAMEN-stup") ;

for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new ImageButton ;

		if (i == 0)
		{//以下為裝備欄
			vpBtn[i]->init (overlayUI, 0, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 1)
		{
			vpBtn[i]->init (overlayUI, 0, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 2)
		{
			vpBtn[i]->init (overlayUI, 0, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 3)
		{
			vpBtn[i]->init (overlayUI, CELL_SIZE*11, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 4)
		{
			vpBtn[i]->init (overlayUI, CELL_SIZE*11, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 5)
		{
			vpBtn[i]->init (overlayUI, CELL_SIZE*11, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 6)
		{
			vpBtn[i]->init (overlayUI, CELL_SIZE*6-10, CELL_SIZE*17, CELL_SIZE*3, CELL_SIZE*3, i) ;
			vpBtn[i]->setImage ("ogreborder") ;
		}else if (i == 7)
		{//UI名稱(主角資訊)
			vpBtn[i]->init (overlayUI, 0, 0, w, CELL_SIZE, i) ;
		}else if (i == 8)
		{//主角名稱
			vpBtn[i]->init (overlayUI, 0, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 9)
		{//等級及經驗值
			vpBtn[i]->init (overlayUI, w/2, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 10)
		{//屬性
			vpBtn[i]->init (overlayUI, CELL_SIZE*14, CELL_SIZE*2, CELL_SIZE*10, CELL_SIZE*18, i) ;
		}else if (i == 11)
		{//主角圖
			vpBtn[i]->init (overlayUI, CELL_SIZE*3, CELL_SIZE*2, CELL_SIZE*8, CELL_SIZE*15, i) ;
			vpBtn[i]->setImage ("tusk") ;
		}
		addChild (vpBtn[i]) ;
	}

	//視窗基本資訊
	for (int i = 0; i<3; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;
		if (i == 0)
		{
			vpText[i]->init (overlayUI, w/2-30, 0, w, CELL_SIZE) ;
			vpText[i]->setText ("角色資訊", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (overlayUI, w/4-30, CELL_SIZE, w/2, CELL_SIZE) ;
			vpText[i]->setText ("主角名稱", 1, 1, 1) ;
		}else if (i == 2)
		{
			vpText[i]->init (overlayUI, w*1/2+40, CELL_SIZE, w/2, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "等級 %dLV/經驗值    %d", pPlayer->data.m_level, pPlayer->data.m_xp) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*(i-1), CELL_SIZE*10, CELL_SIZE) ;
		char buf[256] ;		
		if (i == 3)
		{
			sprintf_s (buf, sizeof (buf), "生命力                  %d", pPlayer->data.iHP) ;
		}else if (i == 4)
		{
			sprintf_s (buf, sizeof (buf), "精神力                  %d", pPlayer->data.iMP) ;
		}else if (i == 5)
		{
			sprintf_s (buf, sizeof (buf), "最大生命力          %d", pPlayer->data.iHPMax) ;
		}else if (i == 6)
		{
			sprintf_s (buf, sizeof (buf), "最大精神力          %d", pPlayer->data.iMPMax) ;
		}else if (i == 7)
		{
			sprintf_s (buf, sizeof (buf), "物理攻擊力          %d", pPlayer->data.iATK) ;
		}else if (i == 8)
		{
			sprintf_s (buf, sizeof (buf), "物理防禦力          %d", pPlayer->data.iDEF) ;
		}else if (i == 9)
		{
			sprintf_s (buf, sizeof (buf), "物理命中率          %d", pPlayer->data.iHIT) ;
		}else if (i == 10)
		{
			sprintf_s (buf, sizeof (buf), "物理暴擊率          %d", pPlayer->data.iCRI) ;
		}else if (i == 11)
		{
			sprintf_s (buf, sizeof (buf), "魔法攻擊力          %d", pPlayer->data.iMATK) ;
		}else if (i == 12)
		{
			sprintf_s (buf, sizeof (buf), "魔法防禦力          %d", pPlayer->data.iMDEF) ;
		}else if (i == 13)
		{
			sprintf_s (buf, sizeof (buf), "魔法命中率          %d", pPlayer->data.iMHIT) ;
		}else if (i == 14)
		{
			sprintf_s (buf, sizeof (buf), "魔法暴擊率          %d", pPlayer->data.iMCRI) ;
		}else if (i == 15)
		{
			sprintf_s (buf, sizeof (buf), "盾牌防禦力          %d", pPlayer->data.iSDEF) ;
		}else if (i == 16)
		{
			sprintf_s (buf, sizeof (buf), "武器防禦力          %d", pPlayer->data.iWDEF) ;
		}else if (i == 17)
		{
			sprintf_s (buf, sizeof (buf), "迴避率                  %d", pPlayer->data.iFlee) ;
		}else if (i == 18)
		{
			sprintf_s (buf, sizeof (buf), "移動速度              %.1f", pPlayer->data.fMove) ;
		}else if (i == 19)
		{
			sprintf_s (buf, sizeof (buf), "攻擊速度              %.1f", pPlayer->data.fATKSpeed) ;
		}else if (i == 20)
		{
			sprintf_s (buf, sizeof (buf), "施展速度              %.1f", pPlayer->data.fCasting) ;
		}
		vpText[i]->setText (buf, 1, 1, 1) ;
		addChild (vpText[i]) ;
	}

#elif _GAMEENGINE_2D_
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new CTextButton ;

		if (i == 0)
		{//以下為裝備欄
			vpBtn[i]->init (0, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 1)
		{
			vpBtn[i]->init (0, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 2)
		{
			vpBtn[i]->init (0, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 3)
		{
			vpBtn[i]->init (CELL_SIZE*11, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 4)
		{
			vpBtn[i]->init (CELL_SIZE*11, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 5)
		{
			vpBtn[i]->init (CELL_SIZE*11, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 6)
		{
			vpBtn[i]->init (CELL_SIZE*6-10, CELL_SIZE*17, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 7)
		{//UI名稱(主角資訊)
			vpBtn[i]->init (0, 0, w, CELL_SIZE, i) ;
		}else if (i == 8)
		{//主角名稱
			vpBtn[i]->init (0, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 9)
		{//等級及經驗值
			vpBtn[i]->init (w/2, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 10)
		{//屬性
			vpBtn[i]->init (CELL_SIZE*14, CELL_SIZE*2, CELL_SIZE*10, CELL_SIZE*18, i) ;
		}else if (i == 11)
		{//主角圖
			vpBtn[i]->init (CELL_SIZE*3, CELL_SIZE*2, CELL_SIZE*8, CELL_SIZE*15, i) ;
		}
		addChild (vpBtn[i]) ;
	}

	//視窗基本資訊
	for (int i = 0; i<3; i++)
	{
		vpText[i] = new CTextArea ;
		if (i == 0)
		{
			vpText[i]->init (w/2-30, 0, w, CELL_SIZE) ;
			vpText[i]->setText ("角色資訊", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (w/4-30, CELL_SIZE, w/2, CELL_SIZE) ;
		}else if (i == 2)
		{
			vpText[i]->init (w*1/2+40, CELL_SIZE, w/2, CELL_SIZE) ;
		}
		addChild (vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		vpText[i] = new CTextArea ;
		vpText[i]->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*(i-1), CELL_SIZE*10, CELL_SIZE) ;
		addChild (vpText[i]) ;
	}
#endif
}

bool CPlayerInfoWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CPlayerInfoWnd::onRCommand (int id)
{
   switch(id) {
      case 0: {  // 肩膀部位
         pPlayer->shedEquip(SHOULDER);
         break;
      }

      case 1: {  // 手套部位
         pPlayer->shedEquip(GLOVE);
         break;
      }

      case 2: {  // 主手武器
         pPlayer->shedEquip(MAIN_HAND);
         break;
      }

      case 3: {  // 上衣
         pPlayer->shedEquip(CHEST);
         break;
      }

      case 4: {  // 褲子
         pPlayer->shedEquip(LEGS);
         break;
      }

      case 5: {  // 副手武器
         pPlayer->shedEquip(OFF_HAND);
         break;
      }

      case 6: {  // 鞋子
         pPlayer->shedEquip(BOOT);
         break;
      }
   }

	/*for (int i = 0; i<6; i++)
	{
		if (i == id)
		{
			if (playerInfo[i].itemID != -1)
			{
				
				playerInfo[i].itemID = -1 ;
#ifdef _GAMEENGINE_3D_
				vpBtn[i]->setImage ("ogreborder") ;
#elif _GAMEENGINE_2D_
				vpBtn[i]->str = "" ;
#endif
			break ;
			}		
		}
	}*/
}

/*void CPlayerInfoWnd::wearEquip (int _itemID)//道具編號 
{
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		ItemInfo* pInfo = Item::getInfo (_itemID) ;
		if (pInfo != NULL)
		{			
			playerInfo[i].itemID = _itemID ;
			if (pInfo->equipPos == ItemInfo::EQUIP_WEAPON && i == PlayerInfoWnd::BUTTON_WEAPON)
			{				
#ifdef _GAMEENGINE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#elif _GAMEENGINE_2D_
					vpBtn[i]->str = pInfo->name ;
#endif
					break ;							
			}else if (pInfo->equipPos == ItemInfo::EQUIP_SHIELD && i == PlayerInfoWnd::BUTTON_SHIELD)
			{				
#ifdef _GAMEENGINE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#elif _GAMEENGINE_2D_
					vpBtn[i]->str = pInfo->name ;
#endif
					break ;				
			}			
		}
	}
}*/

#ifdef _GAMEENGINE_3D_
void CPlayerInfoWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void CPlayerInfoWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void CPlayerInfoWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

// Add by Darren on 2013/01/07 {
WindowClassType CPlayerInfoWnd::getClassType()
{
   return WND_PLAYERINFO;
}

#ifdef _GAMEENGINE_2D_
void CPlayerInfoWnd::draw(HDC hdc, int ox, int oy)
{
   //更新裝備欄
   for (int i = 0; i<BUTTON_COUNT; i++)
	{
		if (i == 0)
		{
         int itemID = pPlayer->getEquip(SHOULDER);
         if(itemID == -1)
			   vpBtn[i]->str = "肩甲" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}else if (i == 1)
		{
         int itemID = pPlayer->getEquip(GLOVE);
         if(itemID == -1)
			   vpBtn[i]->str = "手套" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}else if (i == 2)
		{
         int itemID = pPlayer->getEquip(MAIN_HAND);
         if(itemID == -1)
			   vpBtn[i]->str = "主手武器" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}else if (i == 3)
		{
         int itemID = pPlayer->getEquip(CHEST);
         if(itemID == -1)
			   vpBtn[i]->str = "衣服" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}else if (i == 4)
		{
         int itemID = pPlayer->getEquip(LEGS);
         if(itemID == -1)
			   vpBtn[i]->str = "褲子" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}else if (i == 5)
		{
         int itemID = pPlayer->getEquip(OFF_HAND);
         if(itemID == -1)
			   vpBtn[i]->str = "副手武器" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}else if (i == 6)
		{
         int itemID = pPlayer->getEquip(BOOT);
         if(itemID == -1)
			   vpBtn[i]->str = "鞋子" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemID);
            vpBtn[i]->str = pItemInfo->getName();
         }
		}
	}

   //更新基本資訊
	for (int i = 1; i<3; i++)
	{
		char buf[256] ;
		if (i == 1)
		{
         vpText[i]->setText (pPlayer->getName(), 1, 1, 1) ;
		}else if (i == 2)
		{
         sprintf_s (buf, sizeof (buf), "等級 %dLV/經驗值    %d", pPlayer->getLevel(), pPlayer->getXP()) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
	}

   // 更新屬性資料
   AdvancedAttribute advAttr = pPlayer->getAdvAttr();
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		char buf[256] ;		
		if (i == 3)
		{
         sprintf_s (buf, sizeof (buf), "生命力                  %d", advAttr.iHP) ;  
		}else if (i == 4)
		{
         sprintf_s (buf, sizeof (buf), "精神力                  %d", advAttr.iMP) ;  
		}else if (i == 5)
		{
         sprintf_s (buf, sizeof (buf), "最大生命力          %d", advAttr.iHPMax) ;  
		}else if (i == 6)
		{
         sprintf_s (buf, sizeof (buf), "最大精神力          %d", advAttr.iMPMax) ;  
		}else if (i == 7)
		{
         sprintf_s (buf, sizeof (buf), "物理攻擊力          %d", advAttr.iATK) ;  
		}else if (i == 8)
		{
			sprintf_s (buf, sizeof (buf), "物理防禦力          %d", advAttr.iDEF) ;  
		}else if (i == 9)
		{
         sprintf_s (buf, sizeof (buf), "物理命中率          %d", advAttr.iHIT) ;  
		}else if (i == 10)
		{
         sprintf_s (buf, sizeof (buf), "物理暴擊率          %d", advAttr.iCRI) ;  
		}else if (i == 11)
		{
         sprintf_s (buf, sizeof (buf), "魔法攻擊力          %d", advAttr.iMATK) ;  
		}else if (i == 12)
		{
         sprintf_s (buf, sizeof (buf), "魔法防禦力          %d", advAttr.iMDEF) ;  
		}else if (i == 13)
		{
         sprintf_s (buf, sizeof (buf), "魔法命中率          %d", advAttr.iMHIT) ;  
		}else if (i == 14)
		{
         sprintf_s (buf, sizeof (buf), "魔法暴擊率          %d", advAttr.iMCRI) ;  
		}else if (i == 15)
		{
         sprintf_s (buf, sizeof (buf), "盾牌防禦力          %d", advAttr.iSDEF) ;  
		}else if (i == 16)
		{
         sprintf_s (buf, sizeof (buf), "武器防禦力          %d", advAttr.iWDEF) ;  
		}else if (i == 17)
		{
         sprintf_s (buf, sizeof (buf), "迴避率                  %d", advAttr.iFlee) ;  
		}else if (i == 18)
		{
         sprintf_s (buf, sizeof (buf), "移動速度              %.1f", advAttr.fMove) ;  
		}else if (i == 19)
		{
         sprintf_s (buf, sizeof (buf), "攻擊速度              %.1f", advAttr.fATKSpeed) ;  
		}else if (i == 20)
		{
         sprintf_s (buf, sizeof (buf), "施展速度              %.1f", advAttr.fCasting) ;  
		}
		vpText[i]->setText (buf, 1, 1, 1) ;
	}

   CWindow::draw(hdc, ox, oy);
}
#endif
// } Add by Darren Chen on 2013/01/07