#ifndef _GP_MEMORY_QUEUR_H
#define _GP_MEMORY_QUEUR_H

#include <assert.h>
//#include <g_base_type.h>

//#include <g_small_obj_allocator.h>

//#include <g_queue.h>

//用來存放記憶體區塊
//一塊一塊連接在一起
//事實上完全是連續的

//先丟進去的
//會先取出來

//可以用來製作事件的queue

//請注意,這個物件可能會被用在多執行緒
//這時候要非常小心

template <class MEMORY_SIZE_TYPE, DWORD ALLOCATE_MEMORY_SIZE>
class GMemoryQueue//:public GSmallAlloc <BYTE, 1024>
{
private:
	//所有的記憶體都配置在這裡
	BYTE* pAllMemory ;

	DWORD CurBeginPos ;//目前資料開始的地方
	DWORD CurEndPos ;//目前資料結束的地方
	DWORD MaxMemorySize ;//目前配置的大小

	DWORD MoveMemoryCount ;//發生移動資料的次數
	DWORD ReAllocateCount ;//發生重新配置的次數
	DWORD MemoryChangeCount ;//記憶體有被改變位置的次數

private:
	void AppendMemory (DWORD newMaxSize)
	{
//		THREA_SAFE_CHECK () ;
		//記憶體不夠用了,應該要配置更大的
		//而且要以配置的單位大小來配置
		//如果一口氣配很多個,可能會超過一次能配置的量
		//這時候要配置足夠的量

		BYTE* pOriMem = pAllMemory ;

		int minBlockCount = newMaxSize/ALLOCATE_MEMORY_SIZE ;
		if (newMaxSize%ALLOCATE_MEMORY_SIZE != 0)
			minBlockCount = newMaxSize/ALLOCATE_MEMORY_SIZE+1 ;

		MaxMemorySize = minBlockCount*ALLOCATE_MEMORY_SIZE ;
		assert (MaxMemorySize >= newMaxSize) ;
		if (pAllMemory != NULL)
			pAllMemory = (BYTE*)realloc (pAllMemory, MaxMemorySize) ;
		else
			pAllMemory = (BYTE*)malloc (MaxMemorySize) ;

		//無法配置記憶體
		if (pAllMemory == NULL)
		{
			assert (pAllMemory != NULL) ;
//			throw GMemoryAllocateFail () ;
		}

		ReAllocateCount ++ ;

		if (pOriMem !=  pAllMemory)
			MemoryChangeCount ++ ;
	}

public:
	DWORD getAllDataSize ()
	{
		return CurEndPos-CurBeginPos ;
	}

	DWORD getCurEndPos ()
	{
		return CurEndPos ;
	}

	//如果pData == NULL
	//代表只是想push一個空間出來而已
	void* pushStream (DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;
		//不可以在這邊作資料move的動作
		//因為可能會讓傳出來的指標錯誤

		//只push資料,不會附加資料的大小資訊
		assert (dataSize > 0) ;

		//新的大小含有資訊
		DWORD newEndPos = CurEndPos+dataSize ;

		if (newEndPos > MaxMemorySize)
		{
			//記憶體不足,要配置新的
			AppendMemory (newEndPos) ;
			assert (MaxMemorySize >= newEndPos) ;
		}

		//複製資料
		BYTE* pWritePos = pAllMemory+CurEndPos ;
		CurEndPos += dataSize ;

		assert (CurEndPos <= MaxMemorySize) ;

		return pWritePos ;
	}

	void* pushStream (const void* pData, DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;
		//不可以在這邊作資料move的動作
		//因為可能會讓傳出來的指標錯誤

		//只push資料,不會附加資料的大小資訊
		assert (dataSize > 0) ;

		/*
		//新的大小含有資訊
		DWORD newEndPos = CurEndPos+dataSize ;

		if (newEndPos > MaxMemorySize)
		{
			//記憶體不足,要配置新的
			AppendMemory (newEndPos) ;
			assert (MaxMemorySize >= newEndPos) ;
		}

		//複製資料
		BYTE* pWritePos = pAllMemory+CurEndPos ;
		*/

		void* pWritePos = pushStream (dataSize) ;
		if (pData != NULL)
			if (pWritePos != NULL)
				memcpy (pWritePos, pData, dataSize) ;
//		CurEndPos += dataSize ;

		assert (CurEndPos <= MaxMemorySize) ;

		return pWritePos ;
	}

	void alignMemory ()
	{
		//把記憶體的空位清除
		if (CurBeginPos > 0)//有空的地方
		{
			DWORD allDataSize = CurEndPos-CurBeginPos ;
			if (CurBeginPos  >= allDataSize)
			{
				//如果有足夠容量的大小可以把後面的資料往前移
				//就把資料往前移
				if (allDataSize > 0)
				{
					memmove (pAllMemory, pAllMemory+CurBeginPos, allDataSize) ;

					if (MoveMemoryCount < 0xffffffff)//不讓這個次數爆掉
						MoveMemoryCount ++ ;
				}
				CurEndPos -= CurBeginPos ;
				CurBeginPos = 0 ;
			}
		}

	}

