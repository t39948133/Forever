/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   COgreRender.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _COGRERENDER_H_
#define _COGRERENDER_H_
#include "CGraphicsRender.h"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

class COgreRender : public CGraphicsRender,
                    public Ogre::FrameListener, 
                    public Ogre::WindowEventListener, 
                    public OIS::KeyListener, 
                    public OIS::MouseListener, 
                    public OgreBites::SdkTrayListener
{
   public:
      COgreRender();
      virtual ~COgreRender();

      // CGraphicsRender
      /* virtual */ void addGameFlowListener(IGameFlowListener *listener);
      /* virtual */ void addMouseEventListener(IMouseEventListener *listener);
      /* virtual */ void addKeyEventListener(IKeyEventListener *listener);
      /* virtual */ Ogre::SceneManager* getSceneManager();
      /* virtual */ Ogre::Camera* getCamera();
      /* virtual */ HWND getRenderHwnd();

      //virtual void createResourceListener() = 0;

   protected:
      // CGraphicsRender
      /* virtual */ void run();

   private:
      bool setup();
      void setupResources();
      bool configure();
      void chooseSceneManager();
      void createCamera();
      void createViewports();
      void loadResources();
      void createFrameListener();

      // Ogre::FrameListener
      bool frameRenderingQueued(const Ogre::FrameEvent& evt);

      // OIS::KeyListener
      bool keyPressed(const OIS::KeyEvent &arg);
      bool keyReleased(const OIS::KeyEvent &arg);
      
      // OIS::MouseListener
      bool mouseMoved(const OIS::MouseEvent &arg);
      bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
      bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

      // Ogre::WindowEventListener
      void windowResized(Ogre::RenderWindow* rw); // Adjust mouse clipping area
      void windowClosed(Ogre::RenderWindow* rw);  // Unattach OIS before window shutdown (very important under Linux)

      Ogre::Root *mRoot;
      Ogre::Camera* mCamera;
      Ogre::SceneManager* mSceneMgr;
      Ogre::RenderWindow* mWindow;
      Ogre::String mResourcesCfg;
      Ogre::String mPluginsCfg;

      // OgreBites
      OgreBites::SdkTrayManager* mTrayMgr;
      OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
      OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
      bool mCursorWasVisible;                    // was cursor visible before dialog appeared
      bool mShutDown;

      // OIS Input devices
      OIS::InputManager* mInputManager;
      OIS::Mouse*    mMouse;
      OIS::Keyboard* mKeyboard;

      HWND m_hOgreWnd;
      std::set<IGameFlowListener *>   m_gameFlowListeners;
      std::set<IMouseEventListener *> m_mouseEventListeners;
      std::set<IKeyEventListener *>   m_keyEventListeners;
};

#endif // #ifndef _COGRERENDER_H_