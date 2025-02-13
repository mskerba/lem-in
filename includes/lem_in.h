#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct Path Path;

typedef struct Room {
    char        *name;
    int         id;
    int         x, y;
    int         is_start;
    int         is_end;
    struct Room **connections;
    int         connection_count;
    int        *included_in;
    int         included_count;
    bool        full;
    bool        visited;
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
    int     length;
    int     *conflict_with;
    int     conflict_count;
} Path;

typedef struct Farm {
    int     num_ants;
    Room    **rooms;
    int     room_count;
    Path    **paths;
    int     paths_count;
    Path    **best_paths;
    int     best_paths_count;
    int     score;
} Farm;

//room_ant_utils
Ant* create_ant(int id, Room* start_room);
void free_room(Room* r);

// parse
Farm *parse_input(int fd);
void handle_error(const char *message);
void find_disjoint_paths(Farm* farm, Room* start, Room* end);

//output
void output(Farm *farm);

void algo(Farm *farm);

#endif