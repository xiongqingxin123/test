#include "pch.h"
#include "Student.h"

#pragma warning(disable:4996)

int INPUT(STUDENT)(LINKER *pPos, int nFlag, ...);
int OUTPUT(STUDENT)(const LINKER *pPos);
LINKER* FIND(STUDENT)(LINKER *pHead, int nFlag, ...);
int SAVE(STUDENT)(const LINKER *pHead, const char *pFilename, const char *pMode);

DEFINE_FUNC_TABLE(STUDENT)

int INPUT(STUDENT)(LINKER *pPos, int nFlag, ...)
{
	if (NULL != pPos)
	{
		STUDENT *pTemp = (STUDENT *)pPos;

		if (0 == nFlag)
		{
			MyPrintf("Input Number: ");
			MyScanf("%d", &pTemp->m_nNumber);

			MyPrintf("Input Name: ");
			MyScanf("%s", pTemp->m_szName);


			MyPrintf("Input Age: ");
			MyScanf("%d", &pTemp->m_nAge);

			MyPrintf("Input Sex: ");
			MyScanf("%s", pTemp->m_szSex);
		}
		else
		{
			char **argv = (char **)*(&nFlag + 1);

			((STUDENT *)pTemp)->m_nNumber = A_TO_I(argv[1]);
			((STUDENT *)pTemp)->m_nAge = A_TO_I(argv[3]);

			StrCpy(((STUDENT *)pTemp)->m_szName, argv[2]);
			StrCpy(((STUDENT *)pTemp)->m_szSex, argv[4]);
		}

		return SUCCEED;
	}

	return POINT_ERROR;
}

int OUTPUT(STUDENT)(const LINKER *pPos)
{
	if (NULL != pPos)
	{
		STUDENT *pTemp = (STUDENT *)pPos;
		MyPrintf("%d\t\t%s\t\t%d\t\t%s\n", pTemp->m_nNumber, pTemp->m_szName, pTemp->m_nAge, pTemp->m_szSex);

		return SUCCEED;
	}

	return POINT_ERROR;
}

LINKER* FIND(STUDENT)(LINKER *pHead, int nFlag, ...)
{
	if (NULL != pHead)
	{
		STUDENT *&pTemp = (STUDENT *&)pHead;

		int nNumber = 0;

		if (0 == nFlag)
		{
			MyScanf("%d", &nNumber);
		}
		else
		{
			nNumber = *(&nFlag + 1);
		}
		
		while (NULL != pHead)
		{
			if (nNumber == pTemp->m_nNumber)
			{
				return pHead;
			}

			pHead = pHead->m_pNext;
		}

		return SUCCEED;
	}

	return NULL;
}

int READ(STUDENT)(LINKER **ppHead, const char *pFilename, const char *pMode)
{
	if (NULL != ppHead && NULL != pFilename && NULL != pMode)
	{
		FILE *pFile = fopen(pFilename, pMode);

		if (NULL == pFile)
		{
			return POINT_ERROR;
		}

		STUDENT *pNew = NULL;
		LINKER *pEnd = NULL;

		while (!feof(pFile))
		{
			pNew = new STUDENT;

			if (NULL == pNew)
			{
				return D_M_A_ERROR;
			}

			pNew->Linker.m_pFunc = &GET_FUNC_TABLE(STUDENT);
			pNew->Linker.m_pLast = NULL;
			pNew->Linker.m_pNext = NULL;

			if (0 == fread((char *)pNew + 12, sizeof(STUDENT) - 12, 1, pFile))
			{
				delete pNew;
				break;
			}

			if (NULL == *ppHead)
			{
				*ppHead = (LINKER *)pNew;
			}
			else
			{
				pNew->Linker.m_pLast = pEnd;
				pEnd->m_pNext = (LINKER *)pNew;
			}
			pEnd = (LINKER *)pNew;
		}

		fclose(pFile);

		return SUCCEED;
	}

	return POINT_ERROR;
}


int SAVE(STUDENT)(const LINKER *pHead, const char *pFilename, const char *pMode)
{
	if (NULL != pHead && NULL != pFilename && NULL != pMode)
	{
		FILE *pFile = fopen(pFilename, pMode);

		if (NULL == pFile)
		{
			return POINT_ERROR;
		}

		while (NULL != pHead)
		{
			fwrite((char *)pHead + 12, sizeof(STUDENT) - 12, 1, pFile);
			pHead = pHead->m_pNext;
		}

		fclose(pFile);
		return SUCCEED;
	}

	return POINT_ERROR;
}
