#include "../includes/lem_in.h"

void    ants_distribute(Farm *farm, Path   **paths, int    paths_len) {
    int    ants = farm->num_ants;
    int    s = paths[0]->steps;
    int    ants_sum = 0;
    int    temp_ants_sum = 0;

    for (int i = 0; i < paths_len; i++) {
        if (ants < ants_sum ) {
            break;
        }
        if (paths[i]->steps == s) {
            if (i + 1 >= paths_len) {
                int j = i+ 1;
                int tmp = (ants - ants_sum) / j;
                ants_sum  += tmp * j;
                s = paths[i]->steps + tmp;
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
        int sub = (ants - ants_sum);
        int tmp = sub / j;
        ants_sum  += tmp * j;
        s = paths[paths_len - 1]->steps + tmp;
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

int score_calculate(Farm *farm, Path   **paths, int    paths_len) {
    int    ants = farm->num_ants;
    int    s = paths[0]->steps;
    int    ants_sum = 0;
    int    temp_ants_sum = 0;

    for (int i = 0; i < paths_len; i++) {
        if (ants < ants_sum ) {
            break;
        }
        if (paths[i]->steps == s) {
            if (i + 1 >= paths_len) {
                int j = i+ 1;
                int tmp = (ants - ants_sum) / j;
                ants_sum  += tmp * j;
                s = paths[i]->steps + tmp;
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
        int sub = (ants - ants_sum);
        int tmp = sub / j;
        ants_sum  += tmp * j;
        s = paths[paths_len - 1]->steps + tmp;
    }
    if (ants -ants_sum > 0) s++;
    return s;
}

void algo(Farm *farm) {
    int score_path = score_calculate(farm, farm->paths, farm->paths_count);
    int score_best_path = score_calculate(farm, farm->best_paths, farm->best_paths_count);
    if (score_path < score_best_path) {
        ants_distribute(farm, farm->paths, farm->paths_count);
        for (int i = 0; i < farm->best_paths_count; i++) {
            for (int j = 0; j < farm->best_paths[i]->ant_count; j++) {
                free(farm->best_paths[i]->ants[j]);
            }
            if (farm->best_paths[i]->conflict_with)
                free(farm->best_paths[i]->conflict_with);
            free(farm->best_paths[i]->rooms);
            free(farm->best_paths[i]);
        }

        free(farm->best_paths);
    }
    else {
        ants_distribute(farm, farm->best_paths, farm->best_paths_count);
        for (int i = 0; i < farm->paths_count; i++) {
            for (int j = 0; j < farm->paths[i]->ant_count; j++) {
                free(farm->paths[i]->ants[j]);
            }
            if (farm->paths[i]->conflict_with)
                free(farm->paths[i]->conflict_with);
            free(farm->paths[i]->rooms);
            free(farm->paths[i]);
        }
        free(farm->paths);
        farm->paths = farm->best_paths;
        farm->paths_count = farm->best_paths_count;
    }
}