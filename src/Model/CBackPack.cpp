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
   m_itemBack[0].create(3, 10);
   m_itemBack[1].create(4, 10);

   // 新手裝備
	m_itemBack[3].create(0, 1);
	m_itemBack[4].create(1, 1);
   m_itemBack[5].create(2, 1);

   // 技能書
   m_itemBack[7].create(5, 1);
   m_itemBack[8].create(6, 1);
}