#include "../includes/lem_in.h"

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
    Room *start_room = NULL;
    Room *end_room = NULL;
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

        if (room->is_start) start_room = room;
        if (room->is_end) end_room = room;
    }

    printf("-------------------------------------------------\n\n");


    find_disjoint_paths(farm, start_room, end_room);








    for (int i = 0; i < farm->paths_count; i++) {
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
