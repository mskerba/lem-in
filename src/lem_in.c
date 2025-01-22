#include "../includes/lem_in.h"


int main() {
    FILE *input = fopen("./src/ant_farm.map", "r");
    if (!input)
        handle_error("Failed to open input file.");

    Farm *farm = parse_input(input);
    fclose(input);

    printf("Parsed %d ants and %d rooms successfully.\n", farm->num_ants, farm->room_count);
    // Further processing...

    return 0;
}