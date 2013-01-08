/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEvent.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/27 */
#ifndef _CACTIONEVENT_H_
#define _CACTIONEVENT_H_
#include "Common.h"

/** @brief �ʧ@�ƥ� */
class CActionEvent
{
   public:
      CActionEvent();

      /** @brief �������
        * @param actEvent CActionEvent���� */
      void operator=(CActionEvent &actEvent);

      /** @brief ����P�_
        * @param actEvent CActionEvent���� */
      bool operator==(CActionEvent &actEvent);

      /** @brief �M����� */
      void clear();

      ACTION_EVENT_TYPE m_event;       // �ʧ@�ƥ�

      // AET_KEY (��@����)
      int               m_iKeyID;      // ����(�ϥ�Virtual key)

      // AET_KEY_COMBIN (�h�ӫ���)
      int               m_iKeyDownID;  // ���U����(�ϥ�Virtual key)
      int               m_iKeyUpID;    // ��}����(�ϥ�Virtual key)
};

#endif  // #ifndef _CACTIONEVENT_H_