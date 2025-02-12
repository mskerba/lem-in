#include "../includes/lem_in.h"

void    ants_distribute(Farm *farm) {
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

void    best_paths_no_conflicts(Farm *farm) {
    Path    **paths = farm->paths;
    int     paths_count = farm->paths_count;
    Paths   **sauv_paths;
    int     score = INT_MAX;

    for (int i = 0; i < paths_count; i++) {
        Paths    **new_paths;
        int      new_path_count = 0;
        int      tmp_score = INT_MAX;

        
        for (int j = i + 1; j < paths_count; j++) {
            bool is_conflict = false
            for (int k = 0; k < paths->conflict_count; k++) {
                for (int l = 0; l < new_path_count; l++) {
                    if (new_paths[l]->id == paths[j]->conflict_with[k]) {
                        is_conflict = true;
                        break;
                    }
                }
            }
            if (!is_conflict) {
                new_paths = ft_realloc(new_path, new_path_count * sizeof(Path), (new_path_count + 1) * sizeof(Path));
                new_path_count++;
            }

        }

        if (score > tmp_score) {
            score = tmp_score;
            sauv_paths = new_paths;
        } 
    }

}

void algo(Farm *farm) {
    best_paths_no_conflicts(farm);
    // ants_distribute(farm);
}
