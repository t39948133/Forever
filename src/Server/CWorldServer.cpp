/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWorldServer.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CWorldServer.h"
#include "AttributeSet.h"
#include "CPacketPlayerDataWG.h"

CWorldServer::CWorldServer(std::string machineName)
{
   m_machineName = machineName;
   m_pNetStreamList = new std::list<GP::NetStream *>();
   m_pPlayerList = new std::list<CPlayerServerID *>();
}

CWorldServer::~CWorldServer()
{
   std::list<GP::NetStream *>::iterator itNet = m_pNetStreamList->begin();
   while(itNet != m_pNetStreamList->end()) {
      (*itNet)->stopConnection();
      delete (*itNet);
      itNet++;
   }
   m_pNetStreamList->clear();
   delete m_pNetStreamList;
   m_pNetStreamList = NULL;

   std::list<CPlayerServerID *>::iterator itPlayer = m_pPlayerList->begin();
   while(itPlayer != m_pPlayerList->end()) {
      delete (*itPlayer);
      itPlayer++;
   }
   m_pPlayerList->clear();
   delete m_pPlayerList;
   m_pPlayerList = NULL;
}

void CWorldServer::init(int port)
{
   m_nameVector.push_back("天真可愛小饅頭");
   m_nameVector.push_back("女子女子口乞");
   m_nameVector.push_back("o黑雪姬o");
   m_nameVector.push_back("女王");
   m_nameVector.push_back("神取浩斯");

   m_curUID = 0;
   m_listener.startListen(port);
}

void CWorldServer::work(HWND hWnd, float timePass)
{
   if(m_listener.isAccepted()) {
      GP::NetStream *pNetStream = new GP::NetStream();
      m_pNetStreamList->push_back(pNetStream);

      m_listener.transferAcceptStream(*pNetStream);
   }

   std::list<GP::NetStream *>::iterator it = m_pNetStreamList->begin();
   while(it != m_pNetStreamList->end()) {
      procGameServer((*it));
      it++;
   }
}

CPlayerServerID* CWorldServer::addPlayerServerID(GP::NetStream *pNetStream)
{
   std::string strName;
   if(m_curUID < 5)
      strName = m_nameVector.at((int)m_curUID);

   //守護職業的屬性
   BasicAttribute knightAttr;
   memset(&knightAttr, 0, sizeof(knightAttr));
   knightAttr.iSTR = 115;
   knightAttr.iVIT = 110;
   knightAttr.iDEX = 100;
   knightAttr.iAGI = 100;
   knightAttr.iINT = 90;
   knightAttr.iWIL = 105;

   CPlayerServerID *pNewPlayer = new CPlayerServerID(m_machineName, strName, m_curUID++, 1);
   pNewPlayer->setBasAttr(knightAttr);                   //設定角色為守護星
   pNewPlayer->setPosition(450.0f, 450.0f);              //設定角色位置
   pNewPlayer->setTargetPosition(450.0f, 450.0f);        //設定角色目標位置

   int stack = 10;
   int gridHP = -1;
   pNewPlayer->getBackpack()->addItem(37, stack, gridHP);//設定角色背包內容物: "生命藥水" X 10

   stack = 10;
   int gridMP = -1;
   pNewPlayer->getBackpack()->addItem(38, stack, gridMP);//設定角色背包內容物: "精神藥水" X 10

   stack = 1;
   int grid;
   pNewPlayer->getBackpack()->addItem(0, stack, grid);   //設定角色背包內容物: "訓練用長劍" X 1

   pNewPlayer->wearToEquipSlot(CHEST, 1);                //設定角色穿 "訓練用金屬胸甲"
   pNewPlayer->wearToEquipSlot(LEGS, 2);                 //設定角色穿 "訓練用金屬腿甲"

   pNewPlayer->addSkill(0);                              //設定角色有 "普通攻擊" 技能
   pNewPlayer->addSkill(1);                              //設定角色有 "猛烈一擊" 技能

   HotKeyItem newHotKeyItem;
   newHotKeyItem.iField = 0;
   newHotKeyItem.pSkill = pNewPlayer->getSkill(1);
   newHotKeyItem.pItem = NULL;
   newHotKeyItem.iBackpackGrid = -1;
   pNewPlayer->addHotKeyItem(newHotKeyItem);             //設定角色 "1快捷鍵" 是 "猛烈一擊" 技能

   newHotKeyItem.iField = 8;
   newHotKeyItem.pSkill = NULL;
   newHotKeyItem.pItem = pNewPlayer->getBackpack()->getItem(gridHP);
   newHotKeyItem.iBackpackGrid = gridHP;
   pNewPlayer->addHotKeyItem(newHotKeyItem);             //設定角色 "9快捷鍵" 是 "生命藥水" 道具

   newHotKeyItem.iField = 9;
   newHotKeyItem.pSkill = NULL;
   newHotKeyItem.pItem = pNewPlayer->getBackpack()->getItem(gridMP);
   newHotKeyItem.iBackpackGrid = gridMP;
   pNewPlayer->addHotKeyItem(newHotKeyItem);             //設定角色 "0快捷鍵" 是 "精神藥水" 道具

   pNewPlayer->updateEquipAttr();                        //更新角色因為裝備關係的相關屬性數值
   pNewPlayer->m_pNetStream = pNetStream;

   m_pPlayerList->push_back(pNewPlayer);

   return pNewPlayer;
}

void CWorldServer::procGameServer(GP::NetStream *pNetStream)
{
   pNetStream->procPackage();
   GP::NetBuffer netBuff;
   while(pNetStream->getFullPackage(netBuff)) {
      CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
      if(pPacket->m_id == PACKET_PASSWORD_GW)
         onRecvPasswordGW(pNetStream, (CPacketPasswordGW *)pPacket);
   }
}

void CWorldServer::onRecvPasswordGW(GP::NetStream *pNetStream, CPacketPasswordGW *pPacket)
{
   CPlayerServerID *pNewPlayer = addPlayerServerID(pNetStream);

   CPacketPlayerDataWG packetPlayerDataWG;
   packetPlayerDataWG.pack(pPacket->m_netID, pNewPlayer);
   pNetStream->send(&packetPlayerDataWG, sizeof(packetPlayerDataWG));
}