#include "CNPCChatWnd.h"

CNPCChatWnd::CNPCChatWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++)
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) 
      m_vpBtn[i] = NULL;

   for(int i = 0; i < TEXT_COUNT; i++)
      m_vpText[i] = NULL;
#endif
}

CNPCChatWnd::~CNPCChatWnd()
{
#ifdef _GAMEENGINE_3D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
      }
   }
#elif _GAMEENGINE_2D_
   for(int i = 0; i < BUTTON_COUNT; i++) {
      if(m_vpBtn[i] != NULL) {
         delete m_vpBtn[i];
         m_vpBtn[i] = NULL;
      }
   }

   for(int i = 0; i < TEXT_COUNT; i++) {
      if(m_vpText[i] != NULL) {
         delete m_vpText[i];
         m_vpText[i] = NULL;
      }
   }
#endif
}
void CNPCChatWnd::init (int _x, int _y, CPlayer* pb, NetStream *pNetStream)
{	
	selQuestID = -1 ;//目前選的任務編號
	type = TYPE_CHAT ;
	m_pPlayer = pb ;
	m_pNetStream = pNetStream ;
	m_pNPC = NULL ;
	x = _x ;
	y = _y ;
	w = 200 ;
	h = TEXT_COUNT*CELL_SIZE ;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
    m_overlay.setBackImage("chat");
	
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextAreaOgre ;
		m_vpText[i]->init (&m_overlay, 0, i*CELL_SIZE, w, CELL_SIZE) ;
		if (i == 0)
		{	
			m_vpText[i]->setText ("NPC:對話內容", 1, 1, 1) ;
		}else if (i == 1)
		{
			m_vpText[i]->setText ("", 1, 1, 1) ;
		}else
		{
			m_vpText[i]->setText ("", 1, 1, 1) ;
		}
		addChild (m_vpText[i]) ;
	}
#elif _GAMEENGINE_2D_

	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		m_vpBtn[i] = new CTextButton ;
		m_vpBtn[i]->init (0, i*CELL_SIZE, w, CELL_SIZE, i) ;
		addChild (m_vpBtn[i]) ;
	}

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextArea ;
		m_vpText[i]->init (0, i*CELL_SIZE, w, CELL_SIZE) ;
		if (i == 0)
		{	
			m_vpText[i]->setText ("NPC:對話內容", 1, 1, 1) ;
		}else if (i == 1)
		{
			m_vpText[i]->setText ("", 1, 1, 1) ;
		}else
		{
			m_vpText[i]->setText ("", 1, 1, 1) ;
		}
		addChild (m_vpText[i]) ;
	}
#endif
}

void CNPCChatWnd::setNPC (CNPC* pnp)
{/*
	pNPC = pnp ;
	selQuestID = -1 ;//目前選的任務編號

	if (pNPC == NULL)
		return ;

	Quest* pQuest = pPlayer->questMap.onClickNPC (pNPC->getID ()) ;
	if (pQuest != NULL)
	{
		//可以結束任務
		type = TYPE_REWARD ;

		for (int i = 0; i<QUEST_H_COUNT+CHAT_H_COUNT+1; i++)
			vpBtn[i]->bVisible = false ;

		QuestInfo* pQuestInfo = pQuest->getInfo () ;

		for (int i = 0; i<2; i++)
		{
			ItemInfo* pItemInfo = Item::getInfo (pQuestInfo->vRewardItem[i]) ;
			if (pItemInfo != NULL)
			{
				vpBtn[i]->str = pItemInfo->name ;
				vpBtn[i]->bVisible = true ;
			}
		}
	}else
	{
		type = TYPE_CHAT ;

		NPCInfo* pinfo = pNPC->getInfo () ;

		for (int i = 0; i<QUEST_H_COUNT+CHAT_H_COUNT+1; i++)
			vpBtn[i]->bVisible = false ;

		int offset = 0 ;
		for (int i = 0; i<pinfo->vQuestID.size (); i++)
		{
			int questID = pinfo->vQuestID[i] ;
			if (pPlayer->questMap.canAddQuest (questID))
			{
				//可以加任務
				QuestInfo* pQuestInfo = QUEST_INFO::getInfo (questID) ;
				if (pQuestInfo != NULL)
				{
					vpBtn[offset]->str = pQuestInfo->name ;
					vpBtn[offset]->bVisible = true ;
					offset ++ ;
				}
			}
		}

		for (int i = 0; i<3; i++)
		{
			EasyStr <64> text = pinfo->vChatInfo[i] ;

			if (text.length () > 0)
			{
				vpBtn[QUEST_H_COUNT+i]->str = text ;
				vpBtn[QUEST_H_COUNT+i]->bVisible = true ;
			}
		}

	}*/
}

