#include "../includes/lem_in.h"

#include <time.h>

void create_random_paths(Farm *farm, int num_paths, int max_path_length) {
    if (!farm || num_paths <= 0 || max_path_length <= 0)
        handle_error("Invalid arguments to create_random_paths.");

    srand(time(NULL)); // Seed the random number generator

    // Allocate memory for the paths
    farm->path = (Path **)malloc(sizeof(Path *) * num_paths);
    if (!farm->path)
        handle_error("Memory allocation failed for paths.");
    farm->path_count = num_paths;

    for (int i = 0; i < num_paths; i++) {
        Path *path = (Path *)malloc(sizeof(Path));
        if (!path)
            handle_error("Memory allocation failed for a path.");

        path->id = i + 1;
        path->steps = 0; // Will be updated
        path->ant_count = 3;
        path->arrived_ants_count = 0;
        path->conflict_with = NULL;
        path->conflict_count = 0;

        // Allocate memory for rooms in the path
        path->rooms = (Room **)malloc(sizeof(Room *) * max_path_length);
        if (!path->rooms)
            handle_error("Memory allocation failed for path rooms.");
        path->room_count = 0;

        // Select a random starting room (must be `is_start`)
        Room *current_room = NULL;
        for (int j = 0; j < farm->room_count; j++) {
            if (farm->rooms[j]->is_start) {
                current_room = farm->rooms[j];
                break;
            }
        }
        if (!current_room)
            handle_error("No start room found in the farm.");

        // Track visited rooms to prevent reusing them in the same path
        bool *visited = (bool *)calloc(farm->room_count, sizeof(bool));
        if (!visited)
            handle_error("Memory allocation failed for visited array.");

        // Build the path
        int step_count = 0;
        while (current_room && step_count < max_path_length) {
            // Add the current room to the path
            path->rooms[path->room_count++] = current_room;
            visited[current_room->id] = true;

            // If the current room is the end room, stop
            if (current_room->is_end)
                break;

            // Choose the next room randomly from its connections
            Room *next_room = NULL;
            int valid_connections = 0;
            for (int k = 0; k < current_room->connection_count; k++) {
                if (!visited[current_room->connections[k]->id]) {
                    valid_connections++;
                }
            }

            // If no valid connections are available, terminate the path
            if (valid_connections == 0)
                break;

            // Select a random unvisited connection
            do {
                int random_index = rand() % current_room->connection_count;
                next_room = current_room->connections[random_index];
            } while (visited[next_room->id]);

            current_room = next_room;
            step_count++;
        }

        // Update path steps
        path->steps = path->room_count - 1;

        // Add the path to the farm
        farm->path[i] = path;

        // Free the visited array
        free(visited);
    }
}

void add_ants_to_path(Path *path, Ant **all_ants, int num_ants_to_add, int k) {;

    // Allocate or reallocate memory for the ants array in the path
    path->ants = (Ant **)malloc( sizeof(Ant *) * (num_ants_to_add));
    if (!path->ants)
        handle_error("Memory allocation failed for ants in path.");
    printf("***%d***%d\n", num_ants_to_add, k);
    for (int i = 0; i < num_ants_to_add; i++) {
        path->ants[i] = all_ants[k];
    }
}


int main(int ac, char **av) {
    if (ac != 2)
        handle_error("Invalid number of arguments. Usage: ./lem-in <input_file>");

    int fd = open(av[1], O_RDONLY);
    if (fd <= 0)
        handle_error("Failed to open input file.");

    Farm *farm = parse_input(fd);
    close(fd);

    printf("Number of ants: %d\n", farm->num_ants);

    printf("Rooms:\n");
    for (int i = 0; i < farm->room_count; i++) {
        Room *room = farm->rooms[i];
        printf("    Room Name: %s\n", room->name);
        printf("    Room ID: %d\n", room->id);
        printf("    Coordinates: (%d, %d)\n", room->x, room->y);
        printf("    Start Room: %s\n", room->is_start ? "Yes" : "No");
        printf("    End Room: %s\n", room->is_end ? "Yes" : "No");

        printf("    Connections: [");
        for (int j = 0; j < room->connection_count; j++) {
            printf("%s", room->connections[j]->name);
            if (j < room->connection_count - 1)
                printf(", ");
        }
        printf("]\n\n");
    }

    create_random_paths(farm, 5, 10);

    // Print generated paths
    printf("Generated Paths:\n");
    for (int i = 0; i < farm->path_count; i++) {
        Path *path = farm->path[i];
        printf("Path %d (Steps: %d):\n", path->id, path->steps);
        for (int j = 0; j < path->room_count; j++) {
            printf("  %s", path->rooms[j]->name);
            if (j < path->room_count - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    Room *start_room = NULL;
    for (int i = 0; i < farm->room_count; i++) {
        if (farm->rooms[i]->is_start) {
            start_room = farm->rooms[i];
            break;
        }
    }
    if (!start_room)
        handle_error("Start room not found in the farm.");

    Ant **ants = (Ant **)malloc(sizeof(Ant *) * farm->num_ants);
    if (!ants)
        handle_error("Memory allocation failed for ants.");

    for (int i = 0; i < farm->num_ants; i++) {
        ants[i] = (Ant *)malloc(sizeof(Ant));
        if (!ants[i])
            handle_error("Memory allocation failed for an ant.");

        ants[i]->id = i + 1;
        ants[i]->current_room = start_room;
        ants[i]->room_id = 0;
    }

    Path **path = farm->path;
    int n = 0;
    for (int j = 0; j < farm->path_count; j++) {
        add_ants_to_path(path[j], ants, 3, n);
        n+=3;
    }

    printf("\n\n________________________________________________\n\n");
    printf("Ant movements:\n");
    output(farm);

    for (int i = 0; i < farm->room_count; i++) {
        free(farm->rooms[i]->name);
        free(farm->rooms[i]->connections);
        free(farm->rooms[i]);
    }
    free(farm->rooms);

    for (int i = 0; i < farm->path_count; i++) {
        free(farm->path[i]->ants);
        free(farm->path[i]->rooms);
        free(farm->path[i]->conflict_with);
        free(farm->path[i]);
    }
    free(farm->path);

    free(farm);
    return 0;
}
