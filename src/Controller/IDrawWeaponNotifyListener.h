/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IDrawWeaponNotifyListener.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/29 */
#ifndef _IDRAWWEAPONNOTIFYLISTENER_H_
#define _IDRAWWEAPONNOTIFYLISTENER_H_
#include "Common.h"

class IDrawWeaponNotifyListener
{
   public:
      virtual void notifyDrawWeapon() = 0;
};

#endif  // #ifndef _IDRAWWEAPONNOTIFYLISTENER_H_