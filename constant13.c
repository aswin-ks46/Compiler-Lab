#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 50

struct expr
{
    char op[4];
    char op1[16];
    char op2[16];
    char res[16];
    int flag;
};

struct expr arr[MAX];
int n;

/* Check whether a string is an integer constant */
int is_const(const char *s)
{
    int i = 0;

    if (s[0] == '-' && s[1] != '\0')
        i = 1;

    if (s[i] == '\0')
        return 0;

    for (; s[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)s[i]))
            return 0;
    }

    return 1;
}

/* Input expressions */
void input()
{
    int i;

    printf("\nEnter the number of expressions : ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number (1 to %d allowed)\n", MAX);
        exit(1);
    }

    printf("\nEnter the input (op op1 op2 result)");
    printf("\nUse '.' as op2 for '=':\n");

    for (i = 0; i < n; i++)
    {
        scanf("%3s %15s %15s %15s",
              arr[i].op,
              arr[i].op1,
              arr[i].op2,
              arr[i].res);

        arr[i].flag = 0;
    }
}

/* Replace later uses of a constant */
void change(int p, const char *val)
{
    int i;

    for (i = p + 1; i < n; i++)
    {
        /* Replace first operand */
        if (strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, val);

        /* Replace second operand */
        if (strcmp(arr[i].op, "=") != 0 &&
            strcmp(arr[p].res, arr[i].op2) == 0)
        {
            strcpy(arr[i].op2, val);
        }

        /* Stop when the variable is redefined */
        if (strcmp(arr[p].res, arr[i].res) == 0)
            break;
    }
}

/* Perform constant folding */
void constant()
{
    int i, a, b, r, ok;
    char val[16];

    for (i = 0; i < n; i++)
    {
        char op = arr[i].op[0];
        ok = 0;

        /* Assignment */
        if (strcmp(arr[i].op, "=") == 0)
        {
            if (is_const(arr[i].op1))
            {
                r = atoi(arr[i].op1);
                ok = 1;
            }
        }

        /* Arithmetic operation */
        else if (strlen(arr[i].op) == 1 &&
                 is_const(arr[i].op1) &&
                 is_const(arr[i].op2))
        {
            a = atoi(arr[i].op1);
            b = atoi(arr[i].op2);

            switch (op)
            {
                case '+':
                    r = a + b;
                    ok = 1;
                    break;

                case '-':
                    r = a - b;
                    ok = 1;
                    break;

                case '*':
                    r = a * b;
                    ok = 1;
                    break;

                case '/':
                    if (b != 0)
                    {
                        r = a / b;
                        ok = 1;
                    }
                    break;

                default:
                    ok = 0;
            }
        }

        /* If expression can be evaluated */
        if (ok)
        {
            sprintf(val, "%d", r);

            arr[i].flag = 1;

            change(i, val);
        }
    }
}

/* Display optimized code */
void output()
{
    int i;

    printf("\nOptimized code is :\n");

    for (i = 0; i < n; i++)
    {
        if (!arr[i].flag)
        {
            printf("%s %s %s %s\n",
                   arr[i].op,
                   arr[i].op1,
                   arr[i].op2,
                   arr[i].res);
        }
    }
}

int main()
{
    input();
    constant();
    output();

    return 0;
}
