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
	attr.fMove = 6.0f;
	attr.fATKSpeed = 1.5f;
	attr.fCasting = 1.0f;
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

void MultiPrecent(int& attr, int add)
{
	if(0 != add)
	{
		attr =(int) (attr * add * 0.01f);
	}
}

void AttributeMulti (AdvancedAttribute& attr, AdvancedAttribute add)
{
	attr.iHP *= add.iHP;
	attr.iMP *= add.iMP;
	attr.iHPMax *= add.iHPMax;
	attr.iMPMax *= add.iMPMax;
	attr.iATK *= add.iATK;
	attr.iDEF *= add.iDEF;
	attr.iHIT *= add.iHIT;
	attr.iCRI *= add.iCRI;
	attr.iMATK *= add.iMATK;
	attr.iMDEF *= add.iMDEF;
	attr.iMHIT *= add.iMHIT;
	attr.iMCRI *= add.iMCRI;
	attr.iSDEF *= add.iSDEF;
	attr.iWDEF *= add.iWDEF;
	attr.iFlee *= add.iFlee;
	attr.fMove *= add.fMove;
	attr.fATKSpeed *= add.fATKSpeed;
	attr.fCasting *= add.fCasting;
}

void AttributeMulti (ComplexAttribute& attr, ComplexAttribute add)
{
	AttributeMulti(attr.AdvAttr, add.AdvAttr);
	attr.ObsAttr.iHPR *= add.ObsAttr.iHPR;
	attr.ObsAttr.iMPR *= add.ObsAttr.iMPR;
}

void BasisAttributeSet (int leve, BasisAttribute bas, AdvancedAttribute& adv, ObscureAttribute& obs)
{
	adv.iATK = (int) ((bas.iSTR * 236 * leve) * 0.001f); 

	adv.iHPMax = (int) (((bas.iVIT * 645 * leve) * 0.001f) + (150 / (leve+1)));
	obs.iHPR = ((int) ((leve * 0.1f) + (bas.iVIT * 0.025f)))+1;

	adv.iHIT = (int) ((bas.iDEX * 1.5f) + leve * 0.2f);
	adv.iCRI = (int) (bas.iDEX * 0.02f);

	adv.iFlee = (int) ((leve * 10) + bas.iAGI * 0.6f);
	adv.iSDEF = (int) ((leve * 10) + bas.iAGI * 0.6f);
	adv.iWDEF = (int) ((leve * 10) + bas.iAGI * 0.6f);

	adv.iMATK = (int) ((leve * 0.3f) + bas.iINT * 0.001f);
	adv.iMCRI = (int) ((leve * 0.1f) + bas.iINT * 0.55f);

	adv.iMPMax = ((leve * 70) + bas.iWIL + 10);
	obs.iMPR = (int) ((leve * 0.3f) + (bas.iWIL * 0.05f));
}