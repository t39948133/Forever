/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSoundManager.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/31 */
#ifndef _CSOUNDMANAGER_H_
#define _CSOUNDMANAGER_H_
#ifdef _GAMESOUND_
#include "Common.h"
#include "sound_man.h"

class CSoundManager
{
   public:
      /** @brief 取得CSoundManager實體物件
        * @return CSoundManager實體物件 */
      static CSoundManager* getInstance();

      /** @brief 釋放CSoundManager實體物件 */
      static void releaseInstance();

      void work();

      /** @brief 播放背景音樂
        * @param bgmFile 背景音樂檔名
        * @param bLoop   是否要循環播放 */
      void playBGM(std::string bgmFile, bool bLoop);

      /** @brief 關掉背景音樂 */
      void stopBGM();

      /** @brief 播放音效
        * @param soundFile 音效檔名 */
      void playSound(std::string soundFile);

   private:
      CSoundManager();
      ~CSoundManager();

      static CSoundManager *m_pInstance;  // CSoundManager實體物件

      SoundMan *m_pSoundMan;
};

#endif  // #ifdef _GAMESOUND_
#endif  // #ifndef _CSOUNDMANAGER_H_