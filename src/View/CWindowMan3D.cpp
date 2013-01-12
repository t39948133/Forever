#include "CWindowMan3D.h"
#include "CRenderLoader.h"
#include "CGraphicsRender.h"

CWindowMan3D::CWindowMan3D() : CWindowMan()
{
   CGraphicsRender *pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   if(pRenderCore != NULL) {
      pRenderCore->addKeyEventListener(this);
      pRenderCore->addMouseEventListener(this);
   }
}

void CWindowMan3D::addWnd(CWindow *pWnd)
{
   CWindowMan::addWnd(pWnd);
   pWnd->setWindowMan(this);

   int offset = 0; 
   std::list<CWindow *>::reverse_iterator it = m_pWindowList->rbegin();
   while(it != m_pWindowList->rend()) {
      (*it)->setZOrder(offset++);
      it++;
   }
}

void CWindowMan3D::keyDown(const OIS::KeyEvent &evt)
{
   switch(evt.key) {
      case OIS::KC_P: {
         bool bPlayerInfoWndVisible = false;
         std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_PLAYERINFO) {
               (*it)->show(!(*it)->getVisible());
               bPlayerInfoWndVisible = (*it)->getVisible();
            }
            else if((*it)->getClassType() == WND_BACKPACK)
               (*it)->show(bPlayerInfoWndVisible);

            it++;
         }
         break;
      }

      case OIS::KC_B: {
         std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_BACKPACK) {
               (*it)->show(!(*it)->getVisible());
               break;
            }

            it++;
         }
         break;
      }

      case OIS::KC_K: {
         std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_SKILL) {
               (*it)->show(!(*it)->getVisible());
               break;
            }

            it++;
         }
         break;
      }
   }
}

void CWindowMan3D::keyUp(const OIS::KeyEvent &evt)
{
}

void CWindowMan3D::mouseDown(const OIS::MouseEvent &evt)
{
   m_iClientX = evt.state.X.abs;
   m_iClientY = evt.state.Y.abs;

   if(evt.state.buttonDown(OIS::MB_Left)) {
      std::list<CWindow *>::iterator it = m_pWindowList->begin();
		while(it != m_pWindowList->end ()) {
			if((*it)->checkPoint(m_iClientX, m_iClientY)) {
				int tx = m_iClientX;
				int ty = m_iClientY;

            m_pWindowList->push_front(*it);
				m_pWindowList->erase(it);
				m_pDragWnd = m_pWindowList->front();

            int offset = 0; 
            std::list<CWindow *>::reverse_iterator it1 = m_pWindowList->rbegin();
            while(it1 != m_pWindowList->rend()) {
               (*it1)->setZOrder(offset++);
               it1++;
            }

				if(m_pDragWnd->canDrag(tx - m_pDragWnd->x, ty - m_pDragWnd->y)) {
					//可以拖曳
					m_bInDrag = true;
				}
            else {
					//不可以拖曳
					m_pDragWnd->onLClick(tx, ty);
				}

				m_iDragX = m_iClientX;
				m_iDragY = m_iClientY;
				break ;
			}

			it++;
		}
   }
   else if(evt.state.buttonDown(OIS::MB_Right)) {
      std::list<CWindow *>::iterator it = m_pWindowList->begin();
      while(it != m_pWindowList->end()) {
         if((*it)->checkPoint(m_iClientX, m_iClientY)) {
				int tx = m_iClientX;
				int ty = m_iClientY;

            m_pWindowList->push_front(*it);
				m_pWindowList->erase(it);
				m_pDragWnd = m_pWindowList->front();

            int offset = 0; 
            std::list<CWindow *>::reverse_iterator it1 = m_pWindowList->rbegin();
            while(it1 != m_pWindowList->rend()) {
               (*it1)->setZOrder(offset++);
               it1++;
            }

            m_bInDrag = false;
            m_pDragWnd->onRClick(tx, ty);
            break;
         }

         it++;
      }
   }
}

void CWindowMan3D::mouseMove(const OIS::MouseEvent &evt)
{
   if(m_bInDrag) {
      if(evt.state.buttonDown(OIS::MB_Left)) {
         m_iClientX = evt.state.X.abs;
         m_iClientY = evt.state.Y.abs;

         int dx = m_iClientX - m_iDragX;  //滑鼠拖曳多遠
		   int dy = m_iClientY - m_iDragY;  //滑鼠拖曳多遠

		   m_pDragWnd->x += dx;
		   m_pDragWnd->y += dy;

		   m_pDragWnd->onDrag();

		   m_iDragX = m_iClientX;
		   m_iDragY = m_iClientY;
      }
      else
         m_bInDrag = false;
   }
}

void CWindowMan3D::mouseUp(const OIS::MouseEvent &evt)
{
}

bool CWindowMan3D::isPressWindow(int x, int y)
{
   bool bPress = false;
   std::list<CWindow *>::iterator it = m_pWindowList->begin();
	while(it != m_pWindowList->end ()) {
      if((*it)->checkPoint(m_iClientX, m_iClientY)) {
         bPress = true;
         break;
      }
   
      it++;
   }

   return bPress;
}