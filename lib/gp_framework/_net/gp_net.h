#ifndef _GP_NET_H_
#define _GP_NET_H_

#include <RakPeerInterface.h>
//#include <RakNetTypes.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <memory\gp_memory_queue.h>

#include <list>

namespace GP
{

typedef GMemoryQueue <unsigned int, 1024> MemoryBuffer ;

//只做連線建立
class NetStream
{
private:
	bool bServer ;

	enum {MAX_CONNECTION = 99} ;
	RakNet::RakPeerInterface *pPeer;

	RakNet::Packet *pPacket ;

	RakNet::RakNetGUID guid ;
	RakNet::SystemAddress clientID ;//client的編號

	MemoryBuffer recvBuffer ;

public:

	bool checkID (RakNet::RakNetGUID)const ;
	void pushRecvData (RakNet::Packet*) ;

//	bool startListen (int port) ;

	bool startConnect (const char* ip, int port) ;

	void send (const char* pdata, int dataSize) ;

private:
	void work () ;

public:
	const char* getPacket (unsigned int* pSize = NULL) ;

//	void close () ;

	NetStream () ;
	NetStream (RakNet::RakPeerInterface*, const RakNet::SystemAddress&,
				RakNet::RakNetGUID) ;
	~NetStream () ;
} ;

//###################################

typedef std::list <NetStream*> VP_NET_STREAM ;

class NetListener
{
private:
	enum {MAX_CONNECTION = 99} ;
	RakNet::RakPeerInterface *pPeer;

	RakNet::Packet *pPacket ;

	//網路連線的
	VP_NET_STREAM vpNewStream ;//新連線的
	VP_NET_STREAM vpWorkStream ;//已經運作中的

public:
	NetListener () ;
	~NetListener () ;

	bool startListen (int port) ;

private:
	bool pushRecvData (RakNet::Packet*, VP_NET_STREAM&) ;
	void pushRecvData (RakNet::Packet*) ;

	void work () ;//
public:

	//取得連線
	NetStream* getNetStream () ;
} ;


}


#endif