/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CRenderLoader.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/03 */
#ifndef _CRENDERLOADER_H_
#define _CRENDERLOADER_H_
#include "CGraphicsRender.h"

/** @brief 用來可以載入不同的繪圖引擎(CGraphicsRender),
  *        而該繪圖引擎整個系統中也是唯一物件,
  *        重複取得都會是一樣的繪圖引擎,
  *        不會浪費記憶體空間. */
class CRenderLoader
{
   public:
      /** @brief  取得CGraphicsRender單一物件
        * @return CRenderLoader物件 */
      static CRenderLoader* getInstance();

      /** @brief 釋放CRenderLoader物件的記憶體空間 */
      static void releaseInstance();

      /** @brief  取得繪圖引擎
        *         第一次正確取得繪圖引擎後, 
        *         若第二次要取得其他繪圖引擎則是不允許中途改變, 依然回傳第一次的繪圖引擎
        * @param  renderName 繪圖引擎名稱
        * @return 繪圖引擎物件 */
      CGraphicsRender* getGraphicsRender(const std::string &renderName);

   private:
      CRenderLoader();
      ~CRenderLoader();

      /** @brief 註冊有那種繪圖引擎
        * @param render 繪圖引擎物件 */
      void registerGraphicsRender(CGraphicsRender *pRender);

      static CRenderLoader *m_pInstance;  // CRenderLoader實體物件
      CGraphicsRender *m_pRenderCore;     // 繪圖引擎
      std::map<std::string, CGraphicsRender*> *m_pEngineTable; // 繪圖引擎列表
};
#endif // #ifndef _CRENDERLOADER_H_