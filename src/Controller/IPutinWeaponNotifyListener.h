/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPutinWeaponNotifyListener.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/29 */
#ifndef _IPUTINWEAPONNOTIFYLISTENER_H_
#define _IPUTINWEAPONNOTIFYLISTENER_H_
#include "Common.h"

class IPutinWeaponNotifyListener
{
   public:
      virtual void notifyPutinWeapon() = 0;
};

#endif  // #ifndef _IPUTINWEAPONNOTIFYLISTENER_H_