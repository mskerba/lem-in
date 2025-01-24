
#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>

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
} Room;

// void output(Farm* farm, int* path_id)

typedef struct ant {
    int id;
    Room* current_room;
} ant;

typedef struct Path {
    int id;
    int steps;
    Room** rooms;
    int room_count;
    int* conflict_with;
    int conflict_count;
} Path;

typedef struct Farm {
    int num_ants;
    Room **rooms;
    int room_count;
    Path **path;
    int path_count;
} Farm;

//room_ant_utils
ant* create_ant(int id, Room* start_room);
void free_room(Room* r);

// parse
Farm *parse_input(FILE *input);
void handle_error(const char *message);

void		fatal_error(char *str);
void		parser(char *fileName);

#endif