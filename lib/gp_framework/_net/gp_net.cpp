#include "gp_net.h"

namespace GP
{
	bool NetStream::checkID (RakNet::RakNetGUID id)const
	{
		return guid == id ;
	}

	void NetStream::pushRecvData (RakNet::Packet* pPkt)
	{
		recvBuffer.PushBlock (pPkt->data+1, pPkt->length-1) ;
	}

	/*
	bool NetStream::startListen (int port)
	{
		pPeer->SetTimeoutTime(5000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		RakNet::SocketDescriptor socketDescriptor(port,0);
		socketDescriptor.socketFamily=AF_INET;
		pPeer->SetMaximumIncomingConnections(MAX_CONNECTION);
		RakNet::StartupResult sr;
		sr=pPeer->Startup(MAX_CONNECTION, &socketDescriptor, 1);

		return sr == RakNet::RAKNET_STARTED ;
	}
	*/

	bool NetStream::startConnect (const char* ip, int port)
	{
		pPeer->SetTimeoutTime(5000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		RakNet::SocketDescriptor socketDescriptor(0,0);
		socketDescriptor.socketFamily=AF_INET;
		RakNet::StartupResult sr;
		sr=pPeer->Startup(MAX_CONNECTION, &socketDescriptor, 1);
		if (sr!=RakNet::RAKNET_STARTED)
		{
			//fail
			return false;
		}
		pPeer->SetSplitMessageProgressInterval(10000); // Get ID_DOWNLOAD_PROGRESS notifications
		//	client->SetPerConnectionOutgoingBandwidthLimit(28800);

//		printf("Started client on %s\n", client->GetMyBoundAddress().ToString(true));

		pPeer->Connect(ip, port, 0, 0);
		return true ;
	}

	void NetStream::send (const char* pdata, int dataSize)
	{
		//資料,要
		enum {MAX_DATA = 1024-1} ;
		assert (dataSize <= MAX_DATA) ;
		char buf[MAX_DATA+1] ;

		//保留一個byte,給系統做辨識用
		buf[0] = 'a' ;//讓資料正常...
		memcpy (buf+1, pdata, dataSize) ;

		if (bServer)
		{
			pPeer->Send ((const char*)buf, dataSize+1, 
				HIGH_PRIORITY, RELIABLE_ORDERED, 0, 
				clientID, true);
		}else
		{
			//client -> server
			pPeer->Send ((const char*)buf, dataSize+1, 
				HIGH_PRIORITY, RELIABLE_ORDERED, 0, 
				RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}
	}

	void NetStream::work ()
	{
		if (pPacket != NULL)
		{
			//回收目前的packet
			pPeer->DeallocatePacket(pPacket) ;
			pPacket = NULL ;
		}

		pPacket = pPeer->Receive () ;
		if (pPacket != NULL)
		{
			unsigned char id = pPacket->data[0];
//			if (pSize != NULL)
//				*pSize = pPacket->length-1 ;

			// Check if this is a network message packet
			switch (id)
			{
			case ID_NEW_INCOMING_CONNECTION:
				//新連線
				break ;
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				break;			
			case ID_CONNECTION_ATTEMPT_FAILED:
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				break;
			case ID_INVALID_PASSWORD:
				break;
			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				// This tells the client they have connected
				break;
			default:
				// It's a client, so just show the message
//				return (const char*)pPacket->data+1 ;
				pushRecvData (pPacket) ;
				break;
			}
		}
	}

	const char* NetStream::getPacket (unsigned int* pSize)
	{
		work () ;
		return (const char*)recvBuffer.PopBlock (*pSize) ;
	}

	/*
	void NetStream::close ()
	{
		pPeer->Shutdown(300);
	}
	*/

	NetStream::NetStream ():pPeer(NULL),pPacket(NULL),bServer(false)
	{
		pPeer = RakNet::RakPeerInterface::GetInstance() ;
	}

	NetStream::NetStream (RakNet::RakPeerInterface* pp, 
		const RakNet::SystemAddress& id, RakNet::RakNetGUID uid):pPeer(pp),pPacket(NULL),
		bServer(true),clientID(id),guid(uid)
	{
	}

	NetStream::~NetStream ()
	{
		if (pPeer != NULL)
		{
			if (pPacket != NULL)
			{
				//回收目前的packet
				pPeer->DeallocatePacket(pPacket) ;
			}

			RakNet::RakPeerInterface::DestroyInstance(pPeer) ;
			pPeer = NULL ;
		}
	}
//###############################

	NetListener::NetListener ():pPeer(NULL),pPacket(NULL)
	{
		pPeer = RakNet::RakPeerInterface::GetInstance() ;
	}

	NetListener::~NetListener ()
	{
		if (pPeer != NULL)
		{
			if (pPacket != NULL)
			{
				//回收目前的packet
				pPeer->DeallocatePacket(pPacket) ;
			}

			RakNet::RakPeerInterface::DestroyInstance(pPeer) ;
			pPeer = NULL ;
		}
	}

	bool NetListener::startListen (int port)
	{
		pPeer->SetTimeoutTime(5000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		RakNet::SocketDescriptor socketDescriptor(port,0);
		socketDescriptor.socketFamily=AF_INET;
		pPeer->SetMaximumIncomingConnections(MAX_CONNECTION);
		RakNet::StartupResult sr;
		sr=pPeer->Startup(MAX_CONNECTION, &socketDescriptor, 1);

		return sr == RakNet::RAKNET_STARTED ;
	}

	
	bool NetListener::pushRecvData (RakNet::Packet* pPkt, VP_NET_STREAM& vpNS)
	{
		VP_NET_STREAM::iterator pi = vpNS.begin () ;//新連線的
		while (pi != vpNS.end ())
		{
			NetStream* pNS = *pi ;
			if (pNS->checkID (pPkt->guid))
			{
				//是同一個
				pNS->pushRecvData (pPkt) ;
				return true ;
			}
			++ pi ;
		}

		return false ;
	}

	void NetListener::pushRecvData (RakNet::Packet* pPkt)
	{
		if (pushRecvData (pPkt, vpNewStream) == false)
		{
			pushRecvData (pPkt, vpWorkStream) ;
		}

		/*
			pPkt->guid,
									(const char*)pPkt->data+1, 
									pPkt->length-1
									*/
	}

	void NetListener::work ()
	{
		if (pPacket != NULL)
		{
			//回收目前的packet
			pPeer->DeallocatePacket(pPacket) ;
			pPacket = NULL ;
		}

		pPacket = pPeer->Receive () ;
		if (pPacket != NULL)
		{
			unsigned char id = pPacket->data[0];
//			if (pSize != NULL)
//				*pSize = pPacket->length-1 ;

			// Check if this is a network message packet
			switch (id)
			{
			case ID_NEW_INCOMING_CONNECTION:
				//新連線
				{
//					RakNet::SystemAddress clientID ;
//					clientID = pPacket->systemAddress; // Record the player ID of the client
					NetStream* pNS = new NetStream (pPeer, 
							pPacket->systemAddress,
							pPacket->guid) ;
					vpNewStream.push_back (pNS) ;
				}
				break ;
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				break;			
			case ID_CONNECTION_ATTEMPT_FAILED:
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				break;
			case ID_INVALID_PASSWORD:
				break;
			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				// This tells the client they have connected
				break;
			default:
				// It's a client, so just show the message
//				return (const char*)pPacket->data+1 ;
				{
					//把資料放進NetStream的buffer
					pushRecvData (pPacket) ;
				}
				break;
			}

//			return NULL ;
		}else
		{
//			return NULL ;
		}
	}

	//取得連線
	NetStream* NetListener::getNetStream ()
	{
		work () ;

		NetStream* pNS = NULL ;
		if (vpNewStream.size () > 0)
		{
			pNS = vpNewStream.front () ;
			vpNewStream.pop_front () ;

			//已經被取用了
			vpWorkStream.push_back (pNS) ;
		}

		return pNS ;
	}

//############################

}