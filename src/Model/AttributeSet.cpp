#include "AttributeSet.h"

void AttributeClear (AdvancedAttribute& attr)
{
	attr.iHP = 0;
	attr.iMP = 0;
	attr.iHPMax = 0;
	attr.iMPMax = 0;
	attr.iATK = 0;
	attr.iDEF = 0;
	attr.iHIT = 0;
	attr.iCRI = 0;
	attr.iMATK = 0;
	attr.iMDEF = 0;
	attr.iMHIT = 0;
	attr.iMCRI = 0;
	attr.iSDEF = 0;
	attr.iWDEF = 0;
	attr.iFlee = 0;
	attr.fMove = 0.0f;
	attr.fATKSpeed = 0.0f;
	attr.fCasting = 0.0f;
}

void AttributeClear (ObscureAttribute& obs)
{
	obs.iHPR = 0;
	obs.iMPR = 0;
}

void AttributeClear (ComplexAttribute& com)
{
	AttributeClear(com.AdvAttr);
	AttributeClear(com.ObsAttr);
}

void AttributeClear (BasicAttribute& bas)
{
   bas.iSTR = 0;
   bas.iVIT = 0;
   bas.iDEX = 0;
   bas.iAGI = 0;
   bas.iINT = 0;
   bas.iWIL = 0;
}

void AttributeClear (FloatPrecentAttribute& pre)
{
   pre.fHP = 0.0f;
   pre.fMP = 0.0f;
   pre.fHPMax = 0.0f;
   pre.fMPMax = 0.0f;
   pre.fATK = 0.0f;
   pre.fDEF = 0.0f;
   pre.fHIT = 0.0f;
   pre.fCRI = 0.0f;
   pre.fMATK = 0.0f;
   pre.fMDEF = 0.0f;
   pre.fMHIT = 0.0f;
   pre.fMCRI = 0.0f;
   pre.fSDEF = 0.0f;
   pre.fWDEF = 0.0f;
   pre.fFlee = 0.0f;
   pre.fMove = 0.0f;
   pre.fATKSpeed = 0.0f;
   pre.fCasting = 0.0f;
   pre.fHPR = 0.0f;
   pre.fMPR = 0.0f;
}

void AttributeSet (AdvancedAttribute& attr, int hp, int mp, int hpMax, int mpMax,
				   int atk, int def, int hit, int cri, int matk, int mdef,
				   int mhit, int mcri, int sdef, int wdef, int flee,
				   float move, float atkSpeed, float casting)
{
	attr.iHP = hp;
	attr.iMP = mp;
	attr.iHPMax = hpMax;
	attr.iMPMax = mpMax;
	attr.iATK = atk;
	attr.iDEF = def;
	attr.iHIT = hit;
	attr.iCRI = cri;
	attr.iMATK = matk;
	attr.iMDEF = mdef;
	attr.iMHIT = mhit;
	attr.iMCRI = mcri;
	attr.iSDEF = sdef;
	attr.iWDEF = wdef;
	attr.iFlee = flee;
	attr.fMove = move;
	attr.fATKSpeed = atkSpeed;
	attr.fCasting = casting;
}

void AttributeAdd (AdvancedAttribute& attr, AdvancedAttribute add)
{
	attr.iHP += add.iHP;
	attr.iMP += add.iMP;
	attr.iHPMax += add.iHPMax;
	attr.iMPMax += add.iMPMax;
	attr.iATK += add.iATK;
	attr.iDEF += add.iDEF;
	attr.iHIT += add.iHIT;
	attr.iCRI += add.iCRI;
	attr.iMATK += add.iMATK;
	attr.iMDEF += add.iMDEF;
	attr.iMHIT += add.iMHIT;
	attr.iMCRI += add.iMCRI;
	attr.iSDEF += add.iSDEF;
	attr.iWDEF += add.iWDEF;
	attr.iFlee += add.iFlee;
	attr.fMove += add.fMove;
	attr.fATKSpeed += add.fATKSpeed;
	attr.fCasting += add.fCasting;
}

void AttributeAdd (ComplexAttribute& attr, ComplexAttribute add)
{
	AttributeAdd(attr.AdvAttr, add.AdvAttr);
	attr.ObsAttr.iHPR += add.ObsAttr.iHPR;
	attr.ObsAttr.iMPR += add.ObsAttr.iMPR;
}

void MultiPrecent(float& attr, int add)
{
   if(0 < add)
   {
      if(0.0f >= attr)
      {
         attr = add * 0.01f;
      }
      else
      {
         attr += attr * add * 0.01f;
      }
   }
}

void MultiPrecent(float& attr, float add)
{
   if(0.0f < add)
   {
      if(0.0f >= attr)
      {
         attr = add * 0.01f;
      }
      else
      {
         attr += attr * add * 0.01f;
      }
   }
}

