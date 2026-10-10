#include <stdio.h>
#include <string.h>

#define MAX 100

int main()
{
    char stack[MAX], input[MAX];
    char table[10][10];
    char terminals[10];

    int n;
    int top = 0;
    int ip = 0;
    int row, col;
    int i, j;

    /* -------------------------------
       Input number of terminals
       ------------------------------- */
    printf("Enter the no. of terminals: ");
    scanf("%d", &n);

    printf("\nEnter the terminals: ");
    scanf("%s", terminals);

    /* -------------------------------
       Input precedence table
       ------------------------------- */
    printf("\nEnter the table values:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter the value for %c %c: ",
                   terminals[i], terminals[j]);

            scanf(" %c", &table[i][j]);
        }
    }

    /* -------------------------------
       Display precedence table
       ------------------------------- */
    printf("\nOPERATOR PRECEDENCE TABLE:\n\n");

    printf("\t");
    for (i = 0; i < n; i++)
        printf("%c\t", terminals[i]);

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%c\t", terminals[i]);

        for (j = 0; j < n; j++)
            printf("%c\t", table[i][j]);

        printf("\n");
    }

    /* -------------------------------
       Input string
       ------------------------------- */
    printf("\nEnter the input string: ");
    scanf("%s", input);

    strcat(input, "$");

    /* -------------------------------
       Initialize stack
       ------------------------------- */
    stack[0] = '$';
    stack[1] = '\0';

    printf("\n");
    printf("%-25s %-25s %-25s\n",
           "STACK", "INPUT STRING", "ACTION");

    printf("---------------------------------------------------------------\n");

    while (1)
    {
        /* Find top terminal in stack */
        int stackTerminal = -1;

        for (i = top; i >= 0; i--)
        {
            for (j = 0; j < n; j++)
            {
                if (stack[i] == terminals[j])
                {
                    stackTerminal = j;
                    break;
                }
            }

            if (stackTerminal != -1)
                break;
        }

        /* Find input terminal */
        col = -1;

        for (j = 0; j < n; j++)
        {
            if (input[ip] == terminals[j])
            {
                col = j;
                break;
            }
        }

        /* Invalid input symbol */
        if (col == -1)
        {
            printf("%-25s %-25s %-25s\n",
                   stack, input + ip, "ERROR");
            break;
        }

        /* -------------------------------
           Acceptance
           ------------------------------- */
        if (stack[top] == '$' && input[ip] == '$')
        {
            printf("%-25s %-25s %-25s\n",
                   stack, input + ip, "ACCEPT");

            printf("\nString is accepted.\n");
            break;
        }

        /* Invalid stack terminal */
        if (stackTerminal == -1)
        {
            printf("%-25s %-25s %-25s\n",
                   stack, input + ip, "ERROR");

            printf("\nString is not accepted.\n");
            break;
        }

        row = stackTerminal;

        /* -------------------------------
           SHIFT
           ------------------------------- */
        if (table[row][col] == '<' ||
            table[row][col] == '=')
        {
            char action[30];

            sprintf(action, "Shift %c", input[ip]);

            stack[++top] = input[ip];
            stack[top + 1] = '\0';

            printf("%-25s %-25s %-25s\n",
                   stack, input + ip, action);

            ip++;
        }

        /* -------------------------------
           REDUCE
           ------------------------------- */
        else if (table[row][col] == '>')
        {
            int handleStart;

            /*
             * Find the left boundary of the handle.
             */
            handleStart = top;

            while (handleStart > 0)
            {
                int currentIndex = -1;
                int previousIndex = -1;

                /* Find terminal at handleStart */
                for (j = 0; j < n; j++)
                {
                    if (stack[handleStart] == terminals[j])
                    {
                        currentIndex = j;
                        break;
                    }
                }

                /* Find previous terminal */
                int k;

                for (k = handleStart - 1; k >= 0; k--)
                {
                    for (j = 0; j < n; j++)
                    {
                        if (stack[k] == terminals[j])
                        {
                            previousIndex = j;
                            break;
                        }
                    }

                    if (previousIndex != -1)
                        break;
                }

                if (previousIndex == -1)
                    break;

                if (table[previousIndex][currentIndex] == '<')
                    break;

                handleStart = k;
            }

            /*
             * Replace the handle by 'E'.
             */
            top = handleStart;

            stack[top] = 'E';
            stack[top + 1] = '\0';

            printf("%-25s %-25s %-25s\n",
                   stack, input + ip, "Reduce");
        }

        /* -------------------------------
           ERROR
           ------------------------------- */
        else
        {
            printf("%-25s %-25s %-25s\n",
                   stack, input + ip, "ERROR");

            printf("\nString is not accepted.\n");
            break;
        }
    }

    return 0;
}
 
