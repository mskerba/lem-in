#include "../includes/lem_in.h"

void	print_ants(int id, char *room_name)
{
    write(1, "L", 1);
    ft_putnbr_fd(id + 1, 1);
    write(1, "-", 1);
    ft_putstr_fd(room_name, 1);
}

void    output(Farm *farm) {
    Path **paths = farm->paths;
    int paths_count = farm->paths_count;
    int num_ants = farm->num_ants;

    while (num_ants > 0) {
        bool printed = false;

        for (int i = 0; i < paths_count; i++) {
            Path *path = paths[i];
            Ant **ants = path->ants;
            int ant_count = path->ant_count;
            Room **rooms = path->rooms;
            for (int j = 0; j < ant_count; j++) {
                if (rooms[ants[j]->room_id]->is_end)
                    continue;
                
                int next_room_id = ants[j]->room_id + 1;

                Room *next_room = rooms[next_room_id];

                if (next_room->full && !next_room->is_end) 
                    break;

                ants[j]->current_room->full = false;
                ants[j]->room_id = next_room_id;
                ants[j]->current_room = next_room;
                next_room->full = true;

                if (printed) 
                    write(1, " ", 1);
                print_ants(ants[j]->id, next_room->name);
                printed = true;

                if (next_room->is_end) {
                    path->arrived_ants_count++;
                    num_ants--;
                }
            }
        }

        if (printed) 
            write(1, "\n", 1);
    }
}

