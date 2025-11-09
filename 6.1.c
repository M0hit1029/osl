#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
        if (time[i] < min) { min = time[i]; pos = i; }
    return pos;
}

int main() {
    int pages[30], frames[7], time[7], n = 20, nf, count = 0, flag1, flag2, pf, pos;
    for (int i = 0; i < n; i++) pages[i] = rand() % 10;
    printf("Page Reference String:\n");
    for (int i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\nEnter number of frames (1-7): ");
    scanf("%d", &nf);

    for (int i = 0; i < nf; i++) frames[i] = -1;
    pf = 0;
    for (int i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for (int j = 0; j < nf; j++)
            if (frames[j] == pages[i]) { flag1 = flag2 = 1; count++; time[j] = count; break; }
        if (!flag1) {
            for (int j = 0; j < nf; j++)
                if (frames[j] == -1) {
                    pf++; frames[j] = pages[i]; count++; time[j] = count; flag2 = 1; break;
                }
        }
        if (!flag2) {
            pos = findLRU(time, nf);
            pf++; frames[pos] = pages[i]; count++; time[pos] = count;
        }
    }
    printf("LRU Page Faults: %d\n", pf);

    for (int i = 0; i < nf; i++) frames[i] = -1;
    pf = 0; pos = 0;
    for (int i = 0; i < n; i++) {
        flag1 = 0;
        for (int j = 0; j < nf; j++)
            if (frames[j] == pages[i]) { flag1 = 1; break; }
        if (!flag1) {
            frames[pos] = pages[i];
            pos = (pos + 1) % nf;
            pf++;
        }
    }
    printf("FIFO Page Faults: %d\n", pf);
    return 0;
}

