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

    // printf("Number of ants: %d\n", farm->num_ants);

    // printf("Rooms:\n");
    for (int i = 0; i < farm->room_count; i++) {
        Room *room = farm->rooms[i];
        //     printf("    Room Name: %s\n", room->name);
        //     printf("    Room ID: %d\n", room->id);
        //     printf("    Coordinates: (%d, %d)\n", room->x, room->y);
        //     printf("    Start Room: %s\n", room->is_start ? "Yes" : "No");
        //     printf("    End Room: %s\n", room->is_end ? "Yes" : "No");

        //     printf("    Connections: [");
        //     for (int j = 0; j < room->connection_count; j++) {
        //         printf("%s", room->connections[j]->name);
        //         if (j < room->connection_count - 1)
        //             printf(", ");
        //     }
        //     printf("]\n\n");

        if (room->is_start) start_room = room;
        if (room->is_end) end_room = room;
    }



    find_disjoint_paths(farm, start_room, end_room);

    // printf("\x1b[32m""start algo-------------------------------------------------""\x1b[0m" "\n\n");

    algo(farm);
    // printf("    paths count :%d\n", farm->paths_count);
    // for (int i = 0; i < farm->paths_count; i++) {
    //     printf("    path_length: %d + path_ants: %d ==> %d \n", farm->paths[i]->length, farm->paths[i]->ant_count, farm->paths[i]->length + farm->paths[i]->ant_count);
    // }
    // printf("\x1b[31m""\nend algo-------------------------------------------------""\x1b[0m" "\n\n");

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

    write(1, "##movements\n", 12);


    // printf("\x1b[32m""start output-------------------------------------------------""\x1b[0m" "\n\n");

    output(farm);
    // printf("\x1b[31m""\nend output-------------------------------------------------""\x1b[0m" "\n\n");

    for (int i = 0; i < farm->paths_count; i++) {
        for (int j = 0; j < farm->paths[i]->ant_count; j++) {
            free(farm->paths[i]->ants[j]);
        }
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
    free(farm->rooms);
    free(farm);
    return 0;
}
