/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGraphicsRender.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _CGRAPHICSRENDER_H_
#define _CGRAPHICSRENDER_H_
#include "IGameFlowListener.h"
#include "IMouseEventListener.h"
#include "IKeyEventListener.h"

#include <OgreSceneManager.h>
#include <OgreCamera.h>

/** @brief 繪圖引擎(抽象化物件)
  *        對整個遊戲系統而言只會知道這個物件,
  *        所有3D繪圖只要對這物件傳入相關資訊即可處理,
  *        至於3D細節處理由CGraphicsRender的子類別來集中處理 */
class CGraphicsRender
{
   public:
      virtual ~CGraphicsRender();

      /** @brief  取得繪圖引擎名稱
        * @return 繪圖引擎名稱 */
      std::string getRenderName();

      /** @brief 要接收繪圖引擎丟出的IGameFlowListener訊息,
        *        需要用此成員函式來註冊
        * @param listener 要接收訊息的物件 */
      virtual void addGameFlowListener(IGameFlowListener *listener) = 0;

      /** @brief 要接收繪圖引擎丟出的IMouseEventListener訊息,
        *        需要用此成員函式來註冊
        * @param listener 要接收訊息的物件 */
      virtual void addMouseEventListener(IMouseEventListener *listener) = 0;

      /** @brief 要接收繪圖引擎丟出的IKeyEventListener訊息,
        *        需要用此成員函式來註冊
        * @param listener 要接收訊息的物件 */
      virtual void addKeyEventListener(IKeyEventListener *listener) = 0;

      /** @brief  取得render視窗
        * @return render視窗 */
      virtual HWND getRenderHwnd() = 0;

      // Ogre object
      virtual Ogre::SceneManager* getSceneManager() = 0;
      virtual Ogre::Camera* getCamera() = 0;

   protected:
      /** @brief 設定繪圖引擎名稱
        * @param renderName 繪圖引擎名稱 */
      void setRenderName(std::string renderName);

      /** @brief 繪圖引擎畫圖 */
      virtual void run() = 0;

   private:
      friend class CGameClient3D;  // 允許CGameClient3D物件來存取private/protected
      std::string m_strRenderName; // 繪圖引擎名稱
};

#endif // #ifndef _CGRAPHICSRENDER_H_