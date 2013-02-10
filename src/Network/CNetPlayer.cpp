#include "CNetPlayer.h"

CNetPlayer::CNetPlayer()
{
   m_state = -1;
   m_pPlayer = NULL;
   m_pNetStream = new GP::NetStream();
   m_netID = -1;
}

CNetPlayer::~CNetPlayer()
{
   if(m_pNetStream != NULL) {
      m_pNetStream->stopConnection();
      delete m_pNetStream;
      m_pNetStream = NULL;
   }
}