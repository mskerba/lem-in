#include "../includes/lem_in.h"


int main() {
    FILE *input = fopen("./maps/ant_farm.map", "r");
    if (!input)
        handle_error("Failed to open input file.");

    Farm *farm = parse_input(input);
    fclose(input);


   printf("Number of ants: %d\n", farm->num_ants);

    // Print all rooms and their details
    printf("Rooms:\n");
    for (int i = 0; i < farm->room_count; i++) {
        Room *room = farm->rooms[i];
        printf("    Room Name: %s\n", room->name);
        printf("    Room id: %d\n", room->id);
        printf("    Coordinates: (%d, %d)\n", room->x, room->y);
        printf("    Start Room: %s\n", room->is_start ? "Yes" : "No");
        printf("    End Room: %s\n", room->is_end ? "Yes" : "No");

        printf("    Connections: [");
        for (int j = 0; j < room->connection_count; j++) {
            printf("%s, ", room->connections[j]->name);
        }
        printf("]\n\n");
    }
    return 0;
}