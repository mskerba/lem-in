#include "../includes/lem_in.h"

void output(Farm *farm) {
    Path **paths = farm->paths;
    int paths_count = farm->paths_count;
    int num_ants = farm->num_ants;

    printf("path_count: %d\n", paths_count);
    printf("num_ants: %d\n", num_ants);
    printf("room_count: %d\n", farm->room_count);

    // Main simulation loop
    while (num_ants > 0) {
        bool printed = false;

        printf("+++++++++++++++++++++++++++\n");
        for (int i = 0; i < paths_count; i++) {
            Path *path = paths[i];
            Ant **ants = path->ants;
            int ant_count = path->ant_count;
            Room **rooms = path->rooms;

            printf("Processing Path %d\n", path->id);
            for (int j = path->arrived_ants_count; j < ant_count; j++) {
                int next_room_id = ants[j]->room_id + 1;

                printf("Ant %d at %s moving to room %d\n", ants[j]->id, ants[j]->current_room->name, next_room_id);
                // if (next_room_id >= path->room_count) 
                //     continue;

                Room *next_room = rooms[next_room_id];

                // Check room status
                printf("Next Room Status: full=%d, is_end=%d\n", next_room->full, next_room->is_end);
                if (next_room->full) 
                    break;

                // Move the ant to the next room
                ants[j]->current_room->full = false; // Mark the current room as empty
                ants[j]->room_id = next_room_id;    // Update room_id
                ants[j]->current_room = next_room; // Move the ant to the next room
                // next_room->full = true;            // Mark the next room as full

                // Print movement
                if (printed) 
                    printf(" ");
                printf("L%d-%s", ants[j]->id, next_room->name);
                printed = true;

                // Check if the ant reached the end
                printf("--->%d",next_room->is_end);
                if (next_room->is_end) {
                    path->arrived_ants_count++;
                    num_ants--;
                }
            }
        }

        if (printed) 
            printf("\n");
    }
}
