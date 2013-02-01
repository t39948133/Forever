//#include "stdafx.h"
#include "sound_man.h"

//代表一個聲音
bool Sound3D::IsEnd ()//是否結束
{
	if (uiBuffer != INVALID_SOURCE)
	{
		ALint iState ;
		alGetSourcei( uiSource, AL_SOURCE_STATE, &iState);
		return (iState != AL_PLAYING) ;
	}

	return true ;
}

bool Sound3D::Load (const char* fname)
{
	Release () ;

	// Generate an AL Buffer
	alGenBuffers( 1, &uiBuffer );

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)fname, uiBuffer))
	{
		// Clean up by deleting Source(s) and Buffer(s)
		alDeleteBuffers(1, &uiBuffer);
		uiBuffer = INVALID_SOURCE ;

		return false ;
	}

	// Generate a Source to playback the Buffer
    alGenSources( 1, &uiSource );

	// Attach Source to Buffer
	alSourcei( uiSource, AL_BUFFER, uiBuffer );

	return true ;
}

void Sound3D::Replay ()
{
	// Attach Source to Buffer
	if (uiBuffer != INVALID_SOURCE)
		alSourcei( uiSource, AL_BUFFER, uiBuffer );
}

bool Sound3D::Play (const char* fname)
{
	Release () ;

	if (!Load (fname))
		return false ;

	// Play Source
    alSourcePlay( uiSource );

	return true ;
}

bool Sound3D::Play3D (const char* fname, float x, float y, float z,
					  bool bLoop)
{
	//先釋放音效
	Release () ;

	if (!Load (fname))
		return false ;

	//修改座標
	alSource3f(uiSource, AL_POSITION, x, y, z) ;
	//音量減半範圍
	alSourcef (uiSource, AL_REFERENCE_DISTANCE, 300) ;
	//無聲範圍
	alSourcef (uiSource, AL_MAX_DISTANCE, 600) ;

	//loop
	if (bLoop)
		alSourcei( uiSource, AL_LOOPING, AL_TRUE );
	else
		alSourcei( uiSource, AL_LOOPING, AL_FALSE );

	// Play Source
    alSourcePlay( uiSource );


	return true ;
}

void Sound3D::Release ()
{
	if (uiBuffer != INVALID_SOURCE)
	{
		alSourceStop(uiSource);
		alDeleteSources(1, &uiSource);
		alDeleteBuffers(1, &uiBuffer);

		uiSource = INVALID_SOURCE ;
	}
}

Sound3D::Sound3D ():uiBuffer(INVALID_SOURCE)
{
}

//#########################################################
//#########################################################
//#########################################################

