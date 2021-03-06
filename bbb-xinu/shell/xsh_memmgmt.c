#include <newmem.h>

int n;
pid32 pid;
sid32 consumed,produced;
struct memblk* memptr;
char *sp,*newsp;
struct	procent	*prptr;
int stksize;
void getFreeBlocks(int);

shellcmd xsh_memmgmt(int nargs, char *args[])
{
	/* For argument '--help', emit help about the 'memmgmt' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("use: %s \n\n", args[0]);
		printf("\tMemory statistics\n");
		printf("\tfree list.\n");
		printf("Options:\n");
		printf("\t--help\t\tdisplay this help and exit\n");
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more info\n", args[0]);
		return 1;
	}

	getFreeBlocks(1);
//getmem
	int i = (int) getmem(sizeof(int));

	getFreeBlocks(2);
	stksize = 1024;
	pid = memcreate(test, stksize, 20,"test", 0);
//after process creation
	getFreeBlocks(3);
	prptr = &proctab[pid];
	resume(pid);
	return 0;
}

void getFreeBlocks(int a)
{
	printf("\nFree Blocks ");
	if(a==1)	printf("at the start:\n");
	else if(a==2)	printf("after getmem:\n");
	else if(a==3)	printf("after process creation:\n");
	printf("Block address  Length in decimal \n");
	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext)
		printf("  0x%08x    %9d\n", memptr, memptr->mlength);
	printf("\n");
}
