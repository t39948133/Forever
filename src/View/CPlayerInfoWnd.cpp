#include "CPlayerInfoWnd.h"
#include "CPacketEquipData.h"

#ifdef _GAMEENGINE_3D_
#include <OgreTextAreaOverlayElement.h>
#endif  // #ifdef _GAMEENGINE_3D_

CPlayerInfoWnd::CPlayerInfoWnd()
{
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++) {
      m_vpTextName[i] = NULL;
      m_vpText[i] = NULL;
   }
}

CPlayerInfoWnd::~CPlayerInfoWnd()
{
   if(m_pPlayer != NULL) {
      m_pPlayer->removeAdvAttrEventListener(this);
      m_pPlayer->removePlayerAttrEventListener(this);
      m_pPlayer->removePlayerEquipEventListener(this);
   }

   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpTextName[i] != NULL) {
         delete m_vpTextName[i];
         m_vpTextName[i] = NULL;
      }

      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
      }
   }
}

void CPlayerInfoWnd::init (int _x, int _y, CPlayer *pPlr, GP::NetStream *pNetStream)
{
	m_pPlayer = pPlr;
   m_pNetStream = pNetStream;
   if(m_pPlayer != NULL) {
      m_pPlayer->addPlayerAttrEventListener(this);
      m_pPlayer->addAdvAttrEventListener(this);
      m_pPlayer->addPlayerEquipEventListener(this);
   }
   
   x = _x;
   y = _y;
   w = 408;
   h = 406;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
	m_overlay.setBackImage("UI/BG/PlayerInfoWnd");

   for(int i = 0; i < BUTTON_COUNT; i++) {
		m_vpBtn[i] = new CImageButton();

      switch(i) {
         case BUTTON_MAINHAND:
            m_vpBtn[i]->init(&m_overlay, 17, 127, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_OFFHAND:
            m_vpBtn[i]->init(&m_overlay, 191, 127, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_CHEST:
            m_vpBtn[i]->init(&m_overlay, 17, 217, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_LEGS:
            m_vpBtn[i]->init(&m_overlay, 17, 261, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_SHOULDER:
            m_vpBtn[i]->init(&m_overlay, 191, 217, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_GLOVE:
            m_vpBtn[i]->init(&m_overlay, 191, 261, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_BOOT:
            m_vpBtn[i]->init(&m_overlay, 17, 350, ICON_SIZE, ICON_SIZE, i);
            break;
      }

		addChild(m_vpBtn[i]);
	}

	//視窗基本資訊
	for(int i = 0; i <= TEXT_MP; i++) {
      switch(i) {
         case TEXT_TITLE:
            m_vpText[i] = new CTextAreaOgre();
            m_vpText[i]->init(&m_overlay, 0, 0, w, 25);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
			   m_vpText[i]->setText("角色資訊", 1, 1, 1);
            addChild(m_vpText[i]);
            break;

         case TEXT_NAME:
            m_vpText[i] = new CTextAreaOgre();
            m_vpText[i]->init(&m_overlay, 10, 30, 185, 20);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            addChild(m_vpText[i]);
            break;

         case TEXT_LEVEL:
            m_vpText[i] = new CTextAreaOgre();
            m_vpText[i]->init(&m_overlay, 200, 30, 198, 20);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            addChild(m_vpText[i]);
            break;

         case TEXT_HP:
            m_vpTextName[i] = new CTextAreaOgre();
            m_vpTextName[i]->init(&m_overlay, 245, 62, 75, 26);
            m_vpTextName[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            m_vpTextName[i]->setText("生命", 1, 1, 1);
            addChild(m_vpTextName[i]);

            m_vpText[i] = new CTextAreaOgre();
            m_vpText[i]->init(&m_overlay, 321, 62, 75, 26);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_RIGHT);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            addChild(m_vpText[i]);
            break;

         case TEXT_MP:
            m_vpTextName[i] = new CTextAreaOgre();
            m_vpTextName[i]->init(&m_overlay, 245, 88, 75, 26);
            m_vpTextName[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            m_vpTextName[i]->setText("精神", 1, 1, 1);
            addChild(m_vpTextName[i]);

            m_vpText[i] = new CTextAreaOgre();
            m_vpText[i]->init(&m_overlay, 321, 88, 75, 25);
            m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_RIGHT);
            m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            addChild(m_vpText[i]);
            break;
      }
	}
		
   //人物屬性資訊
	for(int i = TEXT_ATK; i < TEXT_COUNT; i++) {
		m_vpTextName[i] = new CTextAreaOgre();
		m_vpTextName[i]->init(&m_overlay, 245, (i - TEXT_ATK) * 19 + 123, 75, 19);
      switch(i) {
         case TEXT_ATK:
            m_vpTextName[i]->setText("物理攻擊力", 1, 1, 1);
            break;

         case TEXT_DEF:
            m_vpTextName[i]->setText("物理防禦力", 1, 1, 1);
            break;

         case TEXT_HIT:
            m_vpTextName[i]->setText("物理命中", 1, 1, 1);
            break;

         case TEXT_CRI:
            m_vpTextName[i]->setText("物理暴擊", 1, 1, 1);
            break;

         case TEXT_MATK:
            m_vpTextName[i]->setText("魔法攻擊力", 1, 1, 1);
            break;

         case TEXT_MDEF:
            m_vpTextName[i]->setText("魔法防禦力", 1, 1, 1);
            break;

         case TEXT_MHIT:
            m_vpTextName[i]->setText("魔法命中", 1, 1, 1);
            break;

         case TEXT_MCRI:
            m_vpTextName[i]->setText("魔法暴擊", 1, 1, 1);
            break;

         case TEXT_SDEF:
            m_vpTextName[i]->setText("盾牌防禦", 1, 1, 1);
            break;

         case TEXT_WDEF:
            m_vpTextName[i]->setText("武器防禦", 1, 1, 1);
            break;

         case TEXT_FLEE:
            m_vpTextName[i]->setText("迴避", 1, 1, 1);
            break;

         case TEXT_MOVE:
            m_vpTextName[i]->setText("移動速度", 1, 1, 1);
            break;

         case TEXT_ATKSPEED:
            m_vpTextName[i]->setText("攻擊速度", 1, 1, 1);
            break;

         case TEXT_CASTING:
            m_vpTextName[i]->setText("施法速度", 1, 1, 1);
            break;
      }
		addChild(m_vpTextName[i]);

      m_vpText[i] = new CTextAreaOgre();
      m_vpText[i]->init(&m_overlay, 321, (i - TEXT_ATK) * 19 + 123, 75, 19);
      m_vpText[i]->setHorizontalAlignment(CTextAreaOgre::H_RIGHT);
      m_vpText[i]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
		addChild(m_vpText[i]);
	}

#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
		m_vpBtn[i] = new CTextButton();

      switch(i) {
         case BUTTON_MAINHAND:
            m_vpBtn[i]->init(17, 127, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_OFFHAND:
            m_vpBtn[i]->init(191, 127, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_CHEST:
            m_vpBtn[i]->init(17, 217, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_LEGS:
            m_vpBtn[i]->init(17, 261, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_SHOULDER:
            m_vpBtn[i]->init(191, 217, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_GLOVE:
            m_vpBtn[i]->init(191, 261, ICON_SIZE, ICON_SIZE, i);
            break;

         case BUTTON_BOOT:
            m_vpBtn[i]->init(17, 350, ICON_SIZE, ICON_SIZE, i);
            break;
      }
		
		addChild(m_vpBtn[i]);
	}

   //視窗基本資訊
	for(int i = 0; i <= TEXT_MP; i++) {
      switch(i) {
         case TEXT_TITLE:
            m_vpText[i] = new CTextArea();
            m_vpText[i]->init(0, 0, w, 25);
			   m_vpText[i]->setText("角色資訊", 1, 1, 1);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
            addChild(m_vpText[i]);
            break;

         case TEXT_NAME:
            m_vpText[i] = new CTextArea();
            m_vpText[i]->init(10, 30, 185, 20);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
            addChild(m_vpText[i]);
            break;

         case TEXT_LEVEL:
            m_vpText[i] = new CTextArea();
            m_vpText[i]->init(200, 30, 198, 20);
            m_vpText[i]->setAlignment(CTextArea::CENTER);
            addChild(m_vpText[i]);
            break;

         case TEXT_HP:
            m_vpTextName[i] = new CTextArea();
            m_vpTextName[i]->init(245, 62, 75, 26);
            m_vpTextName[i]->setText("生命", 1, 1, 1);
            addChild(m_vpTextName[i]);

            m_vpText[i] = new CTextArea();
		      m_vpText[i]->init(321, 62, 75, 26);
            m_vpText[i]->setAlignment(CTextArea::RIGHT);
            addChild(m_vpText[i]);
            break;

         case TEXT_MP:
            m_vpTextName[i] = new CTextArea();
            m_vpTextName[i]->init(245, 88, 75, 26);
            m_vpTextName[i]->setText("精神", 1, 1, 1);
            addChild(m_vpTextName[i]);

            m_vpText[i] = new CTextArea();
            m_vpText[i]->init(321, 88, 75, 26);
            m_vpText[i]->setAlignment(CTextArea::RIGHT);
            addChild(m_vpText[i]);
            break;
      }
	}

   for(int i = TEXT_ATK; i < TEXT_COUNT; i++) {
		m_vpTextName[i] = new CTextArea();
		m_vpTextName[i]->init(245, (i - TEXT_ATK) * 19 + 123, 75, 19);
      switch(i) {
         case TEXT_ATK:
            m_vpTextName[i]->setText("物理攻擊力", 1, 1, 1);
            break;

         case TEXT_DEF:
            m_vpTextName[i]->setText("物理防禦力", 1, 1, 1);
            break;

         case TEXT_HIT:
            m_vpTextName[i]->setText("物理命中", 1, 1, 1);
            break;

         case TEXT_CRI:
            m_vpTextName[i]->setText("物理暴擊", 1, 1, 1);
            break;

         case TEXT_MATK:
            m_vpTextName[i]->setText("魔法攻擊力", 1, 1, 1);
            break;

         case TEXT_MDEF:
            m_vpTextName[i]->setText("魔法防禦力", 1, 1, 1);
            break;

         case TEXT_MHIT:
            m_vpTextName[i]->setText("魔法命中", 1, 1, 1);
            break;

         case TEXT_MCRI:
            m_vpTextName[i]->setText("魔法暴擊", 1, 1, 1);
            break;

         case TEXT_SDEF:
            m_vpTextName[i]->setText("盾牌防禦", 1, 1, 1);
            break;

         case TEXT_WDEF:
            m_vpTextName[i]->setText("武器防禦", 1, 1, 1);
            break;

         case TEXT_FLEE:
            m_vpTextName[i]->setText("迴避", 1, 1, 1);
            break;

         case TEXT_MOVE:
            m_vpTextName[i]->setText("移動速度", 1, 1, 1);
            break;

         case TEXT_ATKSPEED:
            m_vpTextName[i]->setText("攻擊速度", 1, 1, 1);
            break;

         case TEXT_CASTING:
            m_vpTextName[i]->setText("施法速度", 1, 1, 1);
            break;
      }
		addChild(m_vpTextName[i]);

      m_vpText[i] = new CTextArea();
		m_vpText[i]->init(321, (i - TEXT_ATK) * 19 + 123, 75, 19);
      m_vpText[i]->setAlignment(CTextArea::RIGHT);
		addChild(m_vpText[i]);
	}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   updateAdvAttr(m_pPlayer);
   updatePlayerAttr(m_pPlayer);
   
   // 裝備欄清空
   updatePlayerEquip(m_pPlayer, MAIN_HAND, -1);
   updatePlayerEquip(m_pPlayer, OFF_HAND, -1);
   updatePlayerEquip(m_pPlayer, CHEST, -1);
   updatePlayerEquip(m_pPlayer, LEGS, -1);
   updatePlayerEquip(m_pPlayer, SHOULDER, -1);
   updatePlayerEquip(m_pPlayer, GLOVE, -1);
   updatePlayerEquip(m_pPlayer, BOOT, -1);

   // 顯示玩家裝備
   std::map<EquipSlot, int> vtEquip = m_pPlayer->getEquip();
   std::map<EquipSlot, int>::iterator it = vtEquip.begin();
   while(it != vtEquip.end()) {
      updatePlayerEquip(m_pPlayer, it->first, it->second);
      it++;
   }

   show(false);
}

bool CPlayerInfoWnd::canDrag (int tx, int ty)
{
	return ty < 25;
}

void CPlayerInfoWnd::onRCommand (int btnID)
{
   CPacketEquipData packet;

   switch(btnID) {
      case BUTTON_MAINHAND:   // 主手武器
         packet.pack(m_pPlayer, MAIN_HAND, -1);
         break;

      case BUTTON_OFFHAND:   // 副手武器
         packet.pack(m_pPlayer, OFF_HAND, -1);
         break;

      case BUTTON_CHEST:   // 上衣
         packet.pack(m_pPlayer, CHEST, -1);
         break;

      case BUTTON_SHOULDER:   // 肩膀部位
         packet.pack(m_pPlayer, SHOULDER, -1);
         break;

      case BUTTON_LEGS:   // 褲子
         packet.pack(m_pPlayer, LEGS, -1);
         break;

      case BUTTON_GLOVE:   // 手套部位
         packet.pack(m_pPlayer, GLOVE, -1);
         break;

      case BUTTON_BOOT:   // 鞋子
         packet.pack(m_pPlayer, BOOT, -1);
         break;
   }

   m_pNetStream->send(&packet, sizeof(packet));
}

WindowClassType CPlayerInfoWnd::getClassType()
{
   return WND_PLAYERINFO;
}

void CPlayerInfoWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

void CPlayerInfoWnd::onDrag()
{   
#ifdef _GAMEENGINE_3D_
   m_overlay.setPosition(x, y);
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CPlayerInfoWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

void CPlayerInfoWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
   //更新基本資訊
   char buf[50];
   memset(buf, 0, sizeof(buf));
   m_vpText[TEXT_NAME]->setText(pUnitObject->getName(), 1, 1, 1);
	   

   // 更新屬性資料
   AdvancedAttribute advAttr = pUnitObject->getAdvAttr();
   for(int i = TEXT_HP; i < TEXT_COUNT; i++) {
	   char buf[50];
      memset(buf, 0, sizeof(buf));

	   if(i == TEXT_HP)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iHP);  
	   else if(i == TEXT_MP)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iMP);   
	   else if(i == TEXT_ATK)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iATK);  
	   else if(i == TEXT_DEF)
		   sprintf_s(buf, sizeof (buf), "%5d", advAttr.iDEF);  
	   else if(i == TEXT_HIT)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iHIT);  
	   else if(i == TEXT_CRI)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iCRI);  
	   else if(i == TEXT_MATK)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iMATK);  
	   else if(i == TEXT_MDEF)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iMDEF);  
	   else if(i == TEXT_MHIT)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iMHIT);  
	   else if(i == TEXT_MCRI)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iMCRI);  
	   else if(i == TEXT_SDEF)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iSDEF);  
	   else if(i == TEXT_WDEF)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iWDEF);  
	   else if(i == TEXT_FLEE)
         sprintf_s(buf, sizeof (buf), "%5d", advAttr.iFlee);  
	   else if(i == TEXT_MOVE)
         sprintf_s(buf, sizeof (buf), "%5.1f", advAttr.fMove);  
	   else if(i == TEXT_ATKSPEED)
         sprintf_s(buf, sizeof (buf), "%5.1f", advAttr.fATKSpeed);  
	   else if(i == TEXT_CASTING)
         sprintf_s(buf, sizeof (buf), "%5.1f", advAttr.fCasting);  
	   
	   m_vpText[i]->setText(buf, 1, 1, 1);
   }
}

