#include <stdio.h>
#include <stdlib.h>

void distributeAnts(int paths[], int n, int ants, int result[]) {
    int antsInPath[n];
    for (int i = 0; i < n; i++) antsInPath[i] = 0; // change with bzzero

    for (int i = 0; i < ants; i++) {
        int chosenPath = 0;

        for (int j = 1; j < n; j++) {
            if ((paths[chosenPath] + antsInPath[chosenPath]) > (paths[j] + antsInPath[j])) {
                chosenPath = j;
            }
        }

        antsInPath[chosenPath]++;
    }

    for (int i = 0; i < n; i++) {
        result[i] = antsInPath[i];
    }
}

int main() {
    int paths[] = {1,2,2,4,5,10};
    int ants = 14;
    int n = sizeof(paths) / sizeof(paths[0]);
    int result[n];

    distributeAnts(paths, n, ants, result);

    printf("Ant distribution across paths: [");
    for (int i = 0; i < n; i++) {
        printf("%d", result[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    return 0;
}