//串流聲音
//用來撥放大型檔案
void StreamSound::Work ()
{
	if (pData == NULL)
		return ;

	ALint iBuffersProcessed, iQueuedBuffers ;

	// Request the number of OpenAL Buffers have been processed (played) on the Source
	alGetSourcei(uiSource, AL_BUFFERS_PROCESSED, &iBuffersProcessed);

	// Keep a running count of number of buffers processed (for logging purposes only)
	iTotalBuffersProcessed += iBuffersProcessed;

	// For each processed buffer, remove it from the Source Queue, read next chunk of audio
	// data from disk, fill buffer with new data, and add it to the Source Queue
	while (iBuffersProcessed)
	{
		// Remove the Buffer from the Queue.  (uiBuffer contains the Buffer ID for the unqueued Buffer)
		uiBuffer = 0;
		alSourceUnqueueBuffers(uiSource, 1, &uiBuffer);

		// Read more audio data (if there is any)
		pWaveLoader->ReadWaveData(WaveID, pData, ulBufferSize, &ulBytesWritten);
		if (ulBytesWritten)
		{
			// Copy audio data to Buffer
			alBufferData(uiBuffer, ulFormat, pData, ulBytesWritten, ulFrequency);
			// Queue Buffer on the Source
			alSourceQueueBuffers(uiSource, 1, &uiBuffer);
		}

		iBuffersProcessed--;
	}

	// Check the status of the Source.  If it is not playing, then playback was completed,
	// or the Source was starved of audio data, and needs to be restarted.
	alGetSourcei(uiSource, AL_SOURCE_STATE, &iState);
	if (iState != AL_PLAYING)
	{
		// If there are Buffers in the Source Queue then the Source was starved of audio
		// data, so needs to be restarted (because there is more audio data to play)
		alGetSourcei(uiSource, AL_BUFFERS_QUEUED, &iQueuedBuffers);
		if (iQueuedBuffers)
		{
			alSourcePlay(uiSource);
		}
		else
		{
			if (bLoop)
			{
				// Set read position to start of audio data
				pWaveLoader->SetWaveDataOffset(WaveID, 0);

				// Fill all the Buffers with audio data from the wavefile
				for (ALint iLoop = 0; iLoop < NUMBUFFERS; iLoop++)
				{
					if (SUCCEEDED(pWaveLoader->ReadWaveData(WaveID, pData, ulBufferSize, &ulBytesWritten)))
					{
						alBufferData(uiBuffers[iLoop], ulFormat, pData, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(uiSource, 1, &uiBuffers[iLoop]);
					}
				}

				// Start playing source
				alSourcePlay(uiSource);
				iTotalBuffersProcessed = 0;

			// Finished playing
			}
		}
	}
}

void StreamSound::Stop ()
{
	if (pData != NULL)
	{
		alSourceStop(uiSource);
	}
}

bool StreamSound::Play (const char* fname, bool bloop)
{
	//先釋放掉本來的
	bLoop = bloop ;
	Release () ;

    // Generate some AL Buffers for streaming
	alGenBuffers( NUMBUFFERS, uiBuffers );

	// Generate a Source to playback the Buffers
    alGenSources( 1, &uiSource );

	// Create instance of WaveLoader class
	pWaveLoader = new CWaves();
	if ((pWaveLoader) && (SUCCEEDED(pWaveLoader->OpenWaveFile(fname, &WaveID))))
	{
		pWaveLoader->GetWaveSize(WaveID, &ulDataSize);
		pWaveLoader->GetWaveFrequency(WaveID, &ulFrequency);
		pWaveLoader->GetWaveALBufferFormat(WaveID, &alGetEnumValue, &ulFormat);

		// Queue 250ms of audio data
		pWaveLoader->GetWaveFormatExHeader(WaveID, &wfex);
		ulBufferSize = wfex.nAvgBytesPerSec >> 2;

		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
		ulBufferSize -= (ulBufferSize % wfex.nBlockAlign);

		if (ulFormat != 0)
		{
			pData = malloc(ulBufferSize);
			if (pData)
			{
				// Set read position to start of audio data
				pWaveLoader->SetWaveDataOffset(WaveID, 0);

				// Fill all the Buffers with audio data from the wavefile
				for (ALint iLoop = 0; iLoop < NUMBUFFERS; iLoop++)
				{
					if (SUCCEEDED(pWaveLoader->ReadWaveData(WaveID, pData, ulBufferSize, &ulBytesWritten)))
					{
						alBufferData(uiBuffers[iLoop], ulFormat, pData, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(uiSource, 1, &uiBuffers[iLoop]);
					}
				}

				// Start playing source
				alSourcePlay(uiSource);
				iTotalBuffersProcessed = 0;

				return true ;
			}
		}
	}

	//失敗就release
	Release () ;
	return false ;
}

void StreamSound::Release ()
{
	if (pData != NULL)
	{
		free(pData);
		pData = NULL ;

		// Stop the Source and clear the Queue
		alSourceStop(uiSource);
		alSourcei(uiSource, AL_BUFFER, 0);

	    // Clean up buffers and sources
		alDeleteSources( 1, &uiSource );
		alDeleteBuffers( NUMBUFFERS, uiBuffers );
	}

	// Close Wave Handle
	if (pWaveLoader != NULL)
	{
		pWaveLoader->DeleteWaveFile(WaveID);
		delete pWaveLoader ;
		pWaveLoader = NULL ;
	}

}

StreamSound::StreamSound ():ulDataSize(0),ulFrequency(0),
							ulFormat(0),ulBufferSize(0),
							ulBytesWritten(0),pData(NULL),
							pWaveLoader(NULL)
{
}

//#########################################################
//#########################################################
//#########################################################

void SoundMan::PlaySound3D (const char* fname, float x, float y, float z,
							bool bLoop)
{
	//產生音效
	ListSound.push_back (Sound3D ()) ;
	ListSound.back ().Play3D (fname, x, y, z, bLoop) ;
}

void SoundMan::PlaySound (const char* fname)
{
	//產生音效
	ListSound.push_back (Sound3D ()) ;
	ListSound.back ().Play (fname) ;
}

void SoundMan::StopBGM ()//關掉背景音樂
{
	BGM.Stop () ;
}

void SoundMan::PlayBGM (const char* fname, bool bloop)
{
	BGM.Play (fname, bloop) ;
}

void SoundMan::SetListender (float x, float y, float z, 
							 float dx, float dy, float dz)
{
	float v[3] ;
	v[0] = x ;
	v[1] = y ;
	v[2] = z ;

	//位置
	alListenerfv(AL_POSITION, v) ;

	v[0] = dx ;
	v[1] = dy ;
	v[2] = dz ;

	//方向
	alListenerfv(AL_ORIENTATION, v) ;
}

void SoundMan::Work ()
{
	//檢查播完的音效後刪除
	LIST_SOUND::iterator pi = ListSound.begin () ;
	while (pi != ListSound.end ())
	{
		if (pi->IsEnd ())
		{
			pi->Release () ;
			pi = ListSound.erase (pi) ;
		}else
			++ pi ;
	}

	BGM.Work () ;
}

bool SoundMan::Init ()
{
	ALFWInit();

	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
		return false ;
	}

	return true ;
}

void SoundMan::Release ()
{
	BGM.Release () ;

	ALFWShutdownOpenAL();

	ALFWShutdown();
}
