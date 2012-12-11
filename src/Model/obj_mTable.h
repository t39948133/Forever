#ifndef _OBJ_MTABLE_H_
#define _OBJ_MTABLE_H_

#include <vector>

template <class INFO>
class ObjTable
{

public:
	static bool read (const char* name)
	{
		FILE* pFile ; 
		fopen_s (&pFile, name, "rb") ;

		if (pFile != NULL)
		{
			int version = 0 ;
			fread (&version, sizeof (version), 1, pFile) ;

			int count ;
			fread (&count, sizeof (count), 1, pFile) ;

			vInfo.resize (count) ;

			V_INFO::iterator pi = vInfo.begin () ;
			while (pi != vInfo.end ())
			{
				(*pi)->read (pFile) ;
				++ pi ;
			}

			fclose (pFile) ;

			return true ;
		}else
			return false ;
	}
	static int getInfoCount ()
	{
		return vInfo.size () ;
	}
	static INFO getInfo (size_t id)
	{
		if (id >= 0 && id < vInfo.size ())
			return vInfo[id] ;
		else
			return NULL ;
	}
	static INFO addInfo (INFO tmp)
	{
		if(tmp == NULL)
			return NULL;
		vInfo.push_back (tmp) ;

		return (vInfo.back ()) ;
	}
	bool checkID (size_t id)
	{
		if (id < vInfo.size () && id >= 0)
			return true ;
		else
			return false ;
	}
	ObjTable ():ID(NO_ID)
	{
	}
	int getID ()
	{
		return ID ;
	}
	bool create (size_t i)
	{
		ID = i ;
		if (ID >= 0 && ID < vInfo.size ())
			return true ;
		else
			return false ;
	}
	void clear ()
	{
		ID = NO_ID ;
	}
	INFO getInfo ()
	{
		if (ID >= 0 && ID < vInfo.size ())
			return (vInfo[ID]) ;
		else
			return NULL ;
	}

private:
	enum {NO_ID = -1} ;
	size_t ID ;//½s¸¹
	typedef std::vector <INFO> V_INFO ;
	static V_INFO vInfo ;
} ;

template <class INFO> 
std::vector <INFO>
ObjTable<INFO>::
vInfo ;




#endif