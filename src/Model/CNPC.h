#ifndef _CNPC_H_
#define _CNPC_H_

#include "CUnitObject.h"
#include "CNPCInfoLoader.h"
#include "obj_mTable.h"

typedef ObjTable<CNPCInfo*, CNPCInfoLoader> NPC_INFO;

class CNPC:public NPC_INFO,
           public CUnitObject
{
public:
	CNPC(std::string machineName, int kindID, long long uid, float fx, float fy);
	~CNPC();
	static void initNPC();
#ifdef _GAMEENGINE_2D_
	/** @brief Client端繪圖動作 
     * @param hdc 繪圖裝置 */
      /* virtual */ void draw(HDC hdc);//任務
#endif
private:
	bool create(unsigned int kindID);
};

#endif //#ifndef _CNPC_H_