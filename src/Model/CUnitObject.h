#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"

class CUnitObject
{
public:
	CUnitObject(std::wstring strName,char level=0); //�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ0��)

	std::wstring getName();	//���o����W�r
	char getLevel();	//���o����

	void addHP(int hp);	//�W�[/���HP
	int getHP();	//���oHP
	int getHPMax();	//���o�̤jHP

	void addMP(int mp);	//�W�[/���MP
	int getMP();	//���oMP
	int getMPMax();	//���o�̤jMP
  
	void setAdvAttr(AdvancedAttribute advAttr);	//�]�w�ݩ�
	AdvancedAttribute getAdvAttr();	//���o�ݩ�

private:
	char m_level;	//����
	std::wstring m_strName;	//�W�r
	AdvancedAttribute m_advAttr;	//�ݩ�

};

#endif