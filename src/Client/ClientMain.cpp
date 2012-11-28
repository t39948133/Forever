#include "Common.h"
#include "CUnitObject.h"
#include "CPlayer.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPlayer player(_T("xXX"));	//_T _TEXT的意思 可將內容轉為文字用的2個bytes 1個字
   return 0;
}