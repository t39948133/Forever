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
	m_itemBack[1].create(0, 1);
	m_itemBack[2].create(1, 1);
   m_itemBack[3].create(2, 10);
   m_itemBack[5].create(3, 1);
   m_itemBack[20].create(4, 1);
}