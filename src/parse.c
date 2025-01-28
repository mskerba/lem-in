#include "../includes/lem_in.h"

// Error handling function
void handle_error(const char *message) {
    write(2, "ERROR: ", 7);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}

// Parse the number of ants
int parse_number_of_ants(char *line) {
    for (int i = 0; line[i] && line[i] != '\n'; i++) {
        if (!isdigit(line[i])) {
            handle_error("Invalid number of ants.");
        }
    }
    return atoi(line);
}

int parse_room_coordinate(char *coor) {
    for (int i = 0; coor[i] && coor[i] != '\n'; i++) {

        if (!i && coor[i] == '-') continue;

        if (!isdigit(coor[i])) {
            handle_error("Invalid room coordinate.");
        }
    }
    return atoi(coor);
}

// Parse a room definition
Room *parse_room(char *line, int *is_start, int *is_end, int id) {
    Room *room = (Room *)malloc(sizeof(Room));
    if (!room)
        handle_error("Memory allocation failed for room.");
    
    char *name = ft_strtok(line, " ");
    char *x = ft_strtok(NULL, " ");
    char *y = ft_strtok(NULL, " ");
    char *rest = ft_strtok(NULL, " ");
    
    if (!name || !x || !y || rest)
        handle_error("Invalid room format.");

    if (name[0] == 'L') {
        handle_error("Invalid room name.");
    }

    room->name = ft_strdup(name);
    room->id = id;
    room->x = parse_room_coordinate(x);
    room->y = parse_room_coordinate(y);
    room->is_start = *is_start;
    room->is_end = *is_end;
    room->connections = NULL;
    room->connection_count = 0;
    room->included_in = NULL;
    room->included_count = 0;

    *is_start = 0; // Reset after processing
    *is_end = 0;

    return room;
}

// Parse a link between two rooms
void parse_link(char *line, Farm *farm) {
    char *room1_name = ft_strtok(line, "-");
    char *room2_name = ft_strtok(NULL, "\n");



    if (!room1_name || !room2_name) {
        handle_error("Invalid link format.");
    }

    Room *room1 = NULL, *room2 = NULL;
    for (int i = 0; i < farm->room_count; i++) {
        if (ft_strcmp(farm->rooms[i]->name, room1_name) == 0){
            room1 = farm->rooms[i];
        }
        if (ft_strcmp(farm->rooms[i]->name, room2_name) == 0) {
            room2 = farm->rooms[i];
        }
    }

    if (!room1 || !room2)
        handle_error("Link refers to undefined room(s).");

    room1->connections = ft_realloc(room1->connections, sizeof(Room *) * room1->connection_count, sizeof(Room *) * (room1->connection_count + 1));
    room1->connections[room1->connection_count++] = room2;

    room2->connections = ft_realloc(room2->connections, sizeof(Room *) * room2->connection_count, sizeof(Room *) * (room2->connection_count + 1));
    room2->connections[room2->connection_count++] = room1;
}

Farm *parse_input(int fd) {
    Farm *farm = (Farm *)malloc(sizeof(Farm));
    if (!farm)
        handle_error("Memory allocation failed for farm.");
    
    farm->rooms = NULL;
    farm->room_count = 0;


    char *line = NULL;
    int is_start = 0, is_end = 0;

    // Parse number of ants
    line = ft_get_line(fd);
    if (!line)
        handle_error("Empty.");
    farm->num_ants = parse_number_of_ants(line);

    free(line);

    // Parse rooms and links
    while ((line = ft_get_line(fd))) {
        char    *tmp_line = line;
        line = ft_strtrim(line, " \t\n");
        free(tmp_line);
        if (line[0] == '#') {
            if (ft_strcmp(line, "##start") == 0) {
                is_start = 1;
            } else if (ft_strcmp(line, "##end") == 0) {
                is_end = 1;
            }
        }
        else if (ft_strchr(line, ' ')) { // Room
            farm->rooms = ft_realloc(farm->rooms, sizeof(Room *) * farm->room_count, sizeof(Room *) * (farm->room_count + 1));
            farm->rooms[farm->room_count] = parse_room(line, &is_start, &is_end, farm->room_count);
            farm->room_count++;
        }
        else if (ft_strchr(line, '-')) { // Link
            parse_link(line, farm);
        } else {
            handle_error("Invalid input format.");
        }
        free(line);
    }

    farm->paths = NULL;
    farm->paths_count = 0;


    return farm;
}