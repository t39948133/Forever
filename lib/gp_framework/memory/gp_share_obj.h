#ifndef _GP_SHARE_OBJ_H_
#define _GP_SHARE_OBJ_H_

#include <map>

namespace GP
{

template <class ID_TYPE, class OBJ_TYPE>
class ShareObj
{
private:
	OBJ_TYPE* pObj ;//指向的物件

	//共享的資料
	class ObjCounter:public OBJ_TYPE//, public ID_TYPE
	{
	private:
		int refCount ;

	public:
		OBJ_TYPE* incRef ()
		{
			refCount ++ ;
			return this ;
		}

		void decRef (OBJ_TYPE* po)
		{
			assert (po == this) ;
			refCount -- ;
		}

		bool hasRef ()
		{
			return refCount > 0 ;
		}

		ObjCounter ():refCount(0)
		{
		}
	} ;

	typedef std::map <ID_TYPE, ObjCounter> V_SHARE_OBJ ;
	static V_SHARE_OBJ vShareObj ;

public:
	void load (const ID_TYPE& id)
	{
	}

	void release ()
	{
		if (pObj != NULL)
		{
		}
	}

	ShareObj ():pObj(NULL)
	{
	}

	~ShareObj ()
	{
		//
		release ()
	}
} ;

} 

#endif