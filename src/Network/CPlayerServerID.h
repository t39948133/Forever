#ifndef _CPLAYERSERVERID_H_
#define _CPLAYERSERVERID_H_
#include "CPlayer.h"

#include <network\gp_socket.h>

class CPlayerServerID : public CPlayer
{
   public:
      CPlayerServerID(std::string machineName, std::string strName, long long uid, char level) : CPlayer(machineName, strName, uid, level)
      {
      }

      GP::NetStream *m_pNetStream;
};

#endif  // #ifndef _CPLAYERSERVERID_H_