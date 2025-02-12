#include "../includes/lem_in.h"

int compare_paths(const void *a, const void *b) {
    Path *pathA = *(Path **)a;
    Path *pathB = *(Path **)b;
    return pathA->length - pathB->length;
}

void sort_paths(Farm *farm) {
    qsort(farm->paths, farm->paths_count, sizeof(Path *), compare_paths);
}

