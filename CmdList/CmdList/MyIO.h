#ifndef __MYIO_H__
#define __MYIO_H__

int MyPrintf(const char *pFormat, ...);
int MyScanf(const char *pFormat, ...);

int A_TO_I(const char *pDes);
char* I_TO_A(char *pDes, int nNum);

int PutStr(const char *pDes);
char* GetStr(char *pDes);

#endif // !__MYIO_H__
