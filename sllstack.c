#include <stdlib.h>
#include "sllstack.h"

struct node_st *sp = NULL;

void
push(int val)
{
	struct node_st *prev = sp;
	sp = (struct node_st *) malloc(sizeof(struct node_st));
	sp->prev = prev;
	sp->val = val;
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
		return val;
	}
}
