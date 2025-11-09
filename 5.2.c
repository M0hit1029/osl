#include <stdio.h>

int main() {
    int n, m, i, j, k, p;
    FILE *f = fopen("state.txt", "r");
    fscanf(f, "%d%d", &n, &m);
    int alloc[n][m], max[n][m], avail[m], need[n][m], f1[n], ans[n], ind = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            fscanf(f, "%d", &alloc[i][j]);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            fscanf(f, "%d", &max[i][j]);
    for (i = 0; i < m; i++)
        fscanf(f, "%d", &avail[i]);
    fclose(f);
    for (i = 0; i < n; i++) {
        f1[i] = 0;
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            if (!f1[i]) {
                int flag = 0;
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                if (!flag) {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    ans[ind++] = i;
                    f1[i] = 1;
                }
            }
    int safe = 1;
    for (i = 0; i < n; i++)
        if (!f1[i]) safe = 0;
    if (safe) {
        printf("System is in safe state\nSafe sequence: ");
        for (i = 0; i < n - 1; i++) printf("P%d -> ", ans[i]);
        printf("P%d\n", ans[n - 1]);
    } else printf("System is in unsafe state\n");

    printf("Enter process number and resource request:\n");
    int req[m];
    scanf("%d", &p);
    printf("Enter request for %d resources:\n", m);
    for (i = 0; i < m; i++) scanf("%d", &req[i]);
    int grant = 1;
    for (i = 0; i < m; i++)
        if (req[i] > need[p][i] || req[i] > avail[i]) grant = 0;
    if (!grant) printf("Request cannot be granted\n");
    else {
        for (i = 0; i < m; i++) {
            avail[i] -= req[i];
            alloc[p][i] += req[i];
            need[p][i] -= req[i];
        }
        for (i = 0; i < n; i++) f1[i] = 0;
        ind = 0;
        for (k = 0; k < n; k++)
            for (i = 0; i < n; i++)
                if (!f1[i]) {
                    int flag = 0;
                    for (j = 0; j < m; j++)
                        if (need[i][j] > avail[j]) {
                            flag = 1;
                            break;
                        }
                    if (!flag) {
                        for (j = 0; j < m; j++)
                            avail[j] += alloc[i][j];
                        ans[ind++] = i;
                        f1[i] = 1;
                    }
                }
        safe = 1;
        for (i = 0; i < n; i++)
            if (!f1[i]) safe = 0;
        if (safe) {
            printf("Request can be granted\nSafe sequence: ");
            for (i = 0; i < n - 1; i++) printf("P%d -> ", ans[i]);
            printf("P%d\n", ans[n - 1]);
        } else printf("Request cannot be granted (unsafe state)\n");
    }
    return 0;
}

