#include "CWindowMan.h"

CWindowMan::CWindowMan ()
{
	pDragWnd = NULL ;
	bInDrag = false ;
}

void CWindowMan::addWnd (CWindow* pw)
{
	pw->pParent = NULL ;
	vpWindow.push_back (pw) ;
}

void CWindowMan::doDrag (HWND hWnd, CKeyMan& keyMan)
{
	//拖曳視窗中
	if (keyMan.isDown (KEY_LBUTTON))
	{
		//繼續壓著
		int dx = clientX - dragX ;//滑鼠拖曳多遠
		int dy = clientY - dragY ;//滑鼠拖曳多遠

		pDragWnd->x += dx ;
		pDragWnd->y += dy ;

		pDragWnd->onMove () ;

		dragX = clientX ;
		dragY = clientY ;
	}else
	{
		//放開
		bInDrag = false ;
	}
}

bool CWindowMan::work (HWND hWnd, 
							CKeyMan& keyMan)
{
	bool bPressWindow = false ;

	getMouseScreenPos (screenX, screenY) ;
	getMousePos (hWnd, clientX, clientY) ;

	if (bInDrag)
	{
		doDrag (hWnd, keyMan) ;
	}else
	{
		//不是拖曳視窗
		if (keyMan.isPress (KEY_LBUTTON))
		{
			//壓下去的瞬間
			VP_WINDOW::iterator pi = vpWindow.begin () ;
			while (pi != vpWindow.end ())
			{
				if ((*pi)->checkPoint (clientX, clientY))
				{
					int tx = clientX ;
					int ty = clientY ;

					if ((*pi)->canDrag (tx-(*pi)->x, 
										ty-(*pi)->y))
					{
						//可以拖曳
						bInDrag = true ;
					}else
					{
						//不可以拖曳
						(*pi)->onLClick (tx, ty) ;
					}

					//有按到
					bPressWindow = true ;

					dragX = clientX ;
					dragY = clientY ;

					vpWindow.push_front (*pi) ;

					vpWindow.erase (pi) ;
					pDragWnd = vpWindow.front () ;

					break ;
				}

				++ pi ;
			}
		}
      else if(keyMan.isPress(KEY_RBUTTON)) {
         //壓下去的瞬間
			VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->checkPoint(clientX, clientY)) {
					int tx = clientX;
					int ty = clientY;

               bInDrag = false;
               (*pi)->onRClick(tx, ty);

               //有按到
					bPressWindow = true;

               break;
            }

            pi++;
         }
		}
      else if(keyMan.isPress(KEY_P)) {
         bool bPlayerInfoWndVisible = false;
         VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->getClassType() == WND_PLAYERINFO) {
               (*pi)->bVisible = !(*pi)->bVisible;
               bPlayerInfoWndVisible = (*pi)->bVisible;
            }
            else if((*pi)->getClassType() == WND_BACKPACK)
               (*pi)->bVisible = bPlayerInfoWndVisible;

            pi++;
         }
      }
      else if(keyMan.isPress(KEY_B)) {
         VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->getClassType() == WND_BACKPACK) {
               (*pi)->bVisible = !(*pi)->bVisible;
               break;
            }
            pi++;
         }
      }
      else if(keyMan.isPress(KEY_K)) {
         VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->getClassType() == WND_SKILL) {
               (*pi)->bVisible = !(*pi)->bVisible;
               break;
            }
            pi++;
         }
      }
	}

	return bPressWindow ;
}

#ifdef _GAMEENGINE_2D_
void CWindowMan::draw (HDC hdc)
{
	VP_WINDOW::reverse_iterator pi = vpWindow.rbegin () ;
	while (pi != vpWindow.rend ())
	{
		if ((*pi)->bVisible)
			(*pi)->draw (hdc, 0, 0) ;
		++ pi ;
	}
}
#endif

void CWindowMan::deleteAllWindow ()
{
	VP_WINDOW::reverse_iterator pi = 
			vpWindow.rbegin () ;
	while (pi != vpWindow.rend ())
	{
		delete *pi ;

		++pi ;
	}
}