bool CNPCChatWnd::canDrag (int tx, int ty)
{
	return false ;
}

void CNPCChatWnd::onLCommand(int btnID)
{/*
	if (pNPC == NULL)
		return ;

	if (type == TYPE_REWARD)
	{
		//
		Quest* pQuest = pPlayer->questMap.onClickNPC (pNPC->getID ()) ;
		if (pQuest != NULL)
		{
			PacketQuestReward pkg ;
			pkg.npcUID = pNPC->UID ;
			pkg.rewardPos = btnID ;


			pStream->send (&pkg, sizeof (pkg)) ;
			bVisible = false ;
		}
	}else
	{
		if (btnID == QUEST_H_COUNT+CHAT_H_COUNT)
		{
			//點了接任務
			PacketAddQuest pkg ;
			pkg.questID = selQuestID ;
			pStream->send (&pkg, sizeof (pkg)) ;
			bVisible = false ;
			return ;
		}

		NPCInfo* pinfo = pNPC->getInfo () ;

		int offset = 0 ;
		for (int i = 0; i<pinfo->vQuestID.size (); i++)
		{
			int questID = pinfo->vQuestID[i] ;
			if (pPlayer->questMap.canAddQuest (questID))
			{
				//可以加任務
				QuestInfo* pQuestInfo = QUEST_INFO::getInfo (questID) ;
				if (pQuestInfo != NULL)
				{
					if (btnID == offset)
					{
						//點到某個任務button
						selQuestID = questID ;

						//修改對話內容,改成任務資訊
						vpBtn[QUEST_H_COUNT]->str = 
									pQuestInfo->info ;
						vpBtn[QUEST_H_COUNT]->bVisible = true ;
						vpBtn[QUEST_H_COUNT+1]->bVisible = false ;
						vpBtn[QUEST_H_COUNT+2]->bVisible = false ;

						//把接任務的按鈕顯示出來
						vpBtn[QUEST_H_COUNT+CHAT_H_COUNT]->bVisible = true ;
					}

					offset ++ ;
				}
			}
		}
	}
*/
}
void CNPCChatWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}


#ifdef _GAMEENGINE_3D_
void CNPCChatWnd::onDrag()
{
   m_overlay.setPosition(x, y);
}

void CNPCChatWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

/*
void CNPCChatWnd::draw (HDC hdc, int ox, int oy)
{
	Window::draw (hdc, ox, oy) ;

	if (pNPC == NULL)
		return ;

	NPCInfo* pinfo = pNPC->getInfo () ;

	
	int offset = 0 ;
	for (int i = 0; i<pinfo->vQuestID.size (); i++)
	{
		int questID = pinfo->vQuestID[i] ;
		if (pPlayer->questMap.canAddQuest (questID))
		{
			//可以加任務
			QuestInfo* pQuestInfo = QUEST_INFO::getInfo (questID) ;
			if (pQuestInfo != NULL)
			{
				TextOut (hdc, x+2, y+2+(offset+1)*CELL_SIZE,
					pQuestInfo->name, pQuestInfo->name.length ()) ;
				offset ++ ;
			}
		}
	}


	for (int i = 0; i<3; i++)
	{
		EasyStr <64> text = pinfo->vChatInfo[i] ;

		TextOut (hdc, x+2, y+2+(CELL_SIZE+i+3)*3,
			text, text.length ()) ;
	}
	
}
*/