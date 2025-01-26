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

    write(1, "Ant distribution across paths: [", 32);
    for (int i = 0; i < n; i++) {
        ft_putnbr_fd(result[i]);
        if (i < n - 1) write(1, ", ", 2);
    }
    write(1, "]\n", 2);

    return 0;
}
