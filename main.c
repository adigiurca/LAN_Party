#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    char *buffer = NULL;
    buffer = (char *) malloc(100);
    NODE *head = NULL;
    NODE *team;
    team = (NODE *) malloc(sizeof(NODE));
    team->team_name = (char *) malloc(30);
    char *line;

    printf("Numar echipe:\n");
    int number_of_teams = atoi(fgets(buffer, sizeof(buffer), file));
    printf("%d\n", number_of_teams);

    //Citirea valorilor din fisier si adaugarea lor la inceputul listei
    for (int i = 0; i < number_of_teams; i++) {
        char team_name[50];
        memset(team_name, 0, 50);
        fgets(buffer, 100, file);
        line = strtok(buffer, " ");
        int number_of_players = atoi(line);
        printf("%d ", number_of_players);
        line = strtok(NULL, " ");
        while (line != NULL) {
            strcat(team_name, line);
            strcat(team_name, " ");
            line = strtok(NULL, " ");
        }
        team_name[strlen(team_name) - 2] = '\0';
        printf("%s", team_name);

        PLAYER players[number_of_players];

        for (int j = 0; j < number_of_players; j++) {
            fgets(buffer, 100, file);
            line = strtok(buffer, " ");
            players[j].firstName = (char*)malloc(strlen(line) + 5);
            strcpy(players[j].firstName, line);
            printf("%s ", players[j].firstName);
            line = strtok(NULL, " ");
            players[j].secondName = (char*)malloc(strlen(line) + 5);
            strcpy(players[j].secondName, line);
            printf("%s ", players[j].secondName);
            line = strtok(NULL, " ");
            players[j].points = atoi(line);
            printf("%d\n", players[j].points);
        }
        printf("\n");
        fgets(buffer, 5, file);
        addToBeginning(&head, team_name, number_of_players, players);
    }

    fclose(file);

    print(head);

    return 0;
}


