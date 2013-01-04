#ifndef _GP_CANVAS_GL_ES_H_
#define _GP_CANVAS_GL_ES_H_

#include "gp_canvas.h"
#include "gp_canvas_layer.h"

#include "gp_shader.h"
//最佳化的原則

//1
//減少copy資料到vertex buffer
//盡量直接用vertex buffer

//2
//把多張貼圖合併一張
//一次畫多個物件

//3
//變更頂點格式
//把pos,normal,uv,pos,normal,uv
//變成pos,pos,normal,normal,uv,uv
//在power vr底下
//第一種比較好

//4
//對齊記憶體
//浮點數(4 byte)要是在4byte的align
//2 byte要用 2byte的align

//5
//顏色用16 bit的浮點數
//不要用32 bi6的

//6
//盡量用triangle strip
//但是可能會增加繪圖次數
//這要經過實驗才知道
//參考powerVR的sample code

//7
//用降低繪圖區寬高的方式
//確認效能的瓶頸是pixel填充還是vertex投影/打光

//8
//關掉編譯器的compile for thumb選項

//9
//

//10
//當頂點太多
//考慮用DOT3作normal map

//11
//用light map取代打光

//12
//把貼圖關閉試試看fps有沒有提高
//如果有
//把貼圖變小
//減少總貼圖容量
//用壓縮的貼圖
//合併貼圖
//圖形資料直接編成程式碼(或者先轉成最終的格式)

//13
//先篩選要繪圖的物件

//14
//設法辨識背面(單面貼圖)

//15
//使用clip planes
//刪除看不見的

//16
//用CPU作octree篩選

//17
//shaer中減少if else

//18
//切換shader可能消耗時間
//合併多個shader
//這個要測試才知道

//19
//gpu的kill指令可以結束畫圖程序
//要測試看看才知道有沒有變快
//可以用來做

//20
//不要用太多層貼圖

//21
//慎選skinning演算法

//22
//減少改變opengl es的狀態
//一些狀態的函式呼叫
//如果設定內容一樣,不要重複呼叫

//23
//不要lock(讀或寫)buffer
//因為這會等opengl把圖形畫完
//應該平行讓cpu跟onengl運作

//24
//利用framework
//讓UI的繪製與場景,layer的繪製
//不要擠在一起
//能早點做就早點做
//不要onWork完才通通一起做

//25
//不要用gpu discard指令

//26
//限制fps
//也可以讓移動看起來比較順

//27
//盡量把vertex buffer合在一起
//尤其是介面

//28
//先畫不透明的
//再畫alpha blend

//29
//先根據shader排定繪圖順序
//再根據繪圖狀態排定繪圖順序

//30
//alpha blending
//有些要排序,有些不用
//因為順序通常變更不大
//所以用插入排序法

//31
//在power vr
//index triangle list
//是最有效率的

//32
//要動態修改的vertex buffer
//種類要設定正確
//STATIC_DRAW, DYNAMIC_DRAW, STREAM_DRAW

//33
//vertex shader的處理的頂點資料
//最好都是float
//其他格式的轉換會花時間
//但是byte, word的大小影響頻寬
//要試試看才知道

//34
//盡量對齊4byte的vertex資料
//即使byte也是
//最好小於4byte的資料排在最後

//35
//除了螢幕大小的貼圖(作後製特效用)
//其他的寬高都要是2的次方

//36
//normal map,最好用alpha層
//不要再多用層級
//power vr有工具可用

//37
//慎選貼圖pixel的格式
//RGBA8,RGBA5551,RGBA4444,RGB565...
//盡量用16bit

//38
//盡量少用浮點數的pixel(貼圖)

//39
//盡量用壓縮的貼圖格式
//但是這種格式不能自動產生mipmap
//必須先製作好mipmap
//再設定到貼圖
//glCompressedTexImage2D.

//40
//盡量用mipmap
//glGenerateMipmap可以自動產生
//但是無法針對壓縮的格式運作
//壓縮格式的貼圖要用power vr工具產生

//41
//盡量在遊戲剛啟動
//進入關卡前載入所有的地圖
//因為動態載入貼圖會花額外的時間
//(最好搭配cache機制)

//42
//shader先用高低精確度的變數
//再慢慢調降,看看效果是否合適
//評估效能

//43
//shader中減少不必要的座標轉換

//44
//pixel shader愈小愈好

//45
//矩陣運算用highp
//texture coordinates用highp或mediump
//normal或顏色用lowp
//選用sampler跟pixel格式合適

//46
//把線性移動用shder作

//47
//shader不必要用的計算
//用if else跳過