void CPlayerInfoWnd::updatePlayerAttr(CPlayer *pPlayer)
{
   //更新基本資訊
   char buf[50];
   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "等級  %3d", pPlayer->getLevel());
	m_vpText[TEXT_LEVEL]->setText(buf, 1, 1, 1);
}

void CPlayerInfoWnd::updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId)
{
#ifdef _GAMEENGINE_3D_
   //更新裝備欄
   switch(equipSlot) {
      case MAIN_HAND: {
         if(itemId == -1)
            m_vpBtn[BUTTON_MAINHAND]->setImage("UI/Icon/MainHandSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_MAINHAND]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case OFF_HAND: {
         if(itemId == -1)
            m_vpBtn[BUTTON_OFFHAND]->setImage("UI/Icon/OffHandSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_OFFHAND]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case CHEST: {
         if(itemId == -1)
            m_vpBtn[BUTTON_CHEST]->setImage("UI/Icon/ChestSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_CHEST]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case LEGS: {
         if(itemId == -1)
            m_vpBtn[BUTTON_LEGS]->setImage("UI/Icon/LegsSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_LEGS]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case SHOULDER: {
         if(itemId == -1)
            m_vpBtn[BUTTON_SHOULDER]->setImage("UI/Icon/ShoulderSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_SHOULDER]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case GLOVE: {
         if(itemId == -1)
            m_vpBtn[BUTTON_GLOVE]->setImage("UI/Icon/GloveSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_GLOVE]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case BOOT: {
         if(itemId == -1)
            m_vpBtn[BUTTON_BOOT]->setImage("UI/Icon/BootSlot");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_BOOT]->setImage(pItemInfo->geticonName());
         }
         break;
	   }
   }
#elif _GAMEENGINE_2D_
   //更新裝備欄
   switch(equipSlot) {
      case MAIN_HAND: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_MAINHAND]->str = "主手武器";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_MAINHAND]->str = pItemInfo->getName();
         }
         break;
	   }

      case OFF_HAND: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_OFFHAND]->str = "副手武器";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_OFFHAND]->str = pItemInfo->getName();
         }
         break;
	   }

      case CHEST: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_CHEST]->str = "上衣";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_CHEST]->str = pItemInfo->getName();
         }
         break;
	   }

	   case SHOULDER: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_SHOULDER]->str = "肩甲";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_SHOULDER]->str = pItemInfo->getName();
         }
         break;
	   }

      case LEGS: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_LEGS]->str = "褲子";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_LEGS]->str = pItemInfo->getName();
         }
         break;
	   }

      case GLOVE: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_GLOVE]->str = "手套";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_GLOVE]->str = pItemInfo->getName();
         }
         break;
	   }

      case BOOT: {
         if(itemId == -1)
		      m_vpBtn[BUTTON_BOOT]->str = "鞋子";
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[BUTTON_BOOT]->str = pItemInfo->getName();
         }
         break;
	   }
   }
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
}