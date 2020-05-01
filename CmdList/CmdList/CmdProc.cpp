#include "pch.h"
#include "CmdProc.h"

CMD_MAP *pCurCmdMap;

void CmdProc()
{
	if (NULL != pCurCmdMap)
	{
		char szBuf[500] = "";
		char *argv[10] = {NULL};
		const CMD_MAP *pTemp = NULL;
		int nRet = 0;

		while (true)
		{
			pTemp = pCurCmdMap;
			MyPrintf("%s->", pTemp[-1].m_pCmdName);
			nRet = Handle(argv, szBuf);
			ToLower(argv[0]);

			while (NULL != pTemp->m_pFunc)
			{
				if (StrCmp(argv[0], pTemp->m_pCmdName))
				{
					if (nRet == pTemp->m_nArgc || 0 == nRet)
					{
						pTemp->m_pFunc(argv, nRet);
					}	
					else
					{
						MyPrintf("\nInput Command Error...\n");
					}
					break;
				}

				pTemp++;
			}

			if (NULL == pTemp->m_pFunc)
			{
				MyPrintf("\nInput Command Error...\n");
			}

		}

	}
}

void Cls(char **argv, int nNum)
{
	if (NULL != argv && NULL != *argv)
	{
		system("cls");
	}
}

void Help(char **argv, int nNum)
{
	if (NULL != argv && NULL != *argv && NULL != pCurCmdMap)
	{
		int i = 0;
		MyPrintf("CmdName\t\tCmdInfo\n");
		if (0 == nNum)
		{	
			for (i = 0; NULL != pCurCmdMap[i].m_pFunc; i++)
			{
				MyPrintf("%s\t\t%s\n", pCurCmdMap[i].m_pCmdName, pCurCmdMap[i].m_pCmdInfo);
			}
		}
		else
		{
			i = 0;
			while (NULL != pCurCmdMap[i].m_pFunc)
			{
				if (StrCmp(argv[1], pCurCmdMap[i].m_pCmdName))
				{
					MyPrintf("%s\t\t%s\n", pCurCmdMap[i].m_pCmdName, pCurCmdMap[i].m_pCmdInfo);
					break;
				}
				i++;
			}
		}
	}
}

int Handle(char **argv, char *pDes)
{
	int nRet = -1;
	if (NULL != pDes && NULL != argv)
	{
		nRet = 0;
		bool bFlag = false;
		char *pTemp = pDes;

 		while (true)
		{
			*pDes = getchar();
			if (' ' != *pDes && '\n' != *pDes)
			{
				pDes++;
				bFlag = true;
				continue;
			}
			else
			{
				if (bFlag && '\n' == *pDes)
				{
					*argv = pTemp;
					*pDes = '\0';
					break;
				}
				else if(bFlag && ' ' == *pDes)
				{
					if ('\0' != *(pDes - 1))
					{
						*argv = pTemp;
						*pDes = '\0';
						nRet++;

						pDes++;
						argv++;
						pTemp = pDes;
					}								
				}
				
			}
		}
	}

	return nRet;
}
