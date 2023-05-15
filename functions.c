
#include "functions.h"

void print(NODE *head) {
    while (head != NULL) {
        printf("%d ", head->player_number);
        printf("%s\n", head->team_name);
        for (int i = 0; i < head->player_number; i++) {
            printf("%s  %s  %d \n", head->player_info[i].firstName, head->player_info[i].secondName,
                   head->player_info[i].points);
        }
        head = head->next;
        printf("\n");
    }
}


void addToBeginning(NODE **head, char *team_name, int number_of_players, PLAYER *player) {
    // Alocare memorie pentru noul nod
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }

    newNode->team_name = (char *) malloc(30);
    strcpy(newNode->team_name, team_name);
    newNode->player_number = number_of_players;

    newNode->player_info = (PLAYER *) malloc(number_of_players * sizeof(PLAYER));

    for (int i = 0; i < number_of_players; i++) {
        newNode->player_info[i].firstName = (char *) malloc(15);
        newNode->player_info[i].secondName = (char *) malloc(15);
        newNode->player_info[i] = player[i];
        //strcpy(newNode->player_info[i].firstName, player->firstName);
        //strcpy(newNode->player_info[i].secondName, player->secondName);
        //newNode->player_info[i].points = player->points;
    }

    newNode->next = *head;

    *head = newNode;
}

