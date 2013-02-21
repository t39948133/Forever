/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSceneObjMan.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/16 */
#include "CSceneObjMan.h"

void CSceneObjMan::init(Ogre::SceneManager *pSceneManager)
{
   m_pSceneManager = pSceneManager;
   m_pRaySceneQuery = m_pSceneManager->createRayQuery(Ogre::Ray());
}

void CSceneObjMan::write(std::string fileName)
{
   FILE *pFile = fopen(fileName.c_str(), "wb");
	if(pFile != NULL) {
		int version = 0;
		fwrite(&version, sizeof(version), 1, pFile);

		int count = m_vSceneObj.size();
		fwrite(&count, sizeof(count), 1, pFile);

      std::list<CSceneObj>::iterator it = m_vSceneObj.begin();
		while(it != m_vSceneObj.end()) {
			(*it).write(pFile);
			it++;
		}

		fclose(pFile);
	}
}

void CSceneObjMan::read(std::string fileName)
{
   release();

   FILE *pFile = fopen(fileName.c_str(), "rb");
	if(pFile != NULL) {
		int version = 0 ;
		fread(&version, sizeof(version), 1, pFile);

		int count;
		fread(&count, sizeof(count), 1, pFile);

		m_vSceneObj.resize(count);

		std::list<CSceneObj>::iterator it = m_vSceneObj.begin();
		while(it != m_vSceneObj.end()) {
			(*it).read(m_pSceneManager, pFile);
			it++;
		}

		fclose(pFile);
	}
}

void CSceneObjMan::release()
{
   std::list<CSceneObj>::iterator it = m_vSceneObj.begin();
	while(it != m_vSceneObj.end()) {
		(*it).release(m_pSceneManager);
		it++;
	}

	m_vSceneObj.clear();
}

void CSceneObjMan::showBoundingBox(Ogre::Ray &mouseRay)
{
   CSceneObj *pSceneObj = getSceneObj(mouseRay);
   showBoundingBox(pSceneObj);
}

void CSceneObjMan::showBoundingBox(CSceneObj *pSceneObj)
{
   std::list<CSceneObj>::iterator it = m_vSceneObj.begin();
	while(it != m_vSceneObj.end()) {
		(*it).showBoundingBox(false);
		it++;
	}

	if(pSceneObj != NULL)
		pSceneObj->showBoundingBox(true);
}

void CSceneObjMan::addSceneObj(CSceneObj &sceneObj)
{
   addSceneObj(sceneObj.getPosition(), 
               sceneObj.getRotation(), 
               sceneObj.getScale(), 
               sceneObj.getName());
}

void CSceneObjMan::addSceneObj(const Ogre::Vector3 &pos, 
                               const Ogre::Quaternion &rotation,
                               const Ogre::Vector3 &scale,
                               std::string meshName)
{
   CSceneObj tmp;
	m_vSceneObj.push_back(tmp);

	CSceneObj &sceneObj = m_vSceneObj.back();
	sceneObj.loadMesh(m_pSceneManager, meshName);

	sceneObj.setPosition(pos);
	sceneObj.setRotation(rotation);
	sceneObj.setScale(scale);
}

CSceneObj* CSceneObjMan::getSceneObj(Ogre::Ray &mouseRay)
{
   m_pRaySceneQuery->setRay(mouseRay);
   Ogre::RaySceneQueryResult &result = m_pRaySceneQuery->execute();
   Ogre::RaySceneQueryResult::iterator itr = result.begin();
	while(itr != result.end())	{
		if(itr->movable != NULL) {
			//有點到物件

			std::list<CSceneObj>::iterator it = m_vSceneObj.begin();
			while(it != m_vSceneObj.end()) {
            if((*it).checkEntity((Ogre::Entity *)(itr->movable)))
					return &(*it);
				++it;
			}
		}

		++itr;
	}

	return NULL;
}

void CSceneObjMan::delSceneObj(Ogre::Ray &mouseRay)
{
   CSceneObj *pSceneObj = getSceneObj(mouseRay);
	if(pSceneObj != NULL) {
		std::list<CSceneObj>::iterator it = m_vSceneObj.begin();
		while(it != m_vSceneObj.end()) {
			if(&(*it) == pSceneObj) {
				(*it).release(m_pSceneManager);
				m_vSceneObj.erase(it);
				break;
			}
			++it;
		}
	}
}