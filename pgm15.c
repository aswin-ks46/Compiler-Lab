#include <stdio.h>

int n, m, nfa[10][10], dst[1024], dt[1024][10], nd = 1;
char sym[10];

int main() {
    int i, j, k, t, from, to, nt, s, nf, fin = 0, mask;
    char c;

    printf("Number of states and symbols: ");
    scanf("%d %d", &n, &m);

    printf("Symbols: ");
    for (k = 0; k < m; k++)
        scanf(" %c", &sym[k]);

    printf("Number of transitions, then 'from symbol to' for each:\n");
    scanf("%d", &nt);

    while (nt--) {
        scanf("%d %c %d", &from, &c, &to);

        for (k = 0; k < m; k++) {
            if (sym[k] == c)
                nfa[from][k] |= 1 << to;
        }
    }

    printf("Start state, number of final states, final states: ");
    scanf("%d %d", &s, &nf);

    while (nf--) {
        scanf("%d", &t);
        fin |= 1 << t;
    }

    /* DFA state = set of NFA states */
    dst[0] = 1 << s;

    for (i = 0; i < nd; i++) {
        for (k = 0; k < m; k++) {

            /* Find move(dst[i], symbol k) */
            mask = 0;

            for (j = 0; j < n; j++) {
                if ((dst[i] >> j) & 1)
                    mask |= nfa[j][k];
            }

            /* Check whether this DFA state already exists */
            for (t = 0; t < nd && dst[t] != mask; t++)
                ;

            /* Add new DFA state */
            if (t == nd && mask)
                dst[nd++] = mask;

            dt[i][k] = mask ? t : -1;
        }
    }

    printf("\nDFA:\nState NFA set ");

    for (k = 0; k < m; k++)
        printf("%c ", sym[k]);

    for (i = 0; i < nd; i++) {
        printf("\n%s%c {",
               (dst[i] & fin) ? "*" : " ",
               'A' + i);

        for (j = 0; j < n; j++) {
            if ((dst[i] >> j) & 1)
                printf("q%d ", j);
        }

        printf("}\t");

        for (k = 0; k < m; k++) {
            if (dt[i][k] < 0)
                printf("- ");
            else
                printf("%c ", 'A' + dt[i][k]);
        }
    }

    printf("\n(* = final state, A = start state, - = no move)\n");

    return 0;
}

