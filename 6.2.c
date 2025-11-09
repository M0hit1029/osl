#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
        if (time[i] < min) { min = time[i]; pos = i; }
    return pos;
}

int findOptimal(int pages[], int frames[], int n, int nf, int index) {
    int pos = -1, farthest = index;
    for (int i = 0; i < nf; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (pos == -1) ? 0 : pos;
}

void simulateLRU(int pages[], int n, int nf) {
    int frames[10], time[10], count = 0, pf = 0, flag1, flag2, pos;
    for (int i = 0; i < nf; i++) frames[i] = -1;
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
    printf("LRU (Frames=%d): %d page faults\n", nf, pf);
}

void simulateOptimal(int pages[], int n, int nf) {
    int frames[10], pf = 0, flag, pos;
    for (int i = 0; i < nf; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        flag = 0;
        for (int j = 0; j < nf; j++)
            if (frames[j] == pages[i]) { flag = 1; break; }
        if (!flag) {
            int empty = -1;
            for (int j = 0; j < nf; j++)
                if (frames[j] == -1) { empty = j; break; }
            if (empty != -1) frames[empty] = pages[i];
            else {
                pos = findOptimal(pages, frames, n, nf, i + 1);
                frames[pos] = pages[i];
            }
            pf++;
        }
    }
    printf("Optimal (Frames=%d): %d page faults\n", nf, pf);
}

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 1, 2, 3, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    simulateLRU(pages, n, 3);
    simulateLRU(pages, n, 4);
    simulateOptimal(pages, n, 3);
    simulateOptimal(pages, n, 4);
    return 0;
}

