#ifndef _ATTRILBUTESET_H_
#define _ATTRILBUTESET_H_

#include "Common.h"

void AttributeClear (AdvancedAttribute& attr);

void AttributeClear (ObscureAttribute& obs);

void AttributeClear (ComplexAttribute& com);

void AttributeSet (AdvancedAttribute& attr, int hp = 0, int mp = 0, int hpMax = 0, int mpMax = 0,
				   int atk = 0, int def = 0, int hit = 0, int cri = 0, int matk = 0, int mdef = 0,
				   int mhit = 0, int mcri = 0, int sdef = 0, int wdef = 0, int flee = 0,
				   float move = 6.0f, float atkSpeed = 1.5f, float casting = 1.0f);

void AttributeAdd (AdvancedAttribute& attr, AdvancedAttribute add);

void BasisAttributeSet (int leve, BasisAttribute bas, AdvancedAttribute& adv, 
						ObscureAttribute& obs);

#endif