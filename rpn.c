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

enum tok { OP, VAR };
enum ops { ADD = '+', SUB = '-', MUL = '*', DIV = '/', LP = '(' };

void error(char *msg, int i)
{
	fprintf(stderr, "%s\n%s\n", msg, str);
	for (;i != 0; i--)
		fputc(' ', stderr);
	fputc('^', stderr);
	exit(-1);
}

void
infix_to_rpn()
{
	char outstr[OUT_LEN] = { '\0' };
	char *out = outstr;
	int reading_var = 0;
	int n_ops = 0;
	int n_vars = 0;
	int i = 0;
	enum tok last = OP;
	
	while (1)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')' || str[i] == ' ' || str[i] == '\0')
		{
			if (reading_var == 1)
			{
				reading_var = 0;
				last = VAR;
				n_vars++;
				*out = ' ';
				out++;
			}
			
			if (str[i] == '\0') break;
			
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				if (last == OP) error("missing an operand", i);
				if (str[i] == '+' || str[i] == '-')
				{
					while (*spp != 0 && *stp != LP)
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
					while (*spp != 0 && (*stp == MUL || *stp == DIV))
					{
						*out = (char)pop();
						out++;
						*out = ' ';
						out++;
					}
					push((int)str[i]);
				}
				
				last = OP;
				n_ops++;
			}
			else if (str[i] == ')')
			{
				while (*spp != 0 && *stp != LP)
				{
					*out = (char)pop();
					out++;
					*out = ' ';
					out++;
				}
				
				if (*stp == LP)
					pop();
				else
					error("where's (", i);
			}
			else if (str[i] == '(')
			{
				push(LP);
			}
		}
		else
		/* any char but +*-/() \0 */
		{
			if (last == VAR) error("missing an operator", i);
			reading_var = 1;
			*out = str[i];
			out++;
		}
		
		i++;
	}
	
	while (*spp != 0 && *stp != LP)
	{
		*out = (char)pop();
		out++;
		*out = ' ';
		out++;
	}
	
	if (*stp == LP) error("where's )", 0);
	
	if (n_ops < n_vars - 1)
	{
		error("too many vars", i);
	}
	else if (n_ops > n_vars - 1)
	{
		error("too many ops", i);
	}
	
	printf("%s\n", outstr);
}

void
rpn_compute()
{
	
}
