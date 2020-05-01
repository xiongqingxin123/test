#ifndef __STUDENTCMD_H__
#define __STUDENTCMD_H__

#include "CmdProc.h"

void CreateStudent(char **argv, int nNum);
void AddStudent(char **argv, int nNum);
void InsertStudent(char **argv, int nNum);
void LoadStudent(char **argv, int nNum);
void SaveStudent(char **argv, int nNum);
void DeleteStudent(char **argv, int nNum);
void ClearStudent(char **argv, int nNum);
void ModifyStudent(char **argv, int nNum);
void ShowStudent(char **argv, int nNum);
void FindStudent(char **argv, int nNum);
void BackStudent(char **argv, int nNum);

EXTERN_CMD_MAP(Student)


#endif // !__STUDENTCMD_H__