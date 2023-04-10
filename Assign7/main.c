#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef char element;
typedef struct
{
	element data[MAX_SIZE];
	int top;
} StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_SIZE - 1));
}

void push(StackType* s, char ch)
{
	if (is_full(s))
	{
		fprintf(stderr, "Full Error\n");
		return;
	}
	else s->data[++(s->top)] = ch;
}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "Empty Error\n");
		return;
	}
	else return s->data[(s->top)--];
}

int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType* s;
	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
		{
			if (ch == 32)
				continue;
			else if(ch >= 48 && ch <= 57)
			{
				value = ch - '0';
				push(&s, value);
			}
			else
				return -1;
		}
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch)
			{
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

int main()
{
	char input[MAX_SIZE];
	int result, i = 0;
	char c;
	printf("Postfix Calc : ");
	while ((c = getchar()) != '\n' && i < sizeof(input) - 1)
		input[i++] = c;
	input[i] = '\0';
	result = eval(input);
	if (result == -1)
		printf("Error : Invalid character\n");
	else
		printf("Result = %d", result);
	return 0;
}
