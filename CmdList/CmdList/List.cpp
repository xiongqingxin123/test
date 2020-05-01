#include "pch.h"
#include "List.h"
int CreateList(LINKER **ppHead, PFUNC_CREATE pCreate, int nFlag, ...)
{
	if (NULL != ppHead && NULL == *ppHead && NULL != pCreate)
	{
		LINKER *pNew = pCreate();

		if (NULL == pNew)
		{
			return D_M_A_ERROR;
		}

		pNew->m_pFunc->pInput(pNew, nFlag, *(&nFlag + 1));

		*ppHead = pNew;

		return SUCCEED;
	}

	return POINT_ERROR;
}

int AddNode(LINKER *pHead, int nFlag, ...)
{
	if (NULL != pHead)
	{
		LINKER *pNew = pHead->m_pFunc->pCreate();

		if (NULL == pNew)
		{
			return D_M_A_ERROR;
		}

		pNew->m_pFunc->pInput(pNew, nFlag, *(&nFlag + 1));

		while (NULL != pHead->m_pNext)
		{
			pHead = pHead->m_pNext;
		}

		pNew->m_pLast = pHead;
		pHead->m_pNext = pNew;

		return SUCCEED;
	}

	return POINT_ERROR;
}

int InsertNode(LINKER **ppHead, LINKER *pPos, MODE mode)
{
	if (NULL != ppHead && NULL != *ppHead && NULL != pPos)
	{
		LINKER *pNew = (*ppHead)->m_pFunc->pCreate();

		if (NULL == pNew)
		{
			return D_M_A_ERROR;
		}

		pNew->m_pFunc->pInput(pNew, false);

		if (front == mode)
		{
			if (pPos != *ppHead)
			{

				pNew->m_pLast = pPos->m_pLast;
				pPos->m_pLast->m_pNext = pNew;

			}
			else
			{
				*ppHead = pNew;
			}
			pNew->m_pNext = pPos;
			pPos->m_pLast = pNew;
		}
		else
		{
			if (NULL != pPos->m_pNext)
			{
				pNew->m_pNext = pPos->m_pNext;

				pPos->m_pNext->m_pLast = pNew;

			}
			pNew->m_pLast = pPos;
			pPos->m_pNext = pNew;
		}

		return SUCCEED;
	}

	return POINT_ERROR;
}


int DeleteNode(LINKER **ppHead, LINKER *pPos)
{
	if (NULL != ppHead && NULL != *ppHead && NULL != pPos)
	{
		if (pPos == *ppHead)
		{
			if (NULL != pPos->m_pNext)
			{
				pPos->m_pNext->m_pLast = NULL;
			}
			*ppHead = pPos->m_pNext;
		}
		else
		{
			if (NULL != pPos->m_pNext)
			{
				pPos->m_pNext->m_pLast = pPos->m_pLast;
			}
			pPos->m_pLast->m_pNext = pPos->m_pNext;
		}

		pPos->m_pFunc->pRelease(pPos);

		return SUCCEED;
	}

	return POINT_ERROR;
}

int ClearList(LINKER **ppHead)
{
	if (NULL != ppHead && NULL != *ppHead)
	{
		LINKER *pTemp = NULL;

		while (NULL != *ppHead)
		{
			pTemp = *ppHead;
			*ppHead = (*ppHead)->m_pNext;
			pTemp->m_pFunc->pRelease(pTemp);
		}

		return SUCCEED;
	}

	return POINT_ERROR;
}


int ModifyNode(LINKER *pPos)
{
	if (NULL != pPos)
	{
		return pPos->m_pFunc->pInput(pPos, false);
	}

	return POINT_ERROR;
}


LINKER* FindNode(LINKER *pHead, int nFlag, ...)
{
	if (NULL != pHead)
	{
		return pHead->m_pFunc->pFind(pHead, nFlag, *(&nFlag + 1));
	}

	return NULL;
}


int ShowNode(LINKER *pPos)
{
	if (NULL != pPos)
	{
		return pPos->m_pFunc->pOutput(pPos);
	}

	return POINT_ERROR;
}

int ShowList(LINKER *pHead)
{
	if (NULL != pHead)
	{
		while (NULL != pHead)
		{
			pHead->m_pFunc->pOutput(pHead);

			pHead = pHead->m_pNext;
		}

		return SUCCEED;
	}

	return POINT_ERROR;
}


int FileRead(LINKER **ppHead, const char *pFilename, const char *pMode, PFUNC_READ pRead)
{
	if (NULL != ppHead && NULL != pFilename && NULL != pMode && NULL != pRead)
	{
		return pRead(ppHead, pFilename, pMode);
	}

	return POINT_ERROR;
}

int FileSave(LINKER *pHead, const char *pFilename, const char *pMode)
{
	if (NULL != pHead && NULL != pFilename && NULL != pMode)
	{
		return pHead->m_pFunc->pSave(pHead, pFilename, pMode);
	}

	return POINT_ERROR;
}

