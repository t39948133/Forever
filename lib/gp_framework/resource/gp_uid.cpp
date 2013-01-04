#include "gp_uid.h"

namespace GP
{

long long UID::preID = 0 ;

bool UID::operator == (const UID& uid)const
{
	return id == uid.id ;
}

bool UID::operator < (const UID& uid)const
{
	return id < uid.id ;
}

void UID::generate ()
{
	id = preID ;
	preID ++ ;
}

}