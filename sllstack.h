struct node_st {struct node_st *prev; int val;};
extern struct node_st *sp;
void push(int);
int pop(void);
