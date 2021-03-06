#ifndef _GP_SHARE_POINTER_H_
#define _GP_SHARE_POINTER_H_

#include <map>
#include <assert.h>

#include "gp_uid.h"

namespace GP
{
    template <class OBJ>
    class SHARE_POINTER
    {
 //       typedef long ID_TYPE ;
        typedef UID ID_TYPE ;
        
    public:
        class ShareInfo
        {
        private:
            ID_TYPE id ;
            OBJ* pObj ;//實際的東西
            int refCount ;//共享的計數,紀錄有多少指標用到這個物件
            
        public:
            
            ID_TYPE getID ()
            {
                return id ;
            }
            
            OBJ* getObj ()
            {
                return pObj ;
            }
            
            bool addRef ()
            {
                if (pObj != 0)
                {
                    //有東西可以共享
                    refCount ++ ;
                    return true ;
                }else
                {
                    return false ;
                }
            }
            
            bool decRef ()
            {
                assert (refCount > 0) ;
                refCount -- ;
                if (refCount == 0)
                {
                    //完全沒人在用
                    return true ;
                }else
                    return false ;
            }
            
            void destroy ()
            {
                if (pObj != 0)
                {
                    delete pObj ;
                    pObj = 0 ;
                }
            }
            
            void init (ID_TYPE i, OBJ* po)
            {
                assert (pObj == 0) ;
                assert (refCount == 0) ;
                id = i ;
                pObj = po ;
            }
            
            void operator= (const ShareInfo& si)
            {
                if (si.pObj != NULL)
                {
                    int x = 0 ;
                    x ++ ;
                }
            }
            
            //建構
            ShareInfo ():pObj(0),refCount(0)
            {
            }

            //建構
            ShareInfo (const ShareInfo& si):pObj(0),refCount(0)
            {
                if (si.pObj != NULL)
                {
                    int x = 0 ;
                    x ++ ;
                }
            }
            
            //解構
            ~ShareInfo ()
            {
                destroy () ;
            }
        } ;
        
        typedef std::map <ID_TYPE, ShareInfo> V_SHARE_INFO ;
        static V_SHARE_INFO vShareInfo ;//所有共享的資訊
        
    private:
        ShareInfo* pShareInfo ;//共享的東西
        
    public:
        static void fnAllocate (OBJ* pNewObj, SHARE_POINTER& sp)
        {
            sp.noShare () ;//先釋放
            
//            ID_TYPE id = (ID_TYPE)pNewObj ;
            ID_TYPE uid ;
            uid.generate () ;
            
            typename V_SHARE_INFO::iterator pi = vShareInfo.find (uid) ;
            if (pi != vShareInfo.end ())
            {
                //找到了,不可以發生這種事,因為物件要求只建立一次
                assert (0) ;
            }else
            {
                //沒找到
                ShareInfo& sinfo = vShareInfo[uid] ;
                sinfo.init (uid, pNewObj) ;
                
                sp.pShareInfo = &sinfo ;
                sp.pShareInfo->addRef () ;
            }
        }
        
        bool operator == (const SHARE_POINTER& obj)const
        {
            return pShareInfo == obj.pShareInfo ;
        }

        bool operator != (const SHARE_POINTER& obj)const
        {
            return pShareInfo == obj.pShareInfo ;
        }
        
        bool isSameObj (const SHARE_POINTER& obj)const
        {
            return pShareInfo == obj.pShareInfo ;
        }
        
        OBJ* getPtr ()
        {
            if (pShareInfo != 0)
            {
                //自己有在共享
                
                OBJ* pObj = pShareInfo->getObj () ;
                if (pObj != 0)
                {
                    //有東西
                    return pObj ;
                }else
                {
                    //沒東西,不需要再共享了
                    noShare () ;
                }
            }
            
            return 0 ;
        }
        
        void noShare ()
        {
            //不要共享了
            if (pShareInfo != 0)
            {
                if (pShareInfo->decRef ())
                {
                    //完全沒人在用
                    typename V_SHARE_INFO::iterator pi = vShareInfo.find (pShareInfo->getID ()) ;
                    if (pi != vShareInfo.end ())
                    {
                        //找到
                        vShareInfo.erase (pi) ;
                    }else
                    {
                        assert (0) ;
                    }
                }
                pShareInfo = 0 ;
            }
        }
        
        //複製
        void operator= (const SHARE_POINTER& sp)
        {
            if (this == &sp)
            {
                //避開自己複製自己
                return ;
            }
            
            noShare () ;//先取消共享
            
            pShareInfo = sp.pShareInfo ;
            if (pShareInfo != 0)
            {
                //可以共享
                if (pShareInfo->addRef ())
                {
                    //共享成功
                }else
                {
                    //共享失敗,物件根本不存在
                    pShareInfo = 0 ;
                }
            }
        }
        
        
        
        //標記為物件要被殺掉的狀態
        void setDestroy ()
        {
            assert (pShareInfo != NULL) ;
            //一定要有share,才可以設定destroy,否則其他指標會不知道東西要殺掉
            if (pShareInfo != NULL)
            {
                pShareInfo->destroy () ;//刪除allocate的物件
                
                noShare () ;
            }
        }
        
        //要共享一個物件
        SHARE_POINTER ():pShareInfo(0)
        {
        }
        
        //拷貝建構
        SHARE_POINTER (const SHARE_POINTER& sp):pShareInfo(0)
        {
            operator= (sp) ;
        }
        
        ~SHARE_POINTER ()
        {
            noShare () ;
        }
    } ;
    
    template <class OBJ> typename SHARE_POINTER<OBJ>::V_SHARE_INFO SHARE_POINTER<OBJ> ::vShareInfo ;
}//namespace

#endif//header




