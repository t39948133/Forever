#include "CBackPack.h"

void CBackPack::setGrid(int grid, CItem& itm)
{
	if((grid >= 0) && (grid < BACK_MAX))
	{
		m_itemBack[grid] = itm;
	}
}

CItem* CBackPack::getItem(int grid)
{
	if((grid >= 0) && (grid < BACK_MAX))
	{
		return &(m_itemBack[grid]);
	}
	else
	{
		return NULL;
	}
}

CItemInfo* CBackPack::getItemInfo(int grid)
{
    CItem* pc = getItem(grid);					
    if (pc != NULL)
        return pc->getInfo () ;
    return NULL ;
}

void CBackPack::addItem(int id, int& stack, int& grid)
{
	for(int i = 0; i<BACK_MAX; i++)
	{
		m_itemBack[i].addStack(id, stack);
		if(stack == 0)
		{
			grid = i;
			break;
		}
	}
}

// Add by Darren Chen on 2013/01/13 {
int CBackPack::getSize()
{
   return BACK_MAX;
}
// } Add by Darren Chen on 2013/01/13

void CBackPack::initBack()
{
   // 藥水

   // 新手裝備
	m_itemBack[3].create(0, 1);
	m_itemBack[4].create(1, 1);
   m_itemBack[5].create(2, 1);

   // 技能書

   // 勇氣系列裝備
   m_itemBack[9].create(12, 1);
   m_itemBack[10].create(13, 1);
   m_itemBack[11].create(14, 1);
   m_itemBack[12].create(15, 1);
   m_itemBack[13].create(16, 1);
   m_itemBack[14].create(29, 1);

   // 守衛萬夫長系列裝備
   m_itemBack[18].create(17, 1);
   m_itemBack[19].create(18, 1);
   m_itemBack[20].create(19, 1);
   m_itemBack[21].create(20, 1);
   m_itemBack[22].create(21, 1);
   m_itemBack[23].create(30, 1);
}