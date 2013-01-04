#ifndef _GP_SOCKET_H_
#define _GP_SOCKET_H_

#include <winsock.h>

#include <list>

#include <memory\gp_memory_queue.h>

//#########################################################
//#########################################################
//#########################################################

namespace GP
{

class NetAddress
{
public:
	BYTE A0, A1, A2, A3 ;
	WORD Port ;

	void getIPPort (char*, WORD) ;
	void setIPPort (const char*) ;
	void setIP (const char*) ;

	void release () ;
} ;

//#########################################################
//#########################################################
//#########################################################
class AcceptSocket
{
private:
	SOCKET CurSocket ;//目前的socket,用來listen,或connect

public:
	bool isValid () ;

	void setSocket (SOCKET ckt) ;

	SOCKET removeSocket () ;

	void release () ;

	AcceptSocket () ;

	~AcceptSocket () ;
} ;

typedef std::list <AcceptSocket> LIST_ACCEPT_SOCKET ;

//專門用來listen
class NetStream ;
class NetListener
{
private:
	SOCKET CurSocket ;//目前的socket,用來listen,或connect

	LIST_ACCEPT_SOCKET ListAcceptSocket ;

private:
	void procAccept () ;

private:
	bool listen () ;//server用(TCP)

public:
	bool isAccepted () ;
	void transferAcceptStream (NetStream&) ;//把accecpt的socket傳出來使用

private:
	bool open (const char*, WORD, bool) ;//client & server使用,
public:
	bool startListen (WORD) ;//TCP/server用

private:
	void closeSocket () ;//關閉socket

public:
	void release () ;

	NetListener () ;
	~NetListener () ;
} ;

//#########################################################
//#########################################################
//#########################################################

enum {MAX_BUFFER_SIZE = 1024*10} ;
enum {MAX_PACKAGE_SIZE = 1024} ;
typedef GLocalMemory <MAX_PACKAGE_SIZE> NetBuffer ;

//點對點
class NetStream
{
private:
	SOCKET CurSocket ;//目前的socket,用來listen,或connect
	static HWND WorkWindow ;

protected:
	GMemoryQueue <DWORD, MAX_BUFFER_SIZE> SendBuffer, RecvBuffer ;

public:
	//旗標
	struct _FLAG
	{
		union _BIT
		{
			struct
			{
				BYTE bLink:1 ;//連線中
				BYTE bTryConnect:1 ;//嘗試連線
				BYTE bCanSend:1 ;//可以送資料了
				BYTE bWaitClose:1 ;//等待關閉的階段
			} ;

			BYTE Memory ;
		} BIT ;

		void Reset ()
		{
			BIT.Memory = 0 ;
		}
	} Flag ;

	BYTE _EndTimeRate ;

public:
	static void fnInitShareData (HWND) ;

private:
public:
	//address
	static bool getHostAddress (char*, WORD) ;
	static bool getHostAddress (NetAddress&) ;
	bool getAddressPort (char*, WORD, WORD&) ;
	bool getAddressPort (char*, WORD) ;
	bool getAddressPort (NetAddress&) ;
	bool getPeerAddressPort (char*, WORD) ;
	bool getPeerAddressPort (NetAddress&) ;
	bool getPeerAddress(char*, WORD);

	//state
	bool isConnected () ;

private:
	DWORD unBufSend (const void*, DWORD, NetAddress*) ;
	bool bufSend (const void*, DWORD, NetAddress*) ;
public:
	void send (const void*, DWORD) ;
private:
	DWORD getFullPackage (void*, DWORD) ;

public:
	bool getFullPackage (NetBuffer&) ;

private:
	void* peekRecvBuffer (DWORD&) ;
	void clearRecvBuffer () ;

public:

	void setAcceptStream (SOCKET) ;

	bool procPackage () ;

	bool connect (const NetAddress&) ;//client用(TCP)
	bool connect (const char*, WORD) ;//client用(TCP)

private:
	bool open (const char*, WORD, bool) ;//client & server使用,
public:
	void startConnect (const NetAddress&) ;//TCP/client用

	void stopConnection () ;//停止連線

	void release () ;

	NetStream () ;
	~NetStream () ;
} ;

}

#endif