void MultiPrecent(int& attr, float add)
{
   if(0.0f < add)
   {
      if(0 >= attr)
      {
         attr = (int) (add);
      }
      else
      {
         attr += (int) (attr * add);
      }
   }
}

void MultiPrecent(float& attr, float add, float bas)
{
   if(0.0f < add)
   {
      if(bas == attr)
      {
         attr = add * 0.01f;
      }
      else
      {
         attr += attr * add * 0.01f;
      }
   }
}

void AttributeMulti (AdvancedAttribute& attr, FloatPrecentAttribute add)
{
	MultiPrecent(attr.iHP, add.fHP);
	MultiPrecent(attr.iMP, add.fMP);
	MultiPrecent(attr.iHPMax, add.fHPMax);
	MultiPrecent(attr.iMPMax, add.fMPMax);
	MultiPrecent(attr.iATK, add.fATK);
	MultiPrecent(attr.iDEF, add.fDEF);
	MultiPrecent(attr.iHIT, add.fHIT);
	MultiPrecent(attr.iCRI, add.fCRI);
	MultiPrecent(attr.iMATK, add.fMATK);
	MultiPrecent(attr.iMDEF, add.fMDEF);
	MultiPrecent(attr.iMHIT, add.fMHIT);
	MultiPrecent(attr.iMCRI, add.fMCRI);
	MultiPrecent(attr.iSDEF, add.fSDEF);
	MultiPrecent(attr.iWDEF, add.fWDEF);
	MultiPrecent(attr.iFlee, add.fFlee);
	MultiPrecent(attr.fMove, add.fMove, 6.0f);
	MultiPrecent(attr.fATKSpeed, add.fATKSpeed, 1.5f);
	MultiPrecent(attr.fCasting, add.fCasting, 1.0f);
}

void AttributeMulti (ComplexAttribute& attr, FloatPrecentAttribute add)
{
	AttributeMulti(attr.AdvAttr, add);
	MultiPrecent(attr.ObsAttr.iHPR, add.fHPR);
	MultiPrecent(attr.ObsAttr.iMPR, add.fMPR);
}

void AttributeMulti (FloatPrecentAttribute& attr, FloatPrecentAttribute add)
{
   MultiPrecent(attr.fHP, add.fHP);
   MultiPrecent(attr.fMP, add.fMP);
   MultiPrecent(attr.fHPMax, add.fHPMax);
   MultiPrecent(attr.fMPMax, add.fMPMax);
   MultiPrecent(attr.fATK, add.fATK);
   MultiPrecent(attr.fDEF, add.fDEF);
   MultiPrecent(attr.fHIT, add.fHIT);
   MultiPrecent(attr.fCRI, add.fCRI);
   MultiPrecent(attr.fMATK, add.fMATK);
   MultiPrecent(attr.fMDEF, add.fMDEF);
   MultiPrecent(attr.fMHIT, add.fMHIT);
   MultiPrecent(attr.fMCRI, add.fMCRI);
   MultiPrecent(attr.fSDEF, add.fSDEF);
   MultiPrecent(attr.fWDEF, add.fWDEF);
   MultiPrecent(attr.fFlee, add.fFlee);
   MultiPrecent(attr.fMove, add.fMove);
   MultiPrecent(attr.fATKSpeed, add.fATKSpeed);
   MultiPrecent(attr.fCasting, add.fCasting);
   MultiPrecent(attr.fHPR, add.fHPR);
   MultiPrecent(attr.fMPR, add.fMPR);
}

void BasicAttributeSet (int level, BasicAttribute bas, AdvancedAttribute& adv, ObscureAttribute& obs)
{
   adv.iATK = (int) ((bas.iSTR * 236 * level) * 0.001f); 

   adv.iHPMax = (int) (((bas.iVIT * 645 * level) * 0.001f) + (150 / (level+1)));
   obs.iHPR = ((int) ((level * 0.1f) + (bas.iVIT * 0.025f)))+1;

   adv.iHIT = (int) ((bas.iDEX * 1.5f) + level * 0.2f);
   adv.iCRI = (int) (bas.iDEX * 0.02f);

   adv.iFlee = (int) ((level * 10) + bas.iAGI * 0.6f);
   adv.iSDEF = (int) ((level * 10) + bas.iAGI * 0.6f);
   adv.iWDEF = (int) ((level * 10) + bas.iAGI * 0.6f);

   adv.iMATK = (int) ((level * 0.3f) + bas.iINT * 0.001f);
   adv.iMCRI = (int) ((level * 0.1f) + bas.iINT * 0.55f);

   adv.iMPMax = ((level * 70) + bas.iWIL + 10);
   obs.iMPR = (int) ((level * 0.3f) + (bas.iWIL * 0.05f));

   adv.iHP = adv.iHPMax;
   adv.iMP = adv.iMPMax;
}