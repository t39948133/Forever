#ifndef _OBJ_TABLE_H_
#define _OBJ_TABLE_H_

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

			//char readType = 0;
			V_INFO::iterator pi = vInfo.begin () ;
			while (pi != vInfo.end ())
			{
				//fread (&readType, sizeof(readType), 1, pFile);
				(*pi)->read (pFile) ;
				++ pi ;
			}

			fclose (pFile) ;

			return true ;
		}else
			return false ;
	}
	/*
	static void write (const char* name)
	{
		FILE* pFile ; 
		fopen_s (&pFile, name, "wb") ;

		int version = 0 ;
		fwrite (&version, sizeof (version), 1, pFile) ;

		int count = vInfo.size () ;
		fwrite (&count, sizeof (count), 1, pFile) ;

		V_INFO::iterator pi = vInfo.begin () ;
		while (pi != vInfo.end ())
		{
			(*pi)->write (pFile) ;
			++ pi ;
		}

		fclose (pFile) ;
	}*/
	static int getInfoCount ()
	{
		return vInfo.size () ;
	}
	static INFO* getInfo (size_t id)
	{
		if (id >= 0 && id < vInfo.size ())
			return vInfo[id] ;
		else
			return NULL ;
	}
	static INFO* addInfo ()
	{
		INFO tmp ;
		vInfo.push_back (tmp) ;

		return &(vInfo.back ()) ;
	}
	bool checkID (int id)
	{
		if ((size_t)id < vInfo.size () && id >= 0)
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
	INFO* getInfo ()
	{
		if (ID >= 0 && ID < vInfo.size ())
			return &(vInfo[ID]) ;
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