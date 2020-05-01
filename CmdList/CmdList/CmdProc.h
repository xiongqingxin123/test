#ifndef __CMDPROC_H__
#define __CMDPROC_H__

struct CMD_MAP
{
	const char *m_pCmdName;
	const char *m_pCmdInfo;
	int m_nArgc;
	void (*m_pFunc)(char **argv, int nNum);
};

extern CMD_MAP *pCurCmdMap;

#define EXTERN_CMD_MAP(name)\
	extern CMD_MAP g_##name[];

#define SET_MAP(name)\
	pCurCmdMap = &name[1];

#define GET_MAP(name)\
	g_##name

#define SET_CMD_MAP(name)\
	CMD_MAP g_##name[] = {{#name, NULL, NULL},

#define COMMAND(cmd_name, cmd_info, argc, pfn)\
	{#cmd_name, #cmd_info, argc, pfn},

#define CMD_MAP_END\
	{"help", "Help", 1, Help}, {"cls", "Cls", 0, Cls}, {NULL}};

void CmdProc();
void Cls(char **argv, int nNum);
void Help(char **argv, int nNum);
int Handle(char **argv, char *pDes);

#endif // !__CMDPROC_H__
