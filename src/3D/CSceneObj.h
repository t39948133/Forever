/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSceneObj.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/16 */
#ifndef _CSCENEOBJ_H_
#define _CSCENEOBJ_H_
#include "Common.h"

#include <Ogre.h>

class CSceneObj
{
   public:
      CSceneObj();

      bool checkEntity(Ogre::Entity *pEntity);
      void showBoundingBox(bool bShow);
      void show(bool bShow);
      void write(FILE *pFile);
      void read(Ogre::SceneManager *pSceneManager, FILE *pFile);
      std::string getName();
      void setPosition(const Ogre::Vector3 &pos);
      void setRotation(const Ogre::Vector3 &rot);
      void setRotation(const Ogre::Quaternion &rot);
      void setScale(const Ogre::Vector3 &scale);
      const Ogre::Vector3& getPosition() const;
      const Ogre::Quaternion& getRotation() const;
      const Ogre::Vector3& getScale() const;
      void loadMesh(Ogre::SceneManager *pSceneManager, std::string meshName);
      void release(Ogre::SceneManager *pSceneManager);

   private:
      Ogre::Entity    *m_pEntity;
      Ogre::SceneNode *m_pNode;
};

#endif  // #ifndef _CSCENEOBJ_H_