#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("C:\\Users\\agiur\\OneDrive\\Documents\\GitHub\\LAN_Party\\d.in", "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    struct Node *head = NULL;
    NODE *team;
    int player_number;
    char *team_name = (char *) malloc(25);
    char *player_firstname = (char *) malloc(10);
    char *player_lastname = (char *) malloc(10);
    int player_points;

    // Citirea valorilor din fisier si adaugarea lor la inceputul listei
    while (fscanf(file, "%d", &player_number) && fscanf(file, "%s", team_name) &&
           fscanf(file, "%s", player_firstname) && fscanf(file, "%s", player_lastname) &&
           fscanf(file, "%d", player_points) == 1) {
        addToBeginning(&head, team);
    }

    fclose(file);

    print(head);

    return 0;
}


