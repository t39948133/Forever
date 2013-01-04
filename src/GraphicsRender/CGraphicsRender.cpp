/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGraphicsRender.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/03 */
#include "CGraphicsRender.h"

CGraphicsRender::~CGraphicsRender()
{
}

std::string CGraphicsRender::getRenderName()
{
   return m_strRenderName;
}

void CGraphicsRender::setRenderName(std::string renderName)
{
   m_strRenderName = renderName;
}