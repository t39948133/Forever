#ifndef _GP_APPLICATION_H_
#define _GP_APPLICATION_H_

#include <system\gp_variable_type.h>

#include <io\gp_key_state.h>

namespace GP
{

class Canvas ;

/*
//快速字串
class FastString
{
} ;

//一般字串
class String
{
private:

public:
} ;

//字串
*/


//#########################################
//#########################################
//#########################################

class FPS
{
private:
	float count ;
	float32 fps ;
	float32 accuTime ;

	float totalTime ;

public:
	FPS () ;

	float32 getTotalTime ()const ;
	float32 get ()const ;
	void work (float32) ;
} ;

class Application
{
private:
	static Application* gpApplication ;

	bool bNeedEnd ;//需要結束
	enum {NO_PRE_TIME = -1} ;
	int preTime ;//上次的時間

private:
	Application (const Application&) {} //no copy construct

protected:
	KeyStateMan keyStateMan ;
	FPS fps, wps ;

//	bool b2DPixelMode ;

	Canvas* pCanvas ;

public:
private:
	int coordinateSystem ;

public:
	Application () ;
	~Application () ;

	void setEnd () ;//結束程式

	static void fnInit () ;
	static void fnWork () ;
	static bool fnClose () ;
private:
	void work () ;

public:
	static void fnPaint () ;

	void setDisplayMode (bool, int, int, int) ;//改顯示模式
//	void setScreenPixelMode () ;//把矩陣設定為螢幕,左上角是(0,0),右下角是(w-1,h)
//	void set2DPixelMode () ;

	Canvas& getMainCanvas () ;//取得主畫布

	//繼承用
	virtual void onInit () = 0 ;//作初始
//	virtual Canvas* onCreaetCanvas () = 0 ;//作初始
	virtual void onWork (float32) = 0 ;//取得系統執行權
	virtual void onExtWork () = 0 ;//額外的運作時間
	virtual void onPrePaint () = 0 ;//處理繪圖
	virtual void onPaint () = 0 ;//處理繪圖
	virtual bool onClose () = 0 ;//回傳true確定要關閉
} ;

}

#endif