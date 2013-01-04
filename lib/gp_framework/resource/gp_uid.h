#ifndef _GP_UID_H_
#define _GP_UID_H_

#include <map>
#include <assert.h>

namespace GP
{

class UID
{
private:
	long long id ;

	static long long preID ;

public:
	bool operator == (const UID& uid)const ;

	bool operator < (const UID& uid)const ;

	void generate () ;
} ;

}

#endif




