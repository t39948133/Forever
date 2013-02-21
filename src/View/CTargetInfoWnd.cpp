#include "CTargetInfoWnd.h"

#ifdef _GAMEENGINE_3D_
#include "CGraphicsRender.h"
#include "CRenderLoader.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CNPC.h"
#endif

CTargetInfoWnd::CTargetInfoWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_pBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_pText[i] = NULL;
#endif
}

CTargetInfoWnd::~CTargetInfoWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_pBtn[i] != NULL) {
         delete m_pBtn[i];
         m_pBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_pText[i] != NULL) {
         delete m_pText[i];
         m_pText[i] = NULL;
      }
   }
#endif
}

void CTargetInfoWnd::init(int _x, int _y, CScene *pScene, CPlayer *pPlayer)
{
   m_pPlayer = pPlayer;
   m_pScene = pScene;
   m_targetUID = -1;

   x = _x;
	y = _y;
#ifdef _GAMEENGINE_3D_
   w = 284;
   h = 84;
#elif _GAMEENGINE_2D_
	w = 300;
	h = 60;
#endif

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
   m_overlay.setZOrder(1);
   m_overlay.setBackImage("UI/BG/RegularMonster");

	m_pBtn[BUTTON_AI] = new CImageButton();
	m_pBtn[BUTTON_AI]->init(&m_overlay, 30, 22, 40, 40, BUTTON_AI);
	m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/1");
	addChild(m_pBtn[BUTTON_AI]);

   m_pBtn[BUTTON_HP] = new CImageButton();
	m_pBtn[BUTTON_HP]->init(&m_overlay, 83, 36, 169, 13, BUTTON_HP);
	m_pBtn[BUTTON_HP]->setImage("UI/MonsterHP");
	addChild(m_pBtn[BUTTON_HP]);

	m_pText[TEXT_LEVEL] = new CTextAreaOgre();
	m_pText[TEXT_LEVEL]->init(&m_overlay, 9, 33, 18, 18);
   m_pText[TEXT_LEVEL]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
   m_pText[TEXT_LEVEL]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
	addChild(m_pText[TEXT_LEVEL]);

   m_pText[TEXT_NAME] = new CTextAreaOgre();
	m_pText[TEXT_NAME]->init(&m_overlay, 80, 6, 137, 24);
   m_pText[TEXT_NAME]->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
   m_pText[TEXT_NAME]->setVerticalAlignment(CTextAreaOgre::V_CENTER);
	addChild(m_pText[TEXT_NAME]);
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

void CTargetInfoWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
#ifdef _GAMEENGINE_3D_
   if(pUnitObject != NULL) {
      char buf[50];

      memset(buf, 0, sizeof(buf));
      sprintf_s(buf, sizeof(buf), "%d", pUnitObject->getLevel());
      m_pText[TEXT_LEVEL]->setText(buf, 1, 1, 1);

      memset(buf, 0, sizeof(buf));
      sprintf_s(buf, sizeof(buf), "%s", pUnitObject->getName().c_str());
      m_pText[TEXT_NAME]->setText(buf, 1, 1, 1);

      float diffHP = (float)m_pBtn[BUTTON_HP]->w / (float)pUnitObject->getHPMax();
      m_pBtn[BUTTON_HP]->setWidth(diffHP * (float)pUnitObject->getHP());
   }
#elif _GAMEENGINE_2D_
   if(pUnitObject != NULL) {
      char buf[255];
      sprintf_s(buf, sizeof(buf), "等級: %3d   %s\nHP: %5d", pUnitObject->getLevel(), pUnitObject->getName().c_str(), pUnitObject->getHP());   
      m_pText->setText(buf, 1, 1, 1);
   }
   else
      m_pText->setText("", 1, 1, 1);
#endif
}

