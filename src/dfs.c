#include "../includes/lem_in.h"

Path* create_path1(Farm *farm, Room** rooms, int length) {
    static int new_path_id = 0;
    Path* path = (Path*)malloc(sizeof(Path));
    path->id = new_path_id++;
    path->rooms = (Room**)malloc(sizeof(Room*) * length);
    ft_memcpy(path->rooms, rooms, sizeof(Room*) * length);
    path->length = length;
    path->steps = length;
    path->ant_count = 0;
    path->arrived_ants_count= 0;
    path->conflict_with = NULL;
    path->conflict_count = 0;
    farm->hash_map = ft_realloc(farm->hash_map, farm->hash_map_count * sizeof(int), (farm->hash_map_count + 1) *sizeof(int));
    farm->hash_map[path->id] = -1; 
    farm->hash_map_count++;
    return path;
}



void add_room_to_path(Path *path, Room *room) {
    path->rooms = ft_realloc(path->rooms, path->length* sizeof(Room *), (path->length + 1) * sizeof(Room *));
    path->rooms[path->length] = room;
    path->length++;
}

void    fill_included_in(Path *path) {
    for (int i = 0; i < path->length; ++i) {
        Room    *room = path->rooms[i];

        room->included_in = ft_realloc(room->included_in, room->included_count * sizeof(int), (room->included_count + 1) * sizeof(int));
        room->included_in[room->included_count++] = path->id;

    }
}


void dfs(Room *current, Room *start, Room *end, Path *path, Farm *farm) {
    printf("dfs: %s | steps : %d\n", current->name,  path->length);
    if (current == end) {
        printf("end\n");
        farm->paths = ft_realloc(farm->paths, farm->paths_count * sizeof(Path *), (farm->paths_count + 1) * sizeof(Path *));
        farm->paths[farm->paths_count] = path;
        farm->hash_map[path->id] = farm->paths_count;
        farm->paths_count++;
        fill_included_in(path);
        return ;
    }
    if (current == start && path->length > 1) {
        printf("loop\n");
        free(path->rooms);
        free(path);
        return ;
    }

    for (int i = 0; i < current->connection_count; i++) {
        Room *next_room = current->connections[i];
        bool cont = false;
        for (int j = 0 ; j < path->length; j++) {
            if (path->rooms[j]->name == next_room->name) {
                cont = true;
                break;
            }
        }
        if (cont) continue;
        Path *new_path = create_path1(farm, path->rooms, path->length);
        add_room_to_path(new_path, next_room);
        dfs(next_room, start, end, new_path, farm);
    }
    if (path && path->rooms[path->length - 1]->name != end->name) {
        free(path->rooms);
        free(path);
    }
}

void dfs_paths(Farm *farm, Room* start, Room* end) {
    Path* path = create_path1(farm, &start, 1);
    dfs(start, start, end, path, farm);
}

