#include <stdio.h>
#include "sllstack.h"

static char usage[] = "Usage: rpn < p | c > str";

int
main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "%s", usage);
		return -1;
	}
	else
	{
		char *str = argv[2];
		switch (argv[1][0])
		{
			case 'p':
				break;
			case 'c':
				break;
			default:
				return -1;
				break;
		}
	}
	
	return 0;
}
