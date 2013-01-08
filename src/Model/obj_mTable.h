#ifndef _OBJ_MTABLE_H_
#define _OBJ_MTABLE_H_
#include "Common.h"

template <class INFO, class CLASS_LOADER>
class ObjTable
{
public:
	static bool read (const char* name)
	{
      FILE* pFile ; 
      fopen_s (&pFile, name, "rb") ;

      if (pFile != NULL)
      {
         for(int i = 0; (size_t)i < vInfo.size (); i++)
         {
            delete vInfo[i];
            /*
            INFO pInfo = vInfo[i] ;
            delete pInfo ;*/
         }
         vInfo.clear () ;

         CLASS_LOADER loader ;

         int version = 0 ;
         fread (&version, sizeof (version), 1, pFile) ;

         int count ;
         fread (&count, sizeof (count), 1, pFile) ;

         for(int i = 0; i < count; i++)
         {
            int type;
            fread (&type, sizeof(type), 1, pFile);

            INFO pInfo = loader.create (type) ;		//INFO是指標型態 修改*pInfo
            {
               pInfo->read (pFile) ;
               vInfo.push_back(pInfo);
            }
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

   static void release()
   {
      if(0 == vInfo.size())
      {
         return;
      }
      V_INFO::iterator pi = vInfo.begin () ;
      while(vInfo.end() != pi)
      {
         if(NULL != (*pi))
         {
            delete (*pi);
            (*pi) = NULL;
         }
         pi++;
      }
      vInfo.clear();
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

	~ObjTable()
	{
	}

	int getID ()
	{
		return ID ;
	}

	bool create (size_t i)
	{
		ID = i ;
		if (ID >= 0 && (size_t) ID < vInfo.size ())
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
		if (ID >= 0 && (size_t) ID < vInfo.size ())
			return (vInfo[ID]) ;
		else
			return NULL ;
	}

private:
	enum {NO_ID = -1} ;
	int ID ;//編號
	typedef std::vector <INFO> V_INFO ;
	static V_INFO vInfo ;
} ;

template <class INFO, class CLASS_LOADER> 
std::vector <INFO>
ObjTable<INFO, CLASS_LOADER>::
vInfo ;

#endif