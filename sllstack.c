#include <stdlib.h>
#include "sllstack.h"

static struct node_st *sp = NULL;
static int isp = 0;
const int * const ispp = &isp;

void
push(int val)
{
	struct node_st *prev = sp;
	sp = (struct node_st *) malloc(sizeof(struct node_st));
	sp->prev = prev;
	sp->val = val;
	isp++;
}

int
pop(void)
{
	if (sp == NULL)
	{
		return 0;
	}
	else
	{
		struct node_st *prev = sp->prev;
		int val = sp->val;
		free(sp);
		sp = prev;
		isp--;
		return val;
	}
}

int
top(void)
{
	if (sp == NULL)
	{
		return 0;
	}
	else
	{
		return sp->val;
	}
}
