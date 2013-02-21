#include "CNPC.h"

CNPC::CNPC(std::string machineName, int kindID, long long uid, float fx, float fy):
CUnitObject(machineName, NPC_INFO::getInfo(kindID)->getName(), uid, 50)
{
	if(create(kindID))
	{
		setPosition(fx, fy);
      setTargetPosition(fx, fy);
		BasicAttribute basAttr;
		//memset(&basAttr, 1000, sizeof(basAttr));
		basAttr.iAGI = 1000;
		basAttr.iDEX = 1000;
		basAttr.iINT = 1000;
		basAttr.iSTR = 1000;
		basAttr.iVIT = 1000;
		basAttr.iWIL = 1000;
		setBasAttr(basAttr);

		std::string actionFile = NPC_INFO::getInfo(kindID)->getActionSystemFile();
      if(m_actionSystem.read("../" + actionFile) == false)
         m_actionSystem.read(actionFile);
	}
}

void CNPC::initNPC()
{
	if(NPC_INFO::read("NPC.fla"))
	{
	}
	else
	{
		CNPCInfo* pnpc = new CNPCInfo();
		std::vector<std::string> talk;
		std::string str;
		str = "hello";
		talk.push_back(str);
		str = "我是村長";
		talk.push_back(str);
		str = "買東西嗎?";
		talk.push_back(str);
		std::vector<int> quest;
		std::vector<int> sell;
		sell.push_back(0);
		sell.push_back(1);
		sell.push_back(2);
		pnpc->initNPCInfo("村長", "ShugoFemale.mesh", "ShugoFemale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);
	}
}

CNPC::~CNPC()
{
}

bool CNPC::create(unsigned int kindID)
{
	if(false == NPC_INFO::checkID(kindID))
    {
        return false;
    }
    NPC_INFO::create(kindID);
    CNPCInfo* pInfo = getInfo();
    if(NULL != pInfo)
    {
        return true;
    }
    return false;
}

#ifdef _GAMEENGINE_2D_
void CNPC::draw(HDC hdc)
{
	CUnitObject::draw(hdc);
	//任務
	int size = 20;
   char buf[128];
   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));
}
#endif