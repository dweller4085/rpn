#include <stdlib.h>
#include "sllstack.h"

struct node_st { struct node_st *prev; int val; };

static struct node_st null_node = { &null_node, 0 };
static struct node_st *sp = &null_node;
static int isp = 0;
static int st = 0;

const int * const spp = &isp;
const int * const stp = &st;

void
push(int val)
{
	struct node_st *prev = sp;
	sp = (struct node_st *) malloc(sizeof(struct node_st));
	sp->prev = prev;
	sp->val = val;
	st = val;
	isp++;
}

int
pop(void)
{
	if (sp == &null_node)
	{
		return 0;
	}
	else
	{
		struct node_st *prev = sp->prev;
		int val = sp->val;
		free(sp);
		sp = prev;
		st = sp->val;
		isp--;
		return val;
	}
}
