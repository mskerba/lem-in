#include "../includes/lem_in.h"

void algo(Farm *farm) {
    int    ants = farm->num_ants;
    Path   **paths = farm->paths;
    int    paths_len = farm->paths_count;
    int    s = paths[0]->steps;
    int    ants_sum = 0;
    int    temp_ants_sum = 0;

    for (int i = 0; i < paths_len; i++) {
        if (ants < ants_sum + i + 1) {
            break;
        }
        if (paths[i]->steps == s) {
            if (i + 1 >= paths_len) {
                printf("????????????????????\n");
                int j = (i)?i:1;
                int tmp = (ants - ants_sum) / j;
                ants_sum  = tmp * j;
                s = s + tmp;
                break;
            }
            continue;
        }
        temp_ants_sum = (paths[i]->steps - s) * i;
        // if (paths[i]->steps == s) {
        //     ants_sum += 
        //     break;
        // }
        if (temp_ants_sum + ants_sum <= ants) {
            ants_sum += temp_ants_sum;
            s = paths[i]->steps;
            printf("******************%d  %d  %d\n", temp_ants_sum, s, ants_sum);
        } else {
            ants_sum  = (ants - ants_sum);
            s = s + ants_sum;
            break;
        }
    }
    printf("ants-->%d ____ s=%d _____ ants_sum= %d _____  \n", ants, s, ants_sum);
    temp_ants_sum = 0;
    for (int i = 0; i < paths_len && temp_ants_sum < ants_sum; i++) {
        paths[i]->ant_count = s - paths[i]->steps;
        printf("----->>>>> %d +++ %d", s, paths[i]->steps);
        temp_ants_sum = paths[i]->ant_count;
    }
    for (int i = 0; i < paths_len && temp_ants_sum < ants; i++) {
        paths[i]->ant_count += 1;
        temp_ants_sum++;
    }
}
