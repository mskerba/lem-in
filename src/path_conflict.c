#include "../includes/lem_in.h"


void    mark_paths_as_conflict(Farm *farm, int path_index, int conflict_with_path_id) {
    Path    *path = farm->paths[path_index];

    if (!path->conflict_with) {
        path->conflict_with = malloc(farm->paths_count * sizeof(int) * 10000);
    }
    path->conflict_with[path->conflict_count] = conflict_with_path_id;
    path->conflict_count++;
}


void    paths_conflict(Farm *farm) {
    for (int i = 0; i < farm->room_count; i++) {
        Room    *room = farm->rooms[i];


        if (room->is_start || room->is_end) continue;

        for (int j = 0; j < room->included_count; j++) {
            int current_path_id = room->included_in[j];
            int current_path_index = farm->hash_map[current_path_id];

            if (current_path_index == -1) continue;

            for (int k = j; k < room->included_count; k++) {
                int path_id = room->included_in[k];
                int path_index = farm->hash_map[path_id];

                if (path_index == -1 || path_id == current_path_id) continue;

                mark_paths_as_conflict(farm, path_index, current_path_id);
                mark_paths_as_conflict(farm, current_path_index, path_id);
            }
        }
    }
}