	//push一整塊,會產生大小資訊
	void pushBlock (const void* pData, DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//警告,data不得超過定義的大小,否則會爆掉
		//利用轉型來確認資料沒有爆掉
		MEMORY_SIZE_TYPE tmpSize = (MEMORY_SIZE_TYPE)dataSize ;
		assert (tmpSize == dataSize) ;

		//進行資料移動,把整個stream往前移,這樣可以避免記憶體無限長大
		alignMemory () ;

		//紀錄大小
		pushStream (&dataSize, sizeof (tmpSize)) ;

		pushStream (pData, dataSize) ;

		assert (CurEndPos <= MaxMemorySize) ;
	}

	//從後方切除資料,不是從前方,請注意
	void popStreamTail (DWORD dataSize)
	{
		assert (dataSize <= (CurEndPos-CurBeginPos)) ;
		CurEndPos -= dataSize ;
	}

	void popStream (void* pData, DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//把資料抓出來
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		assert (allDataSize >= dataSize) ;

		memcpy (pData, pAllMemory+CurBeginPos, dataSize) ;
		CurBeginPos += dataSize ;
	}

	void cutStream (DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//把資料抓出來
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		assert (allDataSize >= dataSize) ;

		CurBeginPos += dataSize ;
	}

	void* peekStream (DWORD& dataSize)
	{
		if (CurEndPos > CurBeginPos)
		{
			dataSize = CurEndPos-CurBeginPos ;

			return pAllMemory+CurBeginPos ;
		}
		else
		{
			assert (CurEndPos == CurBeginPos) ;
			dataSize = 0 ;
			return NULL ;
		}
	}

	void* popStream (DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//把資料抓出來
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		assert (allDataSize >= dataSize) ;

		void* pDataPos = pAllMemory+CurBeginPos ;

		CurBeginPos += dataSize ;

		return pDataPos ;
	}

	bool hasBlock ()
	{
		//先檢查是否有足夠辨識大小的容量
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		if (allDataSize < sizeof (MEMORY_SIZE_TYPE))
		{
			//容量不夠
			return false ;
		}

		//取得大小
		MEMORY_SIZE_TYPE& curBlockSize = 
								*((MEMORY_SIZE_TYPE*)(pAllMemory+CurBeginPos)) ;


		//計算資料是否足夠
		if (curBlockSize > (allDataSize-sizeof (MEMORY_SIZE_TYPE)))
		{
			//容量不夠
			return false ;
		}

		return true ;
	}

	//pop出一整塊,如果沒有的話,傳回NULL
	void* popBlock (MEMORY_SIZE_TYPE& size)
	{
//		THREA_SAFE_CHECK () ;
		if (!hasBlock ())
			return NULL ;

		MEMORY_SIZE_TYPE& curBlockSize = 
								*((MEMORY_SIZE_TYPE*)(pAllMemory+CurBeginPos)) ;

		//容量足夠
		size = curBlockSize ;

		//實際的資料
		void* pData = pAllMemory+CurBeginPos+sizeof (MEMORY_SIZE_TYPE) ;
		CurBeginPos += sizeof (MEMORY_SIZE_TYPE)+curBlockSize ;

		return pData ;
	}

	void detach (BYTE* pMem, DWORD dataSize)
	{
		assert (pAllMemory == pMem) ;
		assert (CurEndPos == dataSize) ;
		assert (MaxMemorySize == dataSize) ;

		pAllMemory = NULL ;
		CurEndPos = 0 ;
		MaxMemorySize = 0 ;

		assert (CurBeginPos != 0) ;
		assert (ReAllocateCount == 0) ;
		assert (MemoryChangeCount == 0) ;
		assert (MoveMemoryCount == 0) ;

		CurBeginPos = 0 ;
	}

	//這是一個特殊的功能
	//用來對應一塊既存的記憶體
	///Detach一定要成對呼叫
	GMemoryQueue (BYTE* pMem, DWORD dataSize):pAllMemory(pMem),
															CurEndPos(dataSize),MaxMemorySize(dataSize),
															ReAllocateCount(0),CurBeginPos(0),
															MemoryChangeCount(0),MoveMemoryCount(0)
	{
	}

	GMemoryQueue ():pAllMemory(NULL),CurBeginPos(0),CurEndPos(0),
															MaxMemorySize(0),ReAllocateCount(0),
															MemoryChangeCount(0),MoveMemoryCount(0)
	{
	}

	void release ()
	{
		assert (CurEndPos <= MaxMemorySize) ;
//		assert (CurBeginPos == CurEndPos) ;
		if (pAllMemory != NULL)
		{
			assert (MaxMemorySize > 0) ;
			free (pAllMemory) ;
			pAllMemory = NULL ;
		}
		CurBeginPos = 0 ;
		CurEndPos = 0 ;
		MaxMemorySize = 0 ;
		ReAllocateCount = 0 ;
		MemoryChangeCount = 0 ;
		MoveMemoryCount = 0 ;
	}

	~GMemoryQueue ()
	{
		release () ;
	}
} ;

//#########################################################

template <DWORD MEMORY_SIZE>
class GLocalMemory//:public GSmallAlloc <BYTE, 1024>
{
private:
	char Buffer[MEMORY_SIZE] ;
	DWORD CurSize ;

public:
	void* getBuffer ()
	{
		return (void*) Buffer ;
	}

	DWORD getBufferSize ()
	{
		return MEMORY_SIZE ;
	}

	DWORD getDataSize ()
	{
		return CurSize ;
	}

	void setDataSize (DWORD size)
	{
		CurSize = size ;
	}
} ;

#endif