/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlaySoundNotifyListener.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/31 */
#ifndef _IPLAYSOUNDNOTIFYLISTENER_H_
#define _IPLAYSOUNDNOTIFYLISTENER_H_
#include "Common.h"

class IPlaySoundNotifyListener
{
   public:
      virtual void notifyPlaySound(std::string soundFile) = 0;
};

#endif  // #ifndef _IDRAWWEAPONNOTIFYLISTENER_H_