void CTargetInfoWnd::setTarget(long long uid)
{
   show(false);

   if(uid != m_targetUID) {
      // 更換目標物
      
      // 把舊的監控取消
      CUnitObject *pOldTargetObject = getTarget();
      if(pOldTargetObject != NULL)
         pOldTargetObject->removeAdvAttrEventListener(this);
   }

   m_targetUID = uid;
   CUnitObject *pTargetObject = getTarget();
   m_pPlayer->setTargetObject(pTargetObject);   // 設定玩家目標物
   if(pTargetObject != NULL)
      pTargetObject->addAdvAttrEventListener(this);  // 監聽目標物的資料變動

#ifdef _GAMEENGINE_3D_
   if(pTargetObject != NULL) {
      //取得遊戲畫面寬與高
      CGraphicsRender *pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
      RECT rect;
      memset(&rect, 0, sizeof(rect));
      HWND hRenderWnd = pRenderCore->getRenderHwnd();
      GetClientRect(hRenderWnd, &rect);

      CMonster *pMonster = dynamic_cast<CMonster *>(pTargetObject);
      if(pMonster != NULL) {
         CMonsterInfo *pMonsterInfo = pMonster->getInfo();
         if(pMonsterInfo != NULL) {
            if(pMonsterInfo->getLevelGrade() == REGULAR_GRADE) {
               int x = ((rect.right - rect.left) - 284) / 2;
               m_overlay.setPosition(x, 0);
               m_overlay.setSize(284, 84);
               m_overlay.setBackImage("UI/BG/RegularMonster");

               if(pMonsterInfo->getWistom() == 1) {
                  m_pBtn[BUTTON_AI]->setPosition(30, 22);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/1");
               }
               else if(pMonsterInfo->getWistom() == 2) {
                  m_pBtn[BUTTON_AI]->setPosition(30, 22);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/2");
               }
               else if(pMonsterInfo->getWistom() == 3) {
                  m_pBtn[BUTTON_AI]->setPosition(30, 22);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/3");
               }

               m_pBtn[BUTTON_HP]->setPosition(83, 36);
               m_pBtn[BUTTON_HP]->setSize(169, 13);

               m_pText[TEXT_LEVEL]->setPosition(9, 33);

               m_pText[TEXT_NAME]->setPosition(80, 6);
            }
            else if(pMonsterInfo->getLevelGrade() == ELITE_GRADE) {
               int x = ((rect.right - rect.left) - 284) / 2;
               m_overlay.setPosition(x, 0);
               m_overlay.setSize(284, 84);
               m_overlay.setBackImage("UI/BG/EliteMonster");

               if(pMonsterInfo->getWistom() == 1) {
                  m_pBtn[BUTTON_AI]->setPosition(31, 23);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/1");
               }
               else if(pMonsterInfo->getWistom() == 2) {
                  m_pBtn[BUTTON_AI]->setPosition(31, 23);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/2");
               }
               else if(pMonsterInfo->getWistom() == 3) {
                  m_pBtn[BUTTON_AI]->setPosition(31, 23);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/3");
               }

               m_pBtn[BUTTON_HP]->setPosition(84, 36);
               m_pBtn[BUTTON_HP]->setSize(169, 13);

               m_pText[TEXT_LEVEL]->setPosition(9, 33);

               m_pText[TEXT_NAME]->setPosition(95, 3);
            }
            else if(pMonsterInfo->getLevelGrade() == HERO_GRADE) {
               int x = ((rect.right - rect.left) - 397) / 2;
               m_overlay.setPosition(x, 0);
               m_overlay.setSize(397, 99);
               m_overlay.setBackImage("UI/BG/HeroMonster");

               if(pMonsterInfo->getWistom() == 1) {
                  m_pBtn[BUTTON_AI]->setPosition(31, 28);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/1");
               }
               else if(pMonsterInfo->getWistom() == 2) {
                  m_pBtn[BUTTON_AI]->setPosition(31, 28);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/2");
               }
               else if(pMonsterInfo->getWistom() == 3) {
                  m_pBtn[BUTTON_AI]->setPosition(31, 28);
                  m_pBtn[BUTTON_AI]->setSize(40, 40);
                  m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/3");
               }

               m_pBtn[BUTTON_HP]->setPosition(83, 42);
               m_pBtn[BUTTON_HP]->setSize(251, 13);

               m_pText[TEXT_LEVEL]->setPosition(9, 39);

               m_pText[TEXT_NAME]->setPosition(124, 6);
            }
         }
      }
      else {
			CNPC *pNPC = dynamic_cast<CNPC *>(pTargetObject);
			if(pNPC != NULL) {
				int x = ((rect.right - rect.left) - 284) / 2;
            m_overlay.setPosition(x, 0);
            m_overlay.setSize(284, 84);
            m_overlay.setBackImage("UI/BG/RegularMonster");

            m_pBtn[BUTTON_AI]->setPosition(30, 22);
            m_pBtn[BUTTON_AI]->setSize(40, 40);
            m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/Knight");

            m_pBtn[BUTTON_HP]->setPosition(83, 36);
            m_pBtn[BUTTON_HP]->setSize(169, 13);

            m_pText[TEXT_LEVEL]->setPosition(9, 33);

            m_pText[TEXT_NAME]->setPosition(80, 6);
			}
			else {
         CPlayer *pPlayer = dynamic_cast<CPlayer *>(pTargetObject);
         if(pPlayer != NULL) {
            int x = ((rect.right - rect.left) - 284) / 2;
            m_overlay.setPosition(x, 0);
            m_overlay.setSize(284, 84);
            m_overlay.setBackImage("UI/BG/RegularMonster");

            m_pBtn[BUTTON_AI]->setPosition(30, 22);
            m_pBtn[BUTTON_AI]->setSize(40, 40);
            m_pBtn[BUTTON_AI]->setImage("UI/MonsterAI/Knight");

            m_pBtn[BUTTON_HP]->setPosition(83, 36);
            m_pBtn[BUTTON_HP]->setSize(169, 13);

            m_pText[TEXT_LEVEL]->setPosition(9, 33);

            m_pText[TEXT_NAME]->setPosition(80, 6);
         }
      }
   }
   }
#endif

   updateAdvAttr(pTargetObject);

   if(m_targetUID > -1)
      show(true);
   else
      show(false);
}

CUnitObject* CTargetInfoWnd::getTarget()
{
   return m_pScene->getUnitObject(m_targetUID);
}