namespace GP
{

//opengl es
class LayerNode ;
typedef std::list <CanvasLayer> V_CANVAS_LAYER ;
class CanvasGLES:public Canvas
{
	HWND hWnd ;
	HDC hDC ;

	EGLDisplay			eglDisplay ;
	EGLConfig			eglConfig ;
	EGLSurface			eglSurface ;
	EGLContext			eglContext ;
	EGLNativeWindowType	eglWindow ;

	Color globalLight ;

	enum {SHADER_DEFAULT, SHADER_TEXT, SHADER_LINE, 
			SHADER_RECT, SHADER_COUNT} ;
	Shader vShader[SHADER_COUNT] ;
	enum {NO_SHADER_ID = 0} ;
	GLuint	ui32VboRect, ui32VboLine, ui32VboText,
			ui32VboImage; //最基本的vertex buffer,用來畫簡單的東西

	//所有的layer
	V_CANVAS_LAYER vCanvasLayer ;

public:
	CanvasGLES (const CanvasGLES&) {} //no copy construct
	CanvasGLES (HWND) ;
	~CanvasGLES () ;

private:
	void initContext () ;//起始設定
	void loadShader () ;//設定預設的shader
	void initDafaultVertexBuffer () ;

//	void setShader (GLuint) ;
	void setShaderDefault (const Matrix4&, bool) ;

	//顯示文字用的shader
	void setShaderText (const Matrix4&, const Color&, bool) ;

	//線條用的
	void setShaderLine (const Matrix4&, const Color&) ;

	void setShaderRect (const Matrix4&, const Color&, bool) ;

protected:

public:
	void setMode (int) ;//顯示模式
//	void set2DPixelMode () ;//設定為pixel模式,用來
	void setBrushColor (const Color&) ;

	void clear (const Color&) ;

	enum {AUTO_LEN = -1} ;
//	void drawText (const char*, float, float, int = AUTO_LEN) ;//顯示文字

private:
	void setTexture (Image*) ;//設定貼圖
	void setVertexBuffer (GLuint) ;//設定vertex buffer

	//設定頂點格式(這也同時自動使用對應的shader)
	void setVertexFormat (const VtxU&) ;//
	void setVertexFormat (const VtxC&) ;//

	//###########################
	//光源需求分析
	//場景 : light map + 環境 + 方向
	//地圖物件 : 環境 + 方向
	//角色 : normal map + 環境 + 方向
	//特效 : 只要做疊色就好,不需光源

	//###########################
	//頂點光源計算 = 環境光 + 方向光 + 物件自體光 + 動態額外光源x3
	void setGlobalLight (const Color&) ;//設定環境光(作日夜)
	void setGlobalDirectionLight (const Color&) ;//設定環境方向光(作太陽光模擬)

	void setObjectLight (const Color&) ;//物件自體光,會跟global相加
	//加在物件身上的動態額外光源(目前三盞),座標已經換算成物件座標
	void setDynamicLight (const VtxC*, const VtxC*, const VtxC*) ;

public:
	void drawEllipse (const RectF&) ;
	void drawRect (const RectF&, Image*) ;

private:
	void getMatrixScreen (Matrix4&) ;//取得矩陣
	void getMatrix2D (Matrix4&) ;//取得矩陣
	void getMatrix (Matrix4&) ;//取得矩陣

	void getImageMatrixScreen (const Point3F&, const Point2F&, 
							float, Matrix4&) ;//取得矩陣,給圖片用的
	void getImageMatrix2D (const Point3F&, const Point2F&, 
							float, Matrix4&) ;//取得矩陣,給圖片用的
	void getImageMatrix (const Point3F&, const Point2F&, 
							float, Matrix4&) ;//取得矩陣,給圖片用的

public:
	void drawImage (const Point3F&, const Point2F&, Image* = NULL, float = 0) ;
	void drawRect (const VertexC&, const Point2F&, float = 0) ;

//	void drawLine (const VertexC&, const VertexC&) ;
private:
	void drawLine (const VertexC&, const VertexC&) ;
public:
	void drawLine (const Point3F&, const Point3F&, const Color&) ;
	void drawCircle (const VertexC&, float) ;
	void drawGridLine (const Point3F&, const Point2F&, const Point2I&, const Color&) ;

private:

public:

	void drawText (const char*, const VertexC&, const Point2F&, int) ;

	CanvasLayer* queryLayer () ;
	void releaseLayer (CanvasLayer*) ;

	void drawNode (LayerNode&) ;
	void drawLayer (CanvasLayer&) ;
	void drawAllLayer ()  ;

	void update () ;//把背景頁更新到視窗或螢幕
} ;

}

#endif