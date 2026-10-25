#include <stdio.h>
#include <string.h>

int wt[100], pf[100];
int table[101][1001];

void showTable(int rows, int W) {
    int r, c;
    printf("\n   cap |");
    for (c = 0; c <= W; c++) printf("%3d", c);
    printf("\n  -----");
    for (c = 0; c <= W; c++) printf("---");
    printf("\n");
    for (r = 0; r <= rows; r++) {
        printf("   dp%d |", r);
        for (c = 0; c <= W; c++) printf("%3d", table[r][c]);
        printf("\n");
    }
}

int solveCase(int n, int W) {
    int i, c;
    for (c = 0; c <= W; c++) table[0][c] = 0;

    for (i = 1; i <= n; i++) {
        for (c = 0; c <= W; c++) {
            if (wt[i - 1] <= c) {
                int with    = pf[i - 1] + table[i - 1][c - wt[i - 1]];
                int without = table[i - 1][c];
                table[i][c] = (with > without) ? with : without;
            } else {
                table[i][c] = table[i - 1][c];
            }
        }
        printf("\n  Item %d done:", i);
        showTable(i, W);
    }
    return table[n][W];
}

int main() {
    int n, W, i, caseNo = 0;
    char buf[200];

    FILE *in  = fopen("input.txt", "r");
    FILE *out = fopen("result.txt", "w");

    if (in == NULL || out == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    while (fgets(buf, sizeof(buf), in)) {
        if (strncmp(buf, "#Test", 5) != 0) continue;

        caseNo++;
        fgets(buf, sizeof(buf), in);
        sscanf(buf, "%d %d", &n, &W);

        for (i = 0; i < n; i++) {
            fgets(buf, sizeof(buf), in);
            sscanf(buf, "%d %d", &wt[i], &pf[i]);
        }

        printf("\nCase %d : n=%d W=%d\n", caseNo, n, W);
        int best = solveCase(n, W);
        printf("\n  Best value = %d\n", best);

        fprintf(out, "#Test case input (%d %d) test result: %d\n", n, W, best);
    }

    fclose(in);
    fclose(out);
    printf("\nDone. Check result.txt\n");
    return 0;
}