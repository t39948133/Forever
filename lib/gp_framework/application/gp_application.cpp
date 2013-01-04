#include "gp_application.h"

#include <graphic\gp_canvas.h>
#include <graphic\gp_canvas_gles.h>


#include <assert.h>
#include <stdio.h>

HWND hWnd;

namespace GP
{

FPS::FPS ():count(0),fps(0),accuTime(0),totalTime(0)
{
}

float32 FPS::getTotalTime ()const
{
	return totalTime ;
}

float32 FPS::get ()const
{
	return fps ;
}


void FPS::work (float32 timePass)
{
	count += 1 ;
	accuTime += timePass ;
	totalTime += timePass ;

	if (accuTime > 1.0)
	{
		fps = float32(count)/accuTime ;

		accuTime = 0 ;
		count = 0 ;
	}
}

//#################################################

Application* Application::gpApplication = NULL ;

Application::Application ():bNeedEnd(false),preTime(NO_PRE_TIME),pCanvas(NULL)/*,
							b2DPixelMode(true)*/
{
	assert ((gpApplication == NULL) && "Application::Application") ;
	gpApplication = this ;
}

Application::~Application ()
{
	if (pCanvas != NULL)
	{
		delete pCanvas ;
	}
}

void Application::setEnd ()
{
	bNeedEnd = true ;
}

void Application::fnInit ()
{
	assert ((gpApplication != NULL) && "Application::fnInit") ;

	if (gpApplication != NULL)
	{

		gpApplication->onInit () ;
	}
}

void Application::fnWork ()
{
	assert ((gpApplication != NULL) && "Application::fnWork") ;

	if (gpApplication != NULL)
	{
		gpApplication->work () ;
	}
}

bool Application::fnClose ()
{
	assert ((gpApplication != NULL) && "Application::fnClose") ;
	if (gpApplication != NULL)
	{
		return gpApplication->onClose () ;
	}else
		return true ;
}

void Application::work ()
{
	if (!bNeedEnd)
	{
		int curTime = GetTickCount () ;
		if (preTime == NO_PRE_TIME)
		{
			//第一次先略過
			preTime = curTime ;
			return ;
		}

		int timePass = curTime-preTime ;
		//time pass
		float32 timePassF = (float32(timePass))/1000.0f ;

		//
		wps.work (timePassF) ;

		if (timePass == 0)
		{
			//速度太快,兩次之間沒差距,沒有意義
//			Sleep (1) ;
//			return ;
			gpApplication->onExtWork () ;
			return ;
		}

		//key state
		gpApplication->keyStateMan.work (hWnd, pCanvas->getCoordinateSystem (),
			pCanvas->getWidth (), pCanvas->getHeight ()) ;

		//fps
		fps.work (timePassF) ;

		gpApplication->onWork (timePassF) ;

		preTime = curTime ;
	}
}

void Application::fnPaint ()
{
	assert ((gpApplication != NULL) && "Application::fnPaint") ;

	if (gpApplication != NULL)
	{
		if (!gpApplication->bNeedEnd)
		{
			gpApplication->onPrePaint () ;
			gpApplication->pCanvas->drawAllLayer () ;
			gpApplication->onPaint () ;
			gpApplication->pCanvas->update () ;
		}
	}
}

void Application::setDisplayMode (bool bFullScreen, 
									int cs, int w, int h)
{
	coordinateSystem = cs ;

	RECT wndRect ;
	GetWindowRect (hWnd, &wndRect) ;

	RECT cliRect ;
	GetClientRect (hWnd, &cliRect) ;

	int borderW = wndRect.right-wndRect.left-(cliRect.right-cliRect.left) ;
	int borderH = wndRect.bottom-wndRect.top-(cliRect.bottom-cliRect.top) ;

	MoveWindow (hWnd, wndRect.left, wndRect.top,
		borderW+w, borderH+h, true) ;

	//一開始一定沒有
	assert (pCanvas == NULL) ;
}

/*
void Application::setScreenPixelMode ()//把矩陣設定為螢幕,左上角是(0,0),右下角是(w-1,h)
{
}

void Application::set2DPixelMode ()
{
}
*/

Canvas& Application::getMainCanvas ()
{
	if (pCanvas == NULL)
	{
		//需要時才配置
		pCanvas = new CanvasGLES (hWnd) ;
		pCanvas->setCoordinateSystem (coordinateSystem) ;
	}
	return *pCanvas ;
}

//#########################
}

using namespace GP ;

#define MAX_LOADSTRING 100

HINSTANCE hInst;								// current instance

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
//	HACCEL hAccelTable;

	// Initialize global strings
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_GP_FRAMEWORK_00, szWindowClass, MAX_LOADSTRING);
//	strcpy (szTitle, "IDS_APP_TITLE") ;
//	strcpy (szWindowClass, "IDC_GP_FRAMEWORK_00") ;

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GP_FRAMEWORK_00));

	// Main message loop:

	Application::fnInit () ;
	
//	CanvasDC canvas (hWnd) ;

   while (1)
   {
      while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
         if (msg.message == WM_QUIT)
            return TRUE;
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

	  Application::fnWork () ;

	  Application::fnPaint () ;
//	  canvas.update () ;
    }

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GP_FRAMEWORK_00));
	wcex.hIcon			= NULL ;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GP_FRAMEWORK_00);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"szWindowClass";
//	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(L"szWindowClass", L"szTitle", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 0:
			/*
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			*/
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CLOSE:
		if (Application::fnClose ())
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		break ;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
/*
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
*/

