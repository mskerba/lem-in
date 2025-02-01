#include "../includes/lem_in.h"

void algo(Farm *farm) {
    int    ants = farm->num_ants;
    Path   **paths = farm->paths;
    int    paths_len = farm->paths_count;
    int    s = paths[0]->steps;
    int    ants_sum = 0;
    int    temp_ants_sum = 0;

    for (int i = 0; i < paths_len; i++) {
        // printf("--| s in loop : %d \n", s);
        if (ants < ants_sum ) {
            // if (ants <= ants_sum +i)
            // printf("\x1b[32m"     "This text is RED!"     "\x1b[0m" "\n");
            break;
        }
        if (paths[i]->steps == s) {
            if (i + 1 >= paths_len) {
                // printf("????????????????????\n");
                int j = (i)?i:1;
                int tmp = (ants - ants_sum) / j;
                ants_sum  = tmp * j;
                s = s + tmp;
                break;
            }
            continue;
        }
        // int k = (i)?i:1;
        temp_ants_sum = (paths[i]->steps - s) * (i * 1);
        // if (paths[i]->steps == s) {
        //     ants_sum += 
        //     break;
        // }
        if (temp_ants_sum + ants_sum <= ants) {
            ants_sum += temp_ants_sum;
            s = paths[i]->steps;
            // printf("******************%d  %d  %d\n", temp_ants_sum, s, ants_sum);
        } else {
            int j = (i)?i:1;
            int tmp = (ants - ants_sum) / (j);
            // printf("\x1b[33m"     "tmp= %d tempsum= %d j= %d antssum = %d"     "\x1b[0m" "\n", tmp, temp_ants_sum , j, ants_sum);
            
            ants_sum  += tmp * j;
            // int k = ((tmp * j)!= (ants - ants_sum))?1:0;
            
            s = s + tmp ;
            break;
        }
    }
    if (ants - ants_sum >= paths_len) {
        int j = paths_len;
        int tmp = (ants - ants_sum) / j;
        ants_sum  = tmp * j;
        s = s + tmp;
    }
    // printf("ants-->%d ____ s=%d _____ ants_sum= %d _____  \n", ants, s, ants_sum);
    temp_ants_sum = 0;
    for (int i = 0; i < paths_len && temp_ants_sum < ants_sum; i++) {
        paths[i]->ant_count = s - paths[i]->steps;
        temp_ants_sum += s - paths[i]->steps;
        // printf("\x1b[33m""----->>>>> %d +++ %d   tmp= %d  i= %d antssum = %d " "\x1b[0m""\n", s, paths[i]->steps, temp_ants_sum, i, ants_sum);
    }
    for (int i = 0; i < paths_len && temp_ants_sum < ants; i++) {
        paths[i]->ant_count += 1;
        temp_ants_sum++;
    }
}
