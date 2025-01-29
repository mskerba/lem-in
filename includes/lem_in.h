#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
#include <stdbool.h>
#include "../libft/libft.h"

typedef struct path path;

typedef struct Room {
    char *name;
    int id;
    int x, y;
    int is_start;
    int is_end;
    struct Room **connections;
    int connection_count;
    path** included_in;
    int included_count;
    bool full ;
} Room;

typedef struct Ant {
    int     id;
    Room    *current_room;
    int     room_id;
} Ant;

typedef struct Path {
    int     id;
    int     steps;
    Ant     **ants;
    int     ant_count;
    int     arrived_ants_count;
    Room    **rooms;
    int     room_count;
    int     *conflict_with;
    int     conflict_count;
} Path;

typedef struct Farm {
    int     num_ants;
    Room    **rooms;
    int room_count;
    Path **path;
    int path_count;
} Farm;

//room_ant_utils
Ant* create_ant(int id, Room* start_room);
void free_room(Room* r);

// parse
Farm *parse_input(int fd);
void handle_error(const char *message);

void		fatal_error(char *str);

//output
void output(Farm *farm);

#endif