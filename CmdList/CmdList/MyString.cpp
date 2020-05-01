#include "pch.h"
#include "MyString.h"

int StrLen(const char *pDes)
{
	int nRet = -1;

	if (NULL != pDes)
	{
		for (nRet = 0; '\0' != *pDes++; nRet++);
	}

	return nRet;
}

char* StrCpy(char *pDes, const char *pScr)
{
	if (NULL != pDes && NULL != pScr)
	{
		char *pTemp = pDes;

		while ('\0' != *pScr)
		{
			*pTemp++ = *pScr++;
		}

		*pTemp = '\0';
	}

	return pDes;
}

char* StrCat(char *pDes, const char *pScr)
{
	if (NULL != pDes && NULL != *pScr)
	{
		char *pTemp = pDes;

		while ('\0' != *pTemp++);
		pTemp--;

		while ('\0' != *pScr)
		{
			*pTemp++ = *pScr++;
		}

		*pTemp = '\0';
	}

	return pDes;
}

bool StrCmp(const char *pStr1, const char *pStr2)
{
	if (NULL != pStr1 && NULL != pStr2)
	{
		if (pStr1 == pStr2)
		{
			return true;
		}

		while ('\0' != *pStr2)
		{
			if (*pStr1++ != *pStr2++)
			{
				return false;
			}
		}

		if ('\0' == *pStr1)
		{
			return true;
		}

	}

	return false;
}

char* ToUpper(char *pDes)
{
	if (NULL != pDes)
	{
		char *pTemp = pDes;

		while ('\0' != *pTemp)
		{
			if (*pTemp >= 'a' && *pTemp <= 'z')
			{
				*pTemp -= 32;
			}
			pTemp++;
		}
	}

	return pDes;
}

char* ToLower(char *pDes)
{
	if (NULL != pDes)
	{
		char *pTemp = pDes;

		while ('\0' != *pTemp)
		{
			if (*pTemp >= 'A' && *pTemp <= 'Z')
			{
				*pTemp += 32;
			}
			pTemp++;
		}
	}

	return pDes;
}
