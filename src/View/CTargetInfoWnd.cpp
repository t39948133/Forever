#include "CTargetInfoWnd.h"

void CTargetInfoWnd::init(int _x, int _y, CScene *pScene, CPlayer *pPlayer)
{
   m_pPlayer = pPlayer;
   m_pScene = pScene;
   m_targetUID = -1;

   x = _x;
	y = _y;
	w = 300;
	h = 60;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);

	m_pBtn = new CImageButton ;
	m_pBtn->init (m_overlay, 50, 15, 200, 15, 0) ;
	m_pBtn->setImage ("ogreborder") ;
	addChild (m_pBtn) ;

	m_pText = new CTextAreaOgre ;
	m_pText->init (overlayUI, 50, 35, w, h) ;
	m_pText->setText ("史萊姆", 1, 1, 1) ;
	addChild (m_pText) ;
#elif _GAMEENGINE_2D_
	m_pBtn = new CTextButton();
	m_pBtn->init(50, 15, 200, 15, 0);
	addChild(m_pBtn);
	
	m_pText = new CTextArea();
	m_pText->init(50, 35, w, h);
	addChild(m_pText) ;
#endif

   show(false);
}

bool CTargetInfoWnd::canDrag(int tx, int ty)
{
   return false;
}

WindowClassType CTargetInfoWnd::getClassType()
{
   return WND_TARGETINFO;
}

void CTargetInfoWnd::show(bool bShow)
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
void CTargetInfoWnd::setZOrder(int order)
{
   m_overlay.setZOrder(order);
}
#endif

void CTargetInfoWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
   if(pUnitObject != NULL) {
      char buf[255];
      sprintf_s(buf, sizeof(buf), "等級: %3d   %s\nHP: %5d", pUnitObject->getLevel(), pUnitObject->getName().c_str(), pUnitObject->getHP());   
      m_pText->setText(buf, 1, 1, 1);
   }
   else
      m_pText->setText("", 1, 1, 1);
}

void CTargetInfoWnd::updateBackpack(CUnitObject *pUnitObject)
{
}

void CTargetInfoWnd::updateSkill(CUnitObject *pUnitObject)
{
}

void CTargetInfoWnd::updateHotKeyItem(int field, HotKeyItem *pHotKeyItem)
{
}

void CTargetInfoWnd::updateCoolDown(CSkill *pSkill)
{
}

void CTargetInfoWnd::setTarget(long long uid)
{
   if(uid != m_targetUID) {
      // 更換目標物
      
      // 把舊的監控取消
      CUnitObject *pOldTargetObject = getTarget();
      if(pOldTargetObject != NULL)
         pOldTargetObject->removeModelEventListener(this);
   }

   m_targetUID = uid;
   CUnitObject *pTargetObject = getTarget();
   m_pPlayer->setTargetObject(pTargetObject);   // 設定玩家目標物
   if(pTargetObject != NULL)
      pTargetObject->addModelEventListener(this);  // 監聽目標物的資料變動
      
   updateAdvAttr(pTargetObject);

   if(m_targetUID > 0)
      show(true);
   else if(m_targetUID <= 0)
      show(false);
}

CUnitObject* CTargetInfoWnd::getTarget()
{
   return m_pScene->getUnitObject(m_targetUID);
}