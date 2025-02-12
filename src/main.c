#include "../includes/lem_in.h"

int main(int ac, char **av) {
    if (ac != 2)
        handle_error("Invalid number of arguments. Usage: ./lem-in <input_file>");

    int fd = open(av[1], O_RDONLY);
    if (fd <= 0)
        handle_error("Failed to open input file.");

    Farm *farm = parse_input(fd);
    close(fd);
    Room *start_room = NULL;
    Room *end_room = NULL;
    for (int i = 0; i < farm->room_count; i++) {
        Room *room = farm->rooms[i];
        if (room->is_start) start_room = room;
        if (room->is_end) end_room = room;
    }

    if (farm->num_ants <= 0) {
        handle_error("The number of ants is missing or invalid (must be a positive integer).");
    }
    if (!start_room) {
        handle_error("The ant farm does not have an start room defined (##start).");
    }
    if (!end_room) {
        handle_error("The ant farm does not have an end room defined (##end).");
    }


    find_disjoint_paths(farm, start_room, end_room);

    // dfs_paths(farm, start_room, end_room);


    // for (int i = 0; i < farm->paths_count; i++) {
    //     printf("\n%d paths->%d\n", farm->paths[i]->id,farm->paths[i]->steps);
    //     for (int j = 0; j < farm->paths[i]->conflict_count; j++) {
    //         printf(" %d", farm->paths[i]->conflict_with[j]);
    //     }
    //     printf("\n________\n");
    //     for (int j = 0; j < farm->paths[i]->length; j++) {
    //         printf(" %s", farm->paths[i]->rooms[j]->name);
    //     }
    //     printf("\n");
    // }


    // paths_conflict(farm);


    // for (int i = 0; i < farm->paths_count; ++i) {
    //     printf("\n\npath.id --> %d\n", farm->paths[i]->id);

    //     printf("rooms: ");
    //     for (int j = 0; j < farm->paths[i]->length; j++) {
    //         printf("%s ", farm->paths[i]->rooms[j]->name);
    //     }
    //     printf("\nconflicts: ");
    //     for (int j = 0; j < farm->paths[i]->conflict_count; j++) {
    //         printf("%d ", farm->paths[i]->conflict_with[j]);
    //     }
    //     printf("\n");
    // }

    //    [start]
    //    / |
    // [3] [1]--[5]
    //  |    |   |
    // [4]--[2] [6]
    //       | /
    //     [end]

    if (farm->paths_count <= 0) {
        handle_error("No possible path from start to end.");
    }

    algo(farm);

    int all_ants = 0;
    for (int i = 0; i < farm->paths_count; i++) {
        farm->paths[i]->ants = malloc(sizeof(Ant*) * farm->paths[i]->ant_count);
        if (!farm->paths[i]->ants) {
            perror("Memory allocation failed for ants array");
            exit(1);
        }
        for (int j = 0; j < farm->paths[i]->ant_count && all_ants < farm->num_ants; j++) {
            farm->paths[i]->ants[j] = malloc(sizeof(Ant));
            if (!farm->paths[i]->ants[j]) {
                perror("Memory allocation failed for an individual ant");
                exit(1);
            }
            farm->paths[i]->ants[j]->id = all_ants++;
            farm->paths[i]->ants[j]->current_room = start_room;
            farm->paths[i]->ants[j]->room_id = 0;
        }
    }

    output(farm);

    for (int i = 0; i < farm->paths_count; i++) {
        for (int j = 0; j < farm->paths[i]->ant_count; j++) {
            free(farm->paths[i]->ants[j]);
        }
        if (farm->paths[i]->conflict_with)
            free(farm->paths[i]->conflict_with);
        free(farm->paths[i]->ants);
        free(farm->paths[i]->rooms);
        free(farm->paths[i]);
    }

    free(farm->paths);


    // cleaning
    for (int i = 0; i < farm->room_count; i++) {
        if (farm->rooms[i]->included_count) free(farm->rooms[i]->included_in);
        free(farm->rooms[i]->name);
        free(farm->rooms[i]->connections);
        free(farm->rooms[i]);
    }
    if (farm->hash_map_count)
        free(farm->hash_map);
    free(farm->rooms);
    free(farm);
    return 0;
}
