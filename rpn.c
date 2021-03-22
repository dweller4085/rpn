#include <stdio.h>
#include <stdlib.h>
#include "sllstack.h"

#define OUT_LEN 64

void infix_to_rpn(void);
void rpn_compute(void);
void error(char *, int);

static const char * str;

int
main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return -1;
	}
	else
	{
		str = argv[2];
		switch (argv[1][0])
		{
			case 'p':
				infix_to_rpn();
				break;
			case 'c':
				rpn_compute();
				break;
			default:
				return -1;
				break;
		}
	}
	
	return 0;
}

enum staat_st { START, OP, VAR, READING_VAR, LB };

void
infix_to_rpn()
{
	char outstr[OUT_LEN] = { '\0' };
	char *out = outstr;
	int i = 0;
	int last_i = 0;
	enum staat_st last = START;
	
	while (1)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')' || str[i] == ' ' || str[i] == '\0')
		{
			if (last == READING_VAR)
			{
				last = VAR;
				*out = ' ';
				out++;
			}
			
			if (str[i] == '\0') break;
			
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				last_i = i;
				if (last == OP || last == START || last == LB) error("missing an operand", last_i);
				if (str[i] == '+' || str[i] == '-')
				{
					while (*spp != 0 && *stp != (int)'(')
					{
						*out = (char)pop();
						out++;
						*out = ' ';
						out++;
					}
					push((int)str[i]);
				}
				else
				{
					while (*spp != 0 && (*stp == (int)'*' || *stp == (int)'/'))
					{
						*out = (char)pop();
						out++;
						*out = ' ';
						out++;
					}
					push((int)str[i]);
				}
				
				last = OP;
			}
			else if (str[i] == ')')
			{
				if (last == OP) error("missing an operand", last_i);
				while (*spp != 0 && *stp != (int)'(')
				{
					*out = (char)pop();
					out++;
					*out = ' ';
					out++;
				}
				
				if (*stp == (int)'(')
					pop();
				else
					error("where's (", i);
			}
			else if (str[i] == '(')
			{
				if (last == VAR) error("missing an operand", last_i);
				last = LB;
				push((int)str[i]);
			}
		}
		else
		/* any char but +*-/() \0 */
		{
			if (last != READING_VAR) last_i = i;
			if (last == VAR) error("missing an operator", last_i);
			last = READING_VAR;
			*out = str[i];
			out++;
		}
		
		i++;
	}
	
	while (*spp != 0 && *stp != (int)'(')
	{
		*out = (char)pop();
		out++;
		*out = ' ';
		out++;
	}
	
	if (*stp == (int)'(') error("where's )", 0);
	
	if (str[last_i] == '+' || str[last_i] == '-' || str[last_i] == '*' || str[last_i] == '/')
		error("missing an operand", last_i);
	
	printf("%s\n", outstr);
}

void
rpn_compute()
{
	
}

void error(char *msg, int pos)
{
	fprintf(stderr, "%s\n%s\n%*c", msg, str, pos+1, '^');
	exit(-1);
}
