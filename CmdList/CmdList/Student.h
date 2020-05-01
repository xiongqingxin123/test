#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "List.h"

struct STUDENT
{
	LINKER Linker;

	//data
	int m_nNumber;
	char m_szName[20];
	int m_nAge;
	char m_szSex[4];
};

EXTERN_CREATE(STUDENT)

EXTERN_FUNC_TABLE(STUDENT)

EXTERN_READ(STUDENT)

#endif // !__STUDENT_H__
