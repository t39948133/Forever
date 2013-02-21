/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSceneObj.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/16 */
#include "CSceneObj.h"

CSceneObj::CSceneObj() : m_pEntity(NULL),
                         m_pNode(NULL)
{
}

bool CSceneObj::checkEntity(Ogre::Entity *pEntity)
{
   return pEntity == m_pEntity;
}

void CSceneObj::showBoundingBox(bool bShow)
{
   m_pNode->showBoundingBox(bShow);
}

void CSceneObj::show(bool bShow)
{
   m_pNode->setVisible(bShow);
}

void CSceneObj::write(FILE *pFile)
{
   int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);

	//name
   const Ogre::MeshPtr &meshPtr = m_pEntity->getMesh();
   const Ogre::String &name = meshPtr->getName();

   fwrite(name.c_str(), 32, 1, pFile);

	//pos
   Ogre::Vector3 tmp = m_pNode->getPosition();
	fwrite(&tmp, sizeof(tmp), 1, pFile);

	//rotation
   Ogre::Quaternion tmp2 = m_pNode->getOrientation();
	fwrite(&tmp2, sizeof(tmp2), 1, pFile);

	//scale
	tmp = m_pNode->getScale();
	fwrite(&tmp, sizeof(tmp), 1, pFile);
}

void CSceneObj::read(Ogre::SceneManager *pSceneManager, FILE *pFile)
{
   int version = 0;
	fread(&version, sizeof(version), 1, pFile);

	//name
   char buf[256];
   memset(buf, 0, sizeof(buf));
   fread(buf, 32, 1, pFile);
   std::string name = buf;
	loadMesh(pSceneManager, name);

	//pos
   Ogre::Vector3 tmp;
	fread(&tmp, sizeof(tmp), 1, pFile);
	m_pNode->setPosition(tmp);

	//rotation
   Ogre::Quaternion tmp2;
	fread(&tmp2, sizeof (tmp2), 1, pFile);
	m_pNode->setOrientation(tmp2);

	//scale
	tmp = m_pNode->getScale();
	fread(&tmp, sizeof(tmp), 1, pFile);
	m_pNode->setScale(tmp);
}

std::string CSceneObj::getName()
{
   const Ogre::MeshPtr &meshPtr = m_pEntity->getMesh();
   const Ogre::String &name = meshPtr->getName();

   return name;
}

void CSceneObj::setPosition(const Ogre::Vector3 &pos)
{
   m_pNode->setPosition(pos);
}

void CSceneObj::setRotation(const Ogre::Vector3 &rot)
{
   m_pNode->resetOrientation();
   m_pNode->yaw(Ogre::Radian(rot.y));
   m_pNode->roll(Ogre::Radian(rot.x));
   m_pNode->pitch(Ogre::Radian(rot.z));
}

void CSceneObj::setRotation(const Ogre::Quaternion &rot)
{
   m_pNode->setOrientation(rot);
}

void CSceneObj::setScale(const Ogre::Vector3 &scale)
{
   m_pNode->setScale(scale);
}

const Ogre::Vector3& CSceneObj::getPosition() const
{
   return m_pNode->getPosition();
}

const Ogre::Quaternion& CSceneObj::getRotation() const
{
   return m_pNode->getOrientation();
}

const Ogre::Vector3& CSceneObj::getScale() const
{
   return m_pNode->getScale();
}

void CSceneObj::loadMesh(Ogre::SceneManager *pSceneManager, std::string meshName)
{
   release(pSceneManager);

	m_pEntity = pSceneManager->createEntity(meshName);
	m_pNode = pSceneManager->getRootSceneNode()->createChildSceneNode();
	m_pNode->attachObject(m_pEntity);
}

void CSceneObj::release(Ogre::SceneManager *pSceneManager)
{
   if(m_pNode != NULL) {
		m_pNode->detachAllObjects();

		pSceneManager->getRootSceneNode()->removeChild(m_pNode);
		pSceneManager->destroyEntity(m_pEntity);

		m_pNode = NULL;
		m_pEntity = NULL;
	}
}