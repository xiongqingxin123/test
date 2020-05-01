#include "pch.h"
#include "StudentCmd.h"
#include "Student.h"
#include "Person.h"

LINKER *g_pHead_Student;

SET_CMD_MAP(Student)
	COMMAND(create, Create List, 4, CreateStudent)
	COMMAND(add, Add Node, 4, AddStudent)
	COMMAND(insert, Insert Node, 2, InsertStudent)
	COMMAND(load, Load File, 1, LoadStudent)
	COMMAND(save, Save File, 1, SaveStudent)
	COMMAND(clear, Clear List, 0, ClearStudent)
	COMMAND(modify, Modify Node, 1, ModifyStudent)
	COMMAND(show, Show List, 0, ShowStudent)
	COMMAND(find, Find Node, 1, FindStudent)
	COMMAND(delete, Delete Node, 1, DeleteStudent)
	COMMAND(back, Back List, 0, BackStudent)
CMD_MAP_END


void CreateStudent(char **argv, int nNum)
{
	if (NULL != g_pHead_Student)
	{
		MyPrintf("\nList already exist...\n");
		return;
	}

	CreateList(&g_pHead_Student, GET_CREATE(STUDENT), nNum, argv);


	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList create fail...\n");
	}
	else
	{
		MyPrintf("\nList create succeed...\n");
	}
	
}

void AddStudent(char **argv, int nNum)
{
	int nNumber = 0;

	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n");
		return;
	}
	
	nNumber = AddNode(g_pHead_Student, nNum, argv);

	if (SUCCEED == nNumber)
	{
		MyPrintf("\nNode add succeed...\n");
	}
	else
	{
		MyPrintf("\nNode add fail...\n");
	}
}

void InsertStudent(char **argv, int nNum)
{
	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n");
		return;
	}

	int mode = 0;
	int nNumber = 0;
	LINKER * pTemp = NULL;

	if (0 != nNum)
	{
		mode = A_TO_I(argv[2]);
		pTemp = FindNode(g_pHead_Student, nNum, A_TO_I(argv[1]));
	}
	else
	{
		MyPrintf("\nInput Insert Pos: ");

		pTemp = FindNode(g_pHead_Student, 0);

		MyPrintf("\nInput Insert mode: \n1.Ç°²å\n2.ºó²å\n");
		MyScanf("%d", &mode);
		
	}

	if (NULL == pTemp)
	{
		MyPrintf("\nInsert pos not exist...\n");

		return;
	}

	if (1 == mode)
	{
		nNumber = InsertNode(&g_pHead_Student, pTemp, front);
	}
	else
	{
		nNumber = InsertNode(&g_pHead_Student, pTemp, behind);
	}

	if (SUCCEED == nNumber)
	{
		MyPrintf("\nNode insert succeed...\n");
	}
	else
	{
		MyPrintf("\nNode insert fail...\n");
	}
}

void LoadStudent(char **argv, int nNum)
{
	char File[60] = "";
	char FilePath[60] = "Data/";

	if (NULL != g_pHead_Student)
	{
		char ch = 0;
		MyPrintf("\nList already exist...\n");

		MyPrintf("\nPlease Choose: \nY.save list and read new file\nN.read new file\n");
		MyScanf("%c", &ch);

		if ('Y' == ch || 'y' == ch)
		{
			SaveStudent(argv, nNum);
		}
		ClearList(&g_pHead_Student);
	}

	if (0 != nNum)
	{
		StrCpy(File, argv[1]);
	}
	else
	{
		MyPrintf("\nInput read file name: ");
		MyScanf("%s", File);
	}

	StrCat(File, ".txt");
	StrCat(FilePath, File);

	if (SUCCEED == FileRead(&g_pHead_Student, FilePath, "r", GET_READ(STUDENT)))
	{
		MyPrintf("\nFile read succeed...\n");
	}
	else
	{
		MyPrintf("\nFile read fail...\n");
	}
}

