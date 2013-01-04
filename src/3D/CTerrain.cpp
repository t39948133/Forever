/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTerrain.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/29 */
#include "CTerrain.h"
#include <utility>

CTerrain::CTerrain()
{
   m_pTerrainMgr = NULL;
   m_pSplatMgr = NULL;
}

CTerrain::~CTerrain()
{
   release();
}

void CTerrain::init(Ogre::SceneManager *pSceneManager, Ogre::Camera *pCamera)
{
   // create terrain manager
   m_pTerrainMgr = new ET::TerrainManager(pSceneManager);
   m_pTerrainMgr->setLODErrorMargin(2, pCamera->getViewport()->getActualHeight());
   m_pTerrainMgr->setUseLODMorphing(true, 0.2f, "morphFactor");

   // create a fresh, mid-high terrain for editing
   ET::TerrainInfo terrainInfo(129, 129, std::vector<float>(129*129, 0.5f));

   // set position and size of the terrain
   terrainInfo.setExtents(Ogre::AxisAlignedBox(0, 0, 0, 900, 0, 900));  // 900 x 900

   // now render it
   m_pTerrainMgr->createTerrain(terrainInfo);

   // create the splatting manager
   m_pSplatMgr = new ET::SplattingManager("ETSplatting", "ET", 128, 128, 3);

   // specify number of splatting textures we need to handle
   m_pSplatMgr->setNumTextures(6);

   // create a manual lightmap texture
   Ogre::TexturePtr lightmapTex = Ogre::TextureManager::getSingleton().createManual("ETLightmap", 
                                                                                    "ET", 
                                                                                    Ogre::TEX_TYPE_2D, 
                                                                                    128, 
                                                                                    128, 
                                                                                    1, 
                                                                                    Ogre::PF_BYTE_RGB);

   Ogre::Image lightmap;
   ET::createTerrainLightmap(terrainInfo, lightmap, 128, 128, Ogre::Vector3(1, -1, 1), Ogre::ColourValue::White, Ogre::ColourValue(0.3f, 0.3f, 0.3f));
   lightmapTex->getBuffer(0, 0)->blitFromMemory(lightmap.getPixelBox(0, 0));

   // load the terrain material and assign it
   Ogre::MaterialPtr material(Ogre::MaterialManager::getSingleton().getByName("ETTerrainMaterial"));
   m_pTerrainMgr->setMaterial(material);

	m_pTerrainInfo = &(m_pTerrainMgr->getTerrainInfo());
}

bool CTerrain::getRayPos(Ogre::Ray &mouseRay, Ogre::Vector3 &pos)
{
   std::pair<bool, Ogre::Vector3> result = m_pTerrainInfo->rayIntersects(mouseRay);
   if(result.first) {
      pos = result.second;
      return true;
   }

   return false;
}

void CTerrain::paint(Ogre::Ray &mouseRay, int iChosenTexture, ET::Brush editBrush, float fBrushIntensity)
{
   // since ETM is no longer a scene manager, we don't use a ray scene query,
   // but instead query the terrain info directly
   std::pair<bool, Ogre::Vector3> result = m_pTerrainInfo->rayIntersects(mouseRay);
   if(result.first) {
      int x = m_pTerrainInfo->posToVertexX(result.second.x);
      int z = m_pTerrainInfo->posToVertexZ(result.second.z);

      // now use the splatting manager to update the coverage maps
      m_pSplatMgr->paint(iChosenTexture, x, z, editBrush, fBrushIntensity);
   }
}

void CTerrain::deform(Ogre::Ray &mouseRay, ET::Brush editBrush, float fBrushIntensity)
{
   std::pair<bool, Ogre::Vector3> result = m_pTerrainInfo->rayIntersects(mouseRay);
   if(result.first) {
      int x = m_pTerrainInfo->posToVertexX(result.second.x);
      int z = m_pTerrainInfo->posToVertexZ(result.second.z);

      // now use the splatting manager to update the coverage maps
      m_pTerrainMgr->deform(x, z, editBrush, fBrushIntensity);
   }
}

void CTerrain::updateLightmap()
{
   Ogre::Image lightmap;
   ET::createTerrainLightmap(*m_pTerrainInfo, lightmap, 128, 128, Ogre::Vector3(1, -1, 1), Ogre::ColourValue(1,1,1),
                             Ogre::ColourValue(0.3f, 0.3f,  0.3f));

   // get our dynamic texture and update its contents
   Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("ETLightmap");
   tex->getBuffer(0, 0)->blitFromMemory(lightmap.getPixelBox(0, 0));
}

void CTerrain::saveTerrain(int id)
{
   // just for demonstration, we'll save anything we can
   // start with the terrain
   char buf[256] ;
   Ogre::Image image;
   ET::saveHeightmapToImage(*m_pTerrainInfo, image);
   sprintf(buf, "../Media/ET/ETterrain%d.png", id);
   image.save(buf);

   // now save the splatting maps
   for(unsigned int i = 0; i < m_pSplatMgr->getNumMaps(); ++i)
   {
      m_pSplatMgr->saveMapToImage(i, image);

      sprintf(buf, "../Media/ET/ETcoverage%d_%d.png", id, i);
      image.save(buf);
   }

   // now the lightmap
   Ogre::Image lightmap;
   ET::createTerrainLightmap(*m_pTerrainInfo, lightmap, 512, 512, Ogre::Vector3(1, -1, 1), Ogre::ColourValue(1,1,1),
                             Ogre::ColourValue(0.3f, 0.3f,  0.3f));
   sprintf(buf, "../Media/ET/ETlightmap%d.png", id);
   lightmap.save(buf);

   // generate a base texture for this terrain (could be used for older hardware instead of splatting)
   // create an ImageList of our splatting textures.
   ET::ImageList textures(6);
   for(int i = 0; i < 6; ++i)
      textures[i].load("splatting" + Ogre::StringConverter::toString(i) + ".png", "ET");

   // create the base texture
   Ogre::Image baseTexture;
   m_pSplatMgr->createBaseTexture(baseTexture, 512, 512, textures, 20, 20);
   sprintf(buf, "../Media/ET/ETbase%d.png", id);
   baseTexture.save(buf);

   // finally create a minimap using the lightmap and the generated base texture
   Ogre::Image minimap = ET::createMinimap(baseTexture, lightmap);
   sprintf(buf, "../Media/ET/ETminimap%d.png", id);
   minimap.save(buf);
}

void CTerrain::loadTerrain(int id)
{
   // now we revert the process and load the data back from disk
   // recreate terrain...
   m_pTerrainMgr->destroyTerrain();

   char buf[256] ;
   Ogre::Image image;
   sprintf(buf, "ETterrain%d.png", id);
   image.load(buf, "ET");

   ET::TerrainInfo info;
   ET::loadHeightmapFromImage(info, image);
   info.setExtents(Ogre::AxisAlignedBox(0, 0, 0, 900, 0, 900));
   m_pTerrainMgr->createTerrain(info);
   m_pTerrainInfo = &(m_pTerrainMgr->getTerrainInfo());

   // now load the splatting maps
   for(unsigned int i = 0; i < m_pSplatMgr->getNumMaps(); ++i)
   {
      sprintf(buf, "ETcoverage%d_%d.png", id, i);
      image.load(buf, "ET");
      m_pSplatMgr->loadMapFromImage(i, image);
   }

   // update the lightmap
   updateLightmap();
}

void CTerrain::release()
{
   delete m_pTerrainMgr;
   m_pTerrainMgr = NULL;

   delete m_pSplatMgr;
   m_pSplatMgr = NULL;
}