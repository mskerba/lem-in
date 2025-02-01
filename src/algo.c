#include "../includes/lem_in.h"

void algo(Farm *farm) {
    int    ants = farm->num_ants;
    Path   **paths = farm->paths;
    int    paths_len = farm->paths_count;
    int    s = paths[0]->steps;
    int    ants_sum = 0;
    int    temp_ants_sum = 0;

    for (int i = 0; i < paths_len; i++) {
        if (ants < ants_sum ) {
            break;
        }
        if (paths[i]->steps == s) {
            if (i + 1 >= paths_len) {
                int j = (i)?i:1;
                int tmp = (ants - ants_sum) / j;
                ants_sum  = tmp * j;
                s = s + tmp;
                break;
            }
            continue;
        }
        temp_ants_sum = (paths[i]->steps - s) * (i);//i + 1
        if (temp_ants_sum + ants_sum <= ants) {
            ants_sum += temp_ants_sum;
            s = paths[i]->steps;
        } else {
            int j = (i)?i:1;
            int tmp = (ants - ants_sum) / (j);
            ants_sum  += tmp * j;
            
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
    temp_ants_sum = 0;
    for (int i = 0; i < paths_len && temp_ants_sum < ants_sum; i++) {
        paths[i]->ant_count = s - paths[i]->steps;
        temp_ants_sum += s - paths[i]->steps;
        
    }
    for (int i = 0; i < paths_len && temp_ants_sum < ants; i++) {
        paths[i]->ant_count += 1;
        temp_ants_sum++;
    }
}
