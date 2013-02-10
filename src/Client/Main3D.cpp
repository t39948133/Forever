/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   ClientMain.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/02  */
#include "CClientServer.h"

#ifdef _DEBUGLOG
#include "LogWindow.h"
CLogWindow glog;
#endif  // #ifdef _DEBUG

/** @brief Forever程式進入點 */
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
   CClientServer app;

#ifdef _DEBUGLOG
   glog.Create(hInstance, NULL, FALSE, "Forever3D Log");
   glog.SetOutputFile("Forever3D.log", TRUE);
#endif  // #ifdef _DEBUG

   app.run();

   return 0;
}