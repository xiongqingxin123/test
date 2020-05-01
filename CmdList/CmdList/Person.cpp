#include "pch.h"
#include "Person.h"
#include "StudentCmd.h"

SET_CMD_MAP(List)
	COMMAND(student, Create Student list, 0, Student)
	COMMAND(exit, Exit, 0, Exit)
CMD_MAP_END


void Student(char **argv, int nNum)
{
	if (NULL != argv)
	{
		Cls(argv, nNum);
		SET_MAP(GET_MAP(Student))
	}
}

void Exit(char **argv, int nNum)
{
	if (NULL != argv)
	{
		exit(0);
	}
}
