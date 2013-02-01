#ifndef _SOUND_MAN_H_
#define _SOUND_MAN_H_

#include "Framework.h"
#include "cwaves.h"

//聲音的資料,應該是共享的
//以後請修改sound buffer
//變成可以共享

//代表一個聲音
class Sound3D
{
private:
	enum {INVALID_SOURCE = 0xffffffff} ;
	ALuint      uiBuffer;
	ALuint      uiSource;  

public:

	bool IsEnd () ;//是否結束

	bool Load (const char*) ;
	void Replay () ;

	bool Play (const char*) ;
	bool Play3D (const char*, float, float, float, bool) ;

	void Release () ;
	Sound3D () ;
} ;

//串流聲音
//用來撥放大型檔案
class StreamSound
{
private:
	enum {NUMBUFFERS = 12} ;
	ALuint		    uiBuffers[NUMBUFFERS];
	ALuint		    uiSource;
	ALuint			uiBuffer;
	ALint			iState;
	CWaves*			pWaveLoader ;
	WAVEID			WaveID;
	ALint			iTotalBuffersProcessed ;
	WAVEFORMATEX	wfex;
	unsigned long	ulDataSize ;
	unsigned long	ulFrequency ;
	unsigned long	ulFormat ;
	unsigned long	ulBufferSize;
	unsigned long	ulBytesWritten;
	void *			pData ;
	bool bLoop ;

public:

	void Work () ;

	void Stop () ;
	bool Play (const char*, bool) ;
	void Release () ;

	StreamSound () ;
} ;

//#########################################################
//#########################################################
//#########################################################

#include <list>

//聲音的管理者
class SoundMan
{
private:
	StreamSound BGM ;//背景音樂,未必是音樂,也可以是環境音效

	//用來撥放音效
	typedef std::list <Sound3D> LIST_SOUND ;
	LIST_SOUND ListSound ;

public:
	//自動的撥放一個音效
	//在指定的座標
	//撥完就由soundman管理
	//呼叫不需要去處裡物件的管理
	void PlaySound3D (const char*, float, float, float, bool) ;
	void PlaySound (const char*) ;

	void StopBGM () ;//關掉背景音樂
	void PlayBGM (const char*, bool) ;//撥放背景音樂

	void SetListender (float, float, float, float, float, float) ;

	void Work () ;//定期呼叫work

	bool Init () ;
	void Release () ;
} ;

#endif