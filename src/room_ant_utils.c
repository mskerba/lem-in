#include "../includes/lem_in.h"

ant* create_ant(int id, Room* start_room) {
    ant* new_ant = (ant*)malloc(sizeof(ant));
    new_ant->id = id;
    new_ant->current_room = start_room;
    return new_ant;
}

void free_room(Room* r) {
    if (r) {
        free(r->name);
        // free(r->edges);
        // free(r->included_in);
        free(r);
    }
}