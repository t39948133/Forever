/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IAttackNotifyListener.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/18 */
#ifndef _IATTACKNOTIFYLISTENER_H_
#define _IATTACKNOTIFYLISTENER_H_
#include "Common.h"

class IAttackNotifyListener
{
   public:
      virtual void notifyAttack() = 0;
};

#endif  // #ifndef _IATTACKNOTIFYLISTENER_H_