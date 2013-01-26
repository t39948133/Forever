#include "game_client.h"



void GameClient::initUI ()
	{
		Player* pPlr = scene.getMainPlayer () ;

#ifdef _PROJECT_OGRE_3D_
		windowMan.init () ;
				
		pmw = new MapWnd ;
		pmw->init (250, 134) ;
		windowMan.addWnd (pmw) ;

		ppinw = new PlayerInfoWnd ;
		ppinw->init (10, 80, pPlr) ;
		windowMan.addWnd (ppinw) ;

		phw = new HotKeyWnd ;
		phw->init (472, 893, pPlr) ;
		windowMan.addWnd (phw) ;

		pbw = new BackpackWnd ;
		pbw->init (10, 480, pPlr, phw, ppinw) ;
		windowMan.addWnd (pbw) ;

		psw = new ShopWnd ;
		psw->init (580, 55, pPlr) ;
		windowMan.addWnd (psw) ;

		pTargetInfoWnd = new TargetInfoWnd ;
		pTargetInfoWnd->init (&scene, 362, 5) ;
		windowMan.addWnd (pTargetInfoWnd) ;

		pSkillWnd = new SkillWnd ;
		pSkillWnd->init (580, 340, &stream, pPlr, pTargetInfoWnd, &scene, phw) ;
		windowMan.addWnd (pSkillWnd) ;		

		pNPCWnd = new NPCChatWnd ;
		pNPCWnd->init (5, 500, pPlr, &stream) ;
		windowMan.addWnd (pNPCWnd) ;

		pqw = new QuestWnd ;
		pqw->init (1050, 5, pPlr) ;
		windowMan.addWnd (pqw) ;		

		ppsw = new PlayerStatusWnd ;
		ppsw->init (263, 873, pPlr) ;
		windowMan.addWnd (ppsw) ;

/*		ppnw = new PlayerNameWnd ;
		ppnw->init ((int)(pPlr->x)-50, (int)(pPlr->y)-50, &(pPlr->data)) ;
		windowMan.addWnd (ppnw) ;
*/
		pmmw = new MiniMapWnd ;
		pmmw->init (1050, 660, pPlr, &scene, &cameraDir) ;
		windowMan.addWnd (pmmw) ;

		ppimw = new PlayerImageWnd ;
		ppimw->init (155, 828, &(pPlr->data)) ;
		windowMan.addWnd (ppimw) ;

		ptw = new ToolBarWnd ;
		ptw->init (pbw, ppinw, pSkillWnd, pmw, 825, 860) ;
		windowMan.addWnd (ptw) ;

#else _PROJECT_GDI_	

		pItemInfoWnd = new ItemInfoWnd ;
		pItemInfoWnd->init (0, 0) ;
		windowMan.addWnd (pItemInfoWnd) ;
				
		pSkillInfoWnd = new SkillInfoWnd ;
		pSkillInfoWnd->init (0, 0) ;
		windowMan.addWnd (pSkillInfoWnd) ;

		pmw = new MapWnd ;
		pmw->init (250, 134) ;
		windowMan.addWnd (pmw) ;

		ppinw = new PlayerInfoWnd ;
		ppinw->init (5, 5, pPlr) ;
		windowMan.addWnd (ppinw) ;

		phw = new HotKeyWnd ;
		phw->init (333, 720, pPlr) ;
		windowMan.addWnd (phw) ;

		pbw = new BackpackWnd ;
		pbw->init (5, 405, pPlr, phw, ppinw, pItemInfoWnd) ;
		windowMan.addWnd (pbw) ;

		psw = new ShopWnd ;
		psw->init (539, 5, pPlr, pItemInfoWnd) ;
		windowMan.addWnd (psw) ;

		pTargetInfoWnd = new TargetInfoWnd ;
		pTargetInfoWnd->init (&scene, 362, 5) ;
		windowMan.addWnd (pTargetInfoWnd) ;

		pSkillWnd = new SkillWnd ;
		pSkillWnd->init (400, 200, &stream, pPlr, pTargetInfoWnd, &scene, phw, pSkillInfoWnd) ;
		windowMan.addWnd (pSkillWnd) ;

		pNPCWnd = new NPCChatWnd ;
		pNPCWnd->init (5, 500, pPlr, &stream) ;
		windowMan.addWnd (pNPCWnd) ;

		pqw = new QuestWnd ;
		pqw->init (819, 5, pPlr) ;
		windowMan.addWnd (pqw) ;		

		ppsw = new PlayerStatusWnd ;
		ppsw->init (100, 682, pPlr) ;
		windowMan.addWnd (ppsw) ;

/*		ppnw = new PlayerNameWnd ;
		ppnw->init ((int)(pPlr->x)-50, (int)(pPlr->y)-50, &(pPlr->data)) ;
		windowMan.addWnd (ppnw) ;
*/
		pmmw = new MiniMapWnd ;
		pmmw->init (820, 495, pPlr, &scene, &cameraDir) ;
		windowMan.addWnd (pmmw) ;

		ppimw = new PlayerImageWnd ;
		ppimw->init (27, 660, &(pPlr->data)) ;
		windowMan.addWnd (ppimw) ;

		ptw = new ToolBarWnd ;
		ptw->init (pbw, ppinw, pSkillWnd, pmw, 735, 720) ;
		windowMan.addWnd (ptw) ;

#endif
	}

	void GameClient::init (const char* name, float x, float y)
	{
		scene.loadScene (0) ;

		gameState = STATE_LOGIN ;

		bSendLogin = false ;

		targetX = x ;
		targetY = y ;

		Player* pPlayer = scene.addPlayer (-1) ;
		pPlayer->init (x, y, 20, 40, Unit::GROUP_PLAYER) ;
		pPlayer->name = name ;

		NetAddress addr ;
		addr.setIPPort ("127.0.0.1:2200") ;
		stream.startConnect (addr) ;

		initUI () ;
	}

	void GameClient::onRecvPlayerInit (PacketPlayerInit& pkg)
	{
		Player* pPlayer = scene.getMainPlayer () ;

		pkg.unpack (*pPlayer) ;
	}

	Player* GameClient::onRecvPlayerData (PacketPlayerData& pkg)
	{
		Player* pPlayer = scene.getPlayer (pkg.uid) ;
		if (pPlayer == NULL)
		{
			pPlayer = scene.addPlayer (pkg.uid) ;
		}

		pPlayer->init (pkg.x, pkg.y, 20,
			40, Unit::GROUP_PLAYER) ;

		pkg.unpack (*pPlayer) ;

		return pPlayer ;
	}

	Monster* GameClient::onRecvMonsterData (PacketMonsterData& pkg)
	{
		Monster* pm = scene.getMonster (pkg.uid) ;
		if (pm == NULL)
		{
			//沒有找到
			pm = scene.addMonster (pkg.uid, pkg.id, pkg.x, pkg.y) ;
		}

		pmmw->onAddUnit (pm) ;
		pmmw->update () ;
		pkg.unpack (*pm) ;
		return pm ;
	}

	NPC* GameClient::onRecvNPCData (PacketNPCData& pkg)
	{
		NPC* pm = scene.getNPC (pkg.uid) ;
		if (pm == NULL)
		{
			//沒有找到
			pm = scene.addNPC (pkg.uid, pkg.id, pkg.x, pkg.y) ;
		}

		pkg.unpack (*pm) ;
		return pm ;
	}

	void GameClient::onRecvHP (PacketHP& pkg)
	{
		Unit* pm = scene.getUnit (pkg.uid) ;
		if (pm != NULL)
		{
			//沒有找到
			pm->data.hp = pkg.hp ;
		}
	}

	void GameClient::onRecvAddQuest (PacketAddQuest& pkg)
	{
		Player* plr = scene.getMainPlayer () ;
		if (plr != NULL)
			plr->questMap.addQuest (pkg.questID) ;
	}

	void GameClient::onRecvDelQuest (PacketDelQuest& pkg)
	{
		Player* plr = scene.getMainPlayer () ;
		if (plr != NULL)
			plr->questMap.delQuestID (pkg.questID) ;
	}

	void GameClient::onRecvFinishQuest (PacketFinishQuest& pkg)
	{
		Player* plr = scene.getMainPlayer () ;
		if (plr != NULL)
			plr->questMap.finishQuest (pkg.questID) ;
	}

	void GameClient::onRecvTargetPos (PacketTargetPos& pkg)
	{
		Unit* pu = scene.getUnit (pkg.uid) ;
		if (pu != NULL)
		{
			pu->setMoveTarget (pkg.x, pkg.y, pkg.bFaceTarget) ;
//			pu->targetX = pkg.x ;
//			pu->targetY = pkg.y ;
		}
	}

	void GameClient::onRecvDoAction (PacketDoAction& pkg)
	{
		Unit* pu = scene.getUnit (pkg.uid) ;
		if (pu != NULL)
			pkg.unpack (*pu) ;
	}

	void GameClient::onRecvSetBackpack (PacketSetBackpack& pkg)
	{
		Player* pPlr = scene.getMainPlayer () ;
		if (pPlr != NULL)
			pkg.unpack (pPlr->backpack) ;
	}

	void GameClient::onRecvUseSkill (PacketUseSkill& pkg)
	{
		Player* pPlr = scene.getMainPlayer () ;
		if (pPlr != NULL)
		{
			Unit* pTarget = scene.getUnit (pkg.targetUID) ;

			pPlr->startCast (pkg.skillOffset, pTarget, scene) ;
		}
//		Unit* pu = scene.getUnit (pkg.uid) ;
//		if (pu != NULL)
//			pkg.unpack (*pu) ;
	}

	void GameClient::onRecvChangeGameServer (PacketChangeGameServer& pkg)
	{
		bSendLogin = false ;
		stream.stopConnection () ;

		scene.delNotMainPlayer () ;
		Player* plr = scene.getMainPlayer () ;

		scene.loadScene (pkg.sceneID) ;

		Portal* ppT = scene.getPortal (pkg.portalID) ;
		if (ppT != NULL)
			ppT->getNearPos (plr->x, plr->y) ;

		pTargetInfoWnd->setTarget (NULL) ;

		gameState = STATE_CHANGE_LOGIN ;

		targetX = plr->x ;
		targetY = plr->y ;

		stream.startConnect (pkg.addr) ;
	}

	void GameClient::onRecvDelMonster (PacketDelMonster& pkg)
	{
		Monster* pm = scene.getMonster (pkg.uid) ;
		pmmw->onDelUnit (pm) ;
		scene.delMonster (pkg.uid) ;
	}

	void GameClient::onRecvFormTeamGC (PacketFormTeamGC& pkg)
	{
		PacketJoinTeam pkg2 ;
		pkg2.leaderUID = pkg.leaderUID ;

		stream.send (&pkg2, sizeof (pkg2)) ;
	}

	void GameClient::onRecvTeamInfo (PacketTeamInfo& pkg)
	{
		teamInfo = pkg.teamInfo ;
	}

	void GameClient::onClikcNPC (NPC& npc)
	{
							//
		//顯示對話視窗
		pTargetInfoWnd->setTarget (npc.UID) ;
		pNPCWnd->bVisible = true ;
		pNPCWnd->setNPC (&npc) ;

		/*
		//通知serve點了npc
		PacketClickNPC pkg ;
		pkg.uid = pNPC->UID ;

		stream.send (&pkg, sizeof (pkg)) ;
		*/
	}

	void GameClient::onClickPlayer (Player& player)
	{
		//有點到玩家
		if (&player != scene.getMainPlayer ())
		{
			//點到其他玩家
			PacketFormTeam pkg ;
			pkg.targetUID = player.UID ;

			stream.send (&pkg, sizeof (pkg)) ;
		}
	}

	void GameClient::doUI (HWND hWnd)
	{
		bool bPressWindow = windowMan.work (hWnd, keyMan) ;

		Player* plr = scene.getMainPlayer () ;
		if (keyMan.isPress (KEY_LBUTTON))
		{
			int mx, my ;
			getMousePos (hWnd, mx, my) ;

			if (bPressWindow)
			{
				//點到介面				
			}else
			{
				if (pSkillWnd->bPickGround)
				{
					//要選對地面施展的技能
					if (plr != NULL)
					{
						plr->useSkill (pSkillWnd->groudSkillOffset,
							float(mx), float(my), scene) ;
						pSkillWnd->bPickGround = false ;
					}
				}else
				{
					Monster* pm = scene.getMonster (float(mx), float(my)) ;
					if (pm != NULL)
					{
						//點到怪
						pTargetInfoWnd->setTarget (pm->UID) ;
					}else
					{
						Player* pTargetPlayer = scene.getPlayer (float(mx), float(my)) ;
						if (pTargetPlayer != NULL)
						{
							onClickPlayer (*pTargetPlayer) ;
						}

						NPC* pNPC = scene.getNPC (float(mx), float(my)) ;
						if (pNPC != NULL)
						{
							onClikcNPC (*pNPC) ;
						}else
						{
							//點到地板
							pTargetInfoWnd->setTarget (NULL) ;
							//滑鼠點了地板,設定主角的移動目標
							Player* plr = scene.getMainPlayer () ;
							if (plr != NULL)
							{
								plr->setMoveTarget (float(mx), float(my), true) ;

								PacketTargetPos pos ;
								pos.pack (plr->UID, float(mx), float(my), true) ;
								stream.send (&pos, sizeof (pos)) ;
							}
						}
					}
				}
			}
		}

	}

	void GameClient::work_login (HWND hWnd, bool bActive)
	{
		stream.procPackage () ;
		if (stream.isConnected ())
		{
			if (bSendLogin == false)
			{
				PacketFirstLogin pkg ;
				stream.send (&pkg, sizeof (pkg)) ;
				bSendLogin = true ;
			}

			NetBuffer buf ;
			if (stream.getFullPackage (buf))
			{
				BasePacket* pPacket = (BasePacket*)buf.getBuffer () ;
				if (pPacket->id == PACKET_PLAYER_INIT)
				{
					gameState = STATE_PLAY ;
					onRecvPlayerInit (*((PacketPlayerInit*)pPacket)) ;
				}
			}
		}
	}

	void GameClient::work_change_login (HWND hWnd, bool bActive)
	{
		stream.procPackage () ;
		if (stream.isConnected ())
		{
			if (bSendLogin == false)
			{
				PacketChangeLogin pkg ;
				pkg.uid = scene.getMainPlayer ()->UID ;
				stream.send (&pkg, sizeof (pkg)) ;
				bSendLogin = true ;

				gameState = STATE_PLAY ;
			}

			NetBuffer buf ;
			if (stream.getFullPackage (buf))
			{
				BasePacket* pPacket = (BasePacket*)buf.getBuffer () ;
				if (pPacket->id == PACKET_PLAYER_INIT)
				{
					gameState = STATE_PLAY ;
					onRecvPlayerInit (*((PacketPlayerInit*)pPacket)) ;
				}
			}
		}
	}

	void GameClient::work_play (HWND hWnd, bool bActive)
	{
		doUI (hWnd) ;

		Player* pPlayer = scene.getMainPlayer () ;
		if (pPlayer == NULL)
			return ;

		Player& player = *pPlayer ;

		
/*			
		if (keyMan.isDown (KEY_DOWN))
		{
			pPlayer->data.addHP (-1) ;
			ppsw->upDate () ;
		}
*/
		if (keyMan.isDown (KEY_Q))
		{
			pPlayer->dir += 3.141592f/3.0f*fps.getTimePass () ;
			//送角色方向給server
		}
		if (keyMan.isDown (KEY_E))
		{
			pPlayer->dir -= 3.141592f/3.0f*fps.getTimePass () ;
		}

//		float moveX = 0 , moveY = 0 ;
		bool bKeyMove = false ;
		float moveDir = pPlayer->dir ;
		if (keyMan.isDown (KEY_W))
			bKeyMove = true ;
		if (keyMan.isDown (KEY_S))
		{
			moveDir += 3.141592f ;
			bKeyMove = true ;
		}
		if (keyMan.isDown (KEY_A))
		{
			moveDir += 3.141592f/2.0f ;
			bKeyMove = true ;
		}
		if (keyMan.isDown (KEY_D))
		{
			moveDir += 3.141592f*1.5f ;
			bKeyMove = true ;
		}


		if (bKeyMove)
		{
			float moveX = pPlayer->x+100*cos (moveDir) ;
			float moveY = pPlayer->y-100*sin (moveDir) ;
			pPlayer->setMoveTarget (moveX, moveY, false) ;

			PacketTargetPos pos ;
			pos.pack (pPlayer->UID, moveX, moveY, false) ;
			stream.send (&pos, sizeof (pos)) ;
		}else
		{
			pPlayer->stopMove() ;
			PacketTargetPos pos ;
			pos.pack (pPlayer->UID, pPlayer->x, pPlayer->y, false) ;
			stream.send (&pos, sizeof (pos)) ;
		}

		//
		scene.work (fps.getTimePass (), false) ;

		if (bActive)
			keyMan.work () ;


		/*
		if (keyMan.isDown (KEY_RIGHT))
			player.x ++ ;
		if (keyMan.isDown (KEY_DOWN))
			player.data.addHP (-1) ;
		*/

		stream.procPackage () ;
		if (stream.isConnected ())
		{
			NetBuffer buf ;
			while (stream.getFullPackage (buf))
			{
				BasePacket* pPacket = (BasePacket*)buf.getBuffer () ;
				if (pPacket->id == PACKET_TARGET_POS)
				{
					PacketTargetPos* pPos = (PacketTargetPos*)buf.getBuffer () ;
					onRecvTargetPos (*pPos) ;
				}else if (pPacket->id == PACKET_PLAYER_DATA)
				{
					PacketPlayerData* pPos = (PacketPlayerData*)buf.getBuffer () ;
					onRecvPlayerData (*pPos) ;
				}else if (pPacket->id == PACKET_MONSTER_DATA)
				{
					PacketMonsterData* pPos = (PacketMonsterData*)buf.getBuffer () ;
					onRecvMonsterData (*pPos) ;
				}else if (pPacket->id == PACKET_NPC_DATA)
				{
					PacketNPCData* pPos = (PacketNPCData*)buf.getBuffer () ;
					onRecvNPCData (*pPos) ;
				}else if (pPacket->id == PACKET_HP)
				{
					PacketHP* pHP = (PacketHP*)buf.getBuffer () ;
					onRecvHP (*pHP) ;
				}else if (pPacket->id == PACKET_ADD_QUEST)
				{
					PacketAddQuest* pHP = (PacketAddQuest*)buf.getBuffer () ;
					onRecvAddQuest (*pHP) ;
				}else if (pPacket->id == PACKET_DEL_QUEST)
				{
					PacketDelQuest* pHP = (PacketDelQuest*)buf.getBuffer () ;
					onRecvDelQuest (*pHP) ;
				}else if (pPacket->id == PACKET_FINISH_QUEST)
				{
					PacketFinishQuest* pHP = (PacketFinishQuest*)buf.getBuffer () ;
					onRecvFinishQuest (*pHP) ;
				}else if (pPacket->id == PACKET_DO_ACTION)
				{
					PacketDoAction* pHP = (PacketDoAction*)buf.getBuffer () ;
					onRecvDoAction (*pHP) ;
				}else if (pPacket->id == PACKET_SET_BACKPACK)
				{
					PacketSetBackpack* pHP = (PacketSetBackpack*)buf.getBuffer () ;
					onRecvSetBackpack (*pHP) ;
				}else if (pPacket->id == PACKET_USE_SKILL)
				{
					PacketUseSkill* pHP = (PacketUseSkill*)buf.getBuffer () ;
					onRecvUseSkill (*pHP) ;
				}else if (pPacket->id == PACKET_CHANGE_GAME_SERVER)
				{
					PacketChangeGameServer* pHP = (PacketChangeGameServer*)buf.getBuffer () ;
					onRecvChangeGameServer (*pHP) ;
				}else if (pPacket->id == PACKET_DEL_MONSTER)
				{
					PacketDelMonster* pHP = (PacketDelMonster*)buf.getBuffer () ;
					onRecvDelMonster (*pHP) ;
				}else if (pPacket->id == PACKET_FORM_TEAM_GC)
				{
					PacketFormTeamGC* pHP = (PacketFormTeamGC*)buf.getBuffer () ;
					onRecvFormTeamGC (*pHP) ;
				}else if (pPacket->id == PACKET_TEAM_INFO)
				{
					PacketTeamInfo* pHP = (PacketTeamInfo*)buf.getBuffer () ;
					onRecvTeamInfo (*pHP) ;
				}
			}
		}
	//	pbw->upDate (pPlayer) ;
	//	pmmw->update () ;
	}

	void GameClient::work (HWND hWnd, bool bActive)
	{
		fps.work () ;

		if (gameState == STATE_LOGIN)
			work_login (hWnd, bActive) ;
		else if (gameState == STATE_CHANGE_LOGIN)
			work_change_login (hWnd, bActive) ;
		else if (gameState == STATE_PLAY)
			work_play (hWnd, bActive) ;

	}

	void GameClient::draw (HDC hdc)
	{
		Player* pl = scene.getMainPlayer () ;

		if (pl != NULL)
			scene.draw (hdc, &(pl->questMap)) ;
		else
			scene.draw (hdc, NULL) ;

		windowMan.draw (hdc) ;
	}
