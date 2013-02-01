/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSoundManager.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/31 */
#include "CSoundManager.h"

CSoundManager *CSoundManager::m_pInstance = NULL;

CSoundManager* CSoundManager::getInstance()
{
   if(m_pInstance == NULL)
      m_pInstance = new CSoundManager();

   return m_pInstance;
}

void CSoundManager::releaseInstance()
{
   if(m_pInstance != NULL) {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

void CSoundManager::work()
{
   m_pSoundMan->Work();
}

void CSoundManager::playBGM(std::string bgmFile, bool bLoop)
{
   m_pSoundMan->PlayBGM(bgmFile.c_str(), bLoop);
}

void CSoundManager::stopBGM()
{
   m_pSoundMan->StopBGM();
}

void CSoundManager::playSound(std::string soundFile)
{
   m_pSoundMan->PlaySound(soundFile.c_str());
}

CSoundManager::CSoundManager()
{
   m_pSoundMan = new SoundMan();
   m_pSoundMan->Init();
}

CSoundManager::~CSoundManager()
{
   if(m_pSoundMan != NULL) {
      m_pSoundMan->Release();
      delete m_pSoundMan;
      m_pSoundMan = NULL;
   }
}