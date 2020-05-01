#ifndef __LIST_H__
#define __LIST_H__

enum MODE { front, behind };

struct LINKER;

typedef LINKER* (*PFUNC_CREATE)();
typedef int(*PFUNC_RELEASE)(LINKER *);
typedef int(*PFUNC_INPUT)(LINKER *, int nFlag, ...);
typedef int(*PFUNC_OUTPUT)(const LINKER *);
typedef LINKER* (*PFUNC_FIND)(LINKER *, int nFlag, ...);

typedef int(*PFUNC_READ)(LINKER **, const char *, const char *);
typedef int(*PFUNC_SAVE)(const LINKER *, const char *, const char *);

struct FUNC_TABLE
{
	PFUNC_CREATE pCreate;
	PFUNC_RELEASE pRelease;
	PFUNC_INPUT pInput;
	PFUNC_OUTPUT pOutput;
	PFUNC_FIND pFind;
	PFUNC_READ pRead;
	PFUNC_SAVE pSave;
};

struct LINKER
{
	FUNC_TABLE *m_pFunc;
	LINKER *m_pLast;
	LINKER *m_pNext;
};

int CreateList(LINKER **ppHead, PFUNC_CREATE pCreate, int nFlag, ...);
int AddNode(LINKER *pHead, int nFlag, ...);
int InsertNode(LINKER **ppHead, LINKER *pPos, MODE mode = behind);

int DeleteNode(LINKER **ppHead, LINKER *pPos);
int ClearList(LINKER **ppHead);

int ModifyNode(LINKER *pPos);

LINKER* FindNode(LINKER *pHead, int nFlag, ...);

int ShowNode(LINKER *pPos);
int ShowList(LINKER *pHead);

int FileRead(LINKER **ppHead, const char *pFilename, const char *pMode, PFUNC_READ pRead);
int FileSave(LINKER *pHead, const char *pFilename, const char *pMode);


////////////////////////////////////////////////

#define INPUT(name) Input##name
#define OUTPUT(name) Output##name
#define FIND(name) Find##name
#define READ(name) Read##name
#define SAVE(name) Save##name

#define EXTERN_CREATE(name)\
	LINKER* Create##name();

#define GET_CREATE(name) Create##name

#define EXTERN_FUNC_TABLE(name)\
	extern FUNC_TABLE g_Func_Table##name;

#define GET_FUNC_TABLE(name) g_Func_Table##name

#define EXTERN_READ(name)\
	int Read##name(LINKER **, const char *, const char *);

#define GET_READ(name)	Read##name

#define DEFINE_FUNC_TABLE(name)\
	LINKER* Create##name()\
	{\
		name *pNew = new name;\
\
		if (NULL != pNew)\
		{\
			pNew->Linker.m_pFunc = &g_Func_Table##name;\
			pNew->Linker.m_pLast = NULL;\
			pNew->Linker.m_pNext = NULL;\
		}\
\
		return (LINKER*)pNew;\
	}\
\
	int Release##name(LINKER *pNode)\
	{\
		if (NULL != pNode)\
		{\
			delete (name *)pNode;\
\
			return SUCCEED;\
		}\
\
		return POINT_ERROR;\
	}\
\
FUNC_TABLE g_Func_Table##name = {Create##name, Release##name, Input##name, Output##name, Find##name, Read##name, Save##name};


#endif
