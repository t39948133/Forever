#include "CBackPack.h"

void CBackPack::setGrid(int grid, CItemTable& itm)
{
	if((grid >= 0) && (grid < BACK_MAX))
	{
		m_itemBack[grid] = itm;
	}
}

CItemTable* CBackPack::getItem(int grid)
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

CItem* CBackPack::getCItem(int grid)
{
    CItemTable* pc = getItem(grid);					
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

void CBackPack::initBack()
{
	m_itemBack[0].create(0, 1);
	m_itemBack[1].create(1, 1);
}