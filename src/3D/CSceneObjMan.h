/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSceneObjMan.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/16 */
#ifndef _CSCENEOBJMAN_H_
#define _CSCENEOBJMAN_H_
#include "CSceneObj.h"

class CSceneObjMan
{
   public:
      void init(Ogre::SceneManager *pSceneManager);
      void write(std::string fileName);
      void read(std::string fileName);
      void release();
      void showBoundingBox(Ogre::Ray &mouseRay);
      void showBoundingBox(CSceneObj *pSceneObj);
      void addSceneObj(CSceneObj &sceneObj);
      void addSceneObj(const Ogre::Vector3 &pos, 
                       const Ogre::Quaternion &rotation,
                       const Ogre::Vector3 &scale,
                       std::string meshName);
      CSceneObj* getSceneObj(Ogre::Ray &mouseRay);
      void delSceneObj(Ogre::Ray &mouseRay);

   private:
      std::list<CSceneObj>  m_vSceneObj;
      Ogre::SceneManager   *m_pSceneManager;
      Ogre::RaySceneQuery  *m_pRaySceneQuery;
};

#endif // #ifndef _CSCENEOBJMAN_H_