void SaveStudent(char **argv, int nNum)
{

	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n");
		return;
	}

	char File[60] = "";
	char FilePath[60] = "Data/";

	if (0 != nNum)
	{
		StrCpy(File, argv[1]);
	}
	else
	{
		MyPrintf("\nInput read file name: ");
		MyScanf("%s", File);
	}

	StrCat(File, ".txt");
	StrCat(FilePath, File);

	if (SUCCEED == FileSave(g_pHead_Student, FilePath, "w"))
	{
		MyPrintf("\nList save succeed...\n");
	}
	else
	{
		MyPrintf("\nList save fail...\n");
	}
}

void DeleteStudent(char **argv, int nNum)
{
	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n\n");
		return;
	}

	LINKER *pTemp = NULL;

	if (0 != nNum)
	{
		pTemp = FindNode(g_pHead_Student, nNum, A_TO_I(argv[1]));
	}
	else
	{
		MyPrintf("\nInput delete node pos: ");

		pTemp = FindNode(g_pHead_Student, 0);
	}
		

	if (NULL == pTemp)
	{
		MyPrintf("\nDelete node not exist...\n");
	}
	else
	{
		if (SUCCEED == DeleteNode(&g_pHead_Student, pTemp))
		{
			MyPrintf("\nNode delete succeed...\n");
		}
		else
		{
			MyPrintf("\nNode delete fail...\n");
		}
	}
	
}

void ClearStudent(char **argv, int nNum)
{
	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n");
	}
	else
	{
		if (SUCCEED == ClearList(&g_pHead_Student))
		{
			MyPrintf("\nList clear succeed...\n");
		}
		else
		{
			MyPrintf("\nList clear fail...\n");
		}
	}
}

void ModifyStudent(char **argv, int nNum)
{
	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n\n");
		return;
	}

	LINKER *pTemp = NULL;

	if (0 != nNum)
	{
		pTemp = FindNode(g_pHead_Student, nNum, A_TO_I(argv[1]));
	}
	else
	{
		MyPrintf("\nInput modify node pos: ");

		pTemp = FindNode(g_pHead_Student, 0);
	}

	if (NULL == pTemp)
	{
		MyPrintf("\nModify Node not exist...\n");
	}
	else
	{
		if (SUCCEED == ModifyNode(pTemp))
		{
			MyPrintf("\nNode modify succeed...\n");
		}
		else
		{
			MyPrintf("\nNode modify fail...\n");
		}
	}
	
}

void ShowStudent(char **argv, int nNum)
{
	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n");
	}
	else
	{
		MyPrintf("Number\t\tName\t\tAge\t\tSex\n");
		ShowList(g_pHead_Student);
	}
}

void FindStudent(char **argv, int nNum)
{
	if (NULL == g_pHead_Student)
	{
		MyPrintf("\nList not exist...\n");
		return;
	}

	LINKER *pTemp = NULL;

	if (0 != nNum)
	{
		pTemp = FindNode(g_pHead_Student, nNum, A_TO_I(argv[1]));
	}
	else
	{
		MyPrintf("\nInput find node pos: ");

		pTemp = FindNode(g_pHead_Student, 0);
	}

	if (NULL == pTemp)
	{
		MyPrintf("\nNode not exist...\n");
	}
	else
	{
		MyPrintf("Number\t\tName\t\tAge\t\tSex\n");
		ShowNode(pTemp);
	}
}

void BackStudent(char **argv, int nNum)
{
	if (NULL != g_pHead_Student)
	{
		char ch = 0;
		MyPrintf("\nInput selete: \nY.save list and exit\nN.exit\n");
		MyScanf("%c", &ch);

		if ('Y' == ch || 'y' == ch)
		{
			SaveStudent(argv, nNum);
		}
	}

	ClearList(&g_pHead_Student);

	Cls(argv, nNum);
	SET_MAP(GET_MAP(List))
}
