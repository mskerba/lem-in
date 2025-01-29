#include "../includes/lem_in.h"

Path* create_path(Room** rooms, int length) {
    Path* path = (Path*)malloc(sizeof(Path));

    path->rooms = (Room**)malloc(sizeof(Room*) * length);
    ft_memcpy(path->rooms, rooms, sizeof(Room*) * length);
    path->length = length;
    path->steps = length;
    free(rooms);
    return path;
}


int is_room_included(Room* room) {
    return room->included_count > 0;
}


void mark_path_as_included(Path *path) {
    for (int i = 0; i < path->length; i++) {
        Room* room = path->rooms[i];
        if (room->is_start || room->is_end) continue;
        room->included_in = ft_realloc(room->included_in, sizeof(Path*) * room->included_count, sizeof(Path*) * (room->included_count + 1));
        room->included_in[room->included_count++] = path;
    }
}


Path* bfs(Farm* farm, Room* start, Room* end) {
    Room* queue[farm->room_count];
    int front = 0, rear = 0;

    Room* parent[farm->room_count];
    ft_memset(parent, 0, sizeof(parent));

    // Mark visited rooms
    int visited[farm->room_count];
    ft_memset(visited, 0, sizeof(visited));

    queue[rear++] = start;
    visited[start->id] = 1;

    while (front < rear) {
        Room* current = queue[front++];
        if (current == end) {
            // Path found; reconstruct it
            int path_length = 0;
            Room* path_rooms[farm->room_count];

            for (Room* r = end; r != NULL; r = parent[r->id]) {
                path_rooms[path_length++] = r;
            }

            // Reverse the path
            Room** final_path = malloc(sizeof(Room*) * path_length);
            for (int i = 0; i < path_length; i++) {
                final_path[i] = path_rooms[path_length - i - 1];
            }

            return create_path(final_path, path_length);
        }

        for (int i = 0; i < current->connection_count; i++) {
            Room* neighbor = current->connections[i];
            if (!visited[neighbor->id] && !is_room_included(neighbor)) {
                queue[rear++] = neighbor;
                visited[neighbor->id] = 1;
                parent[neighbor->id] = current;
            }
        }
    }

    return NULL;
}

void find_disjoint_paths(Farm* farm, Room* start, Room* end) {
    while (1) {
        Path* path = bfs(farm, start, end);
        if (!path) {
            break; // No more paths
        }

        // Mark path as included and add it to the farm
        mark_path_as_included(path);
        farm->paths = ft_realloc(farm->paths, sizeof(Path*) * farm->paths_count, sizeof(Path*) * (farm->paths_count + 1));
        farm->paths[farm->paths_count++] = path;

        // Print the path
        printf("Path %d: ", farm->paths_count);
        for (int i = 0; i < path->length; i++) {
            printf("%s ", path->rooms[i]->name);
        }
        printf("\n");
    }
}
