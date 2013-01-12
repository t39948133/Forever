#ifdef _GAMEENGINE_3D_
#include "CTextAreaOgre.h"

#include <OgreOverlayManager.h>
#include <OgreFontManager.h>

Ogre::UTFString ConvertToUTFString(const std::string & str) 
{ 
   DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

   wchar_t *pWbuffer = new wchar_t[dwNum + 1];
   ZeroMemory(pWbuffer, dwNum + 1);

   MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pWbuffer, dwNum);

   return Ogre::UTFString(pWbuffer);
} 

CTextAreaOgre::CTextAreaOgre()
{
   //m_pTextArea = NULL;
}

CTextAreaOgre::~CTextAreaOgre()
{
   /*if(m_pTextArea != NULL) {
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_pTextArea);
      m_pTextArea = NULL;
   }*/
}

void CTextAreaOgre::init (COverlayUI& ui, int _x, int _y, int _w, int _h)
{
	x = _x ;
	y = _y ;
	w = _w ;
	h = _h ;

	//textOverlay.Init (ui.getOverlayContainer ()) ;
	//textOverlay.SetPos ((float)x, (float)y) ;

   static int in = 0;
	in++;
	char buf[256];
	sprintf(buf, "CTextAreaOgre %d", in) ;
   m_pTextArea = static_cast<Ogre::TextAreaOverlayElement *>(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", buf));
   m_pTextArea->setMetricsMode(Ogre::GMM_PIXELS);
   m_pTextArea->setPosition((Ogre::Real)x, (Ogre::Real)y);
   m_pTextArea->setDimensions((Ogre::Real)w, (Ogre::Real)h);
   m_pTextArea->setFontName("NCTaiwanFont");
   m_pTextArea->setCharHeight(18);   

   ui.getOverlayContainer()->addChild(m_pTextArea);
}

void CTextAreaOgre::setText(std::string text, float r, float g, float b)
{
   //textOverlay.SetText(text.c_str(), r, g, b) ;
   
   m_pTextArea->setColour(Ogre::ColourValue(r, g, b));

   Ogre::UTFString utfText = ConvertToUTFString(text);

   // 計算換行 ************************** {
   Ogre::Font *pFont = (Ogre::Font*)Ogre::FontManager::getSingleton().getByName(m_pTextArea->getFontName()).getPointer();

	bool firstWord = true;
	unsigned int lastSpace = 0;
	unsigned int lineBegin = 0;
	Ogre::Real lineWidth = 0;
   Ogre::Real rightBoundary = (Ogre::Real)w;

   for(unsigned int i = 0; i < utfText.length(); i++) {
      if(utfText[i] == ' ') {
			if(m_pTextArea->getSpaceWidth() != 0)
            lineWidth += m_pTextArea->getSpaceWidth();
			else 
            lineWidth += pFont->getGlyphAspectRatio(' ') * m_pTextArea->getCharHeight();
			firstWord = false;
			lastSpace = i;
		}
	   else if(utfText[i] == '\n') {
			firstWord = true;
			lineWidth = 0;
			lineBegin = i + 1;
		}
      else {
			// use glyph information to calculate line width
			lineWidth += pFont->getGlyphAspectRatio(utfText[i]) * m_pTextArea->getCharHeight();
			if(lineWidth > rightBoundary) {
				if(firstWord) {
					utfText.insert(i, "\n");
					i = i - 1;
				}
				else {
					utfText[lastSpace] = '\n';
					i = lastSpace - 1;
				}
			}
		}
   }
   // } 計算換行 **************************

   m_pTextArea->setCaption(utfText);
}

/*Ogre::OverlayContainer* CTextAreaOgre::getImage ()
{
	return textOverlay.getImage () ;
}*/
#endif  // #ifdef _GAMEENGINE_3D_