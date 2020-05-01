#include "pch.h"
#include "MyIO.h"

int MyPrintf(const char *pFormat, ...)
{
	int nRet = -1;

	if (NULL != pFormat)
	{
		nRet = 0;
		const char *pStr = pFormat;
		const char * const *ppTemp = &pFormat;

		while ('\0' != *pStr)
		{
			if ('%' == *pStr)
			{
				pStr++;
				ppTemp++;
				switch (*pStr)
				{
				case 'c':
				{
					putchar(*(char *)ppTemp);
					nRet++;
				}
				break;
				case 's':
				{
					nRet += PutStr(*ppTemp);
				}
				break;
				case 'd':
				{
					char szBuf[20] = "";
					nRet += PutStr(I_TO_A(szBuf, *(int *)ppTemp));
				}
				break;
				default:
				{
					pStr--;
					ppTemp--;
					putchar(*pStr);
				}
				break;
				}
			}
			else
			{
				putchar(*pStr);
				nRet++;
			}
			pStr++;
		}

	}

	return nRet;
}

int MyScanf(const char *pFormat, ...)
{
	int nRet = -1;

	if (NULL != pFormat)
	{
		nRet = 0;
		const char *pStr = pFormat;
		char * const *ppTemp = (char * const *)&pFormat;

		while ('\0' != *pStr)
		{
			if ('%' == *pStr)
			{
				pStr++;
				ppTemp++;
				switch (*pStr)
				{
				case 'c':
				{
					char szBuf[20] = "";
					**ppTemp = GetStr(szBuf)[0];
					nRet++;
				}
				break;
				case 's':
				{
					char szBuf[20] = "";
					GetStr(*ppTemp);
					nRet++;
				}
				break;
				case 'd':
				{
					char szBuf[20] = "";
					**(int **)ppTemp = A_TO_I(GetStr(szBuf));
					nRet++;
				}
				break;
				default:
				{
					pStr--;
					ppTemp--;
				}
				break;
				}
			}
			pStr++;
		}

	}

	return nRet;
}


int A_TO_I(const char *pDes)
{
	int nRet = -1;

	if (NULL != pDes)
	{
		char ch = *pDes;
		nRet = 0;


		if ('-' == ch)
		{
			pDes++;
		}

		while ('\0' != *pDes)
		{
			nRet = nRet * 10 + *pDes - '0';
			pDes++;
		}

		if ('-' == ch)
		{
			nRet = -nRet;
		}

	}

	return nRet;
}

char* I_TO_A(char *pDes, int nNum)
{
	if (NULL != pDes)
	{
		int nLen = 0;
		int nTemp = nNum;

		if (nNum <= 0)
		{
			if (0 == nNum)
			{
				pDes[0] = '0';
				pDes[1] = '\0';
				return pDes;
			}
			nLen++;
			nNum = -nNum;
		}

		while (0 != nTemp)
		{
			nTemp /= 10;
			nLen++;
		}
		pDes[nLen--] = '\0';

		while (0 != nNum)
		{
			pDes[nLen--] = nNum % 10 + '0';
			nNum /= 10;
		}
	}

	return pDes;
}


int PutStr(const char *pDes)
{
	int nRet = -1;

	if (NULL != pDes)
	{
		nRet = 0;

		while ('\0' != *pDes)
		{
			putchar(*pDes++);
			nRet++;
		}
	}

	return nRet;
}

char* GetStr(char *pDes)
{
	if (NULL != pDes)
	{
		char *pTemp = pDes;
		bool bFlag = false;

		while (true)
		{
			*pTemp = getchar();

			if ('\n' != *pTemp && ' ' != *pTemp)
			{
				bFlag = true;
				pTemp++;
			}
			else
			{
				if (bFlag)
				{
					*pTemp = '\0';
					break;
				}
			}
		}

	}

	return pDes;
}

