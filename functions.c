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
    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }

    newNODE->team_name = (char *) malloc(30);
    strcpy(newNODE->team_name, team_name);
    newNODE->player_number = number_of_players;

    newNODE->player_info = (PLAYER *) malloc(number_of_players * sizeof(PLAYER));

    for (int i = 0; i < number_of_players; i++) {
        newNODE->player_info[i].firstName = (char *) malloc(15);
        newNODE->player_info[i].secondName = (char *) malloc(15);
        newNODE->player_info[i] = player[i];
        //strcpy(newNODE->player_info[i].firstName, player->firstName);
        //strcpy(newNODE->player_info[i].secondName, player->secondName);
        //newNODE->player_info[i].points = player->points;
    }

    newNODE->next = *head;

    *head = newNODE;
}

void delete_node_by_value(NODE **head, int v) {
    if (*head == NULL) return;
    NODE *headcopy = *head;
    int score = 0;
    for (int i = 0; i < headcopy->player_number; i++) {
        score += headcopy->player_info[i].points;
    }
//    printf("%d %d\n", score, v);
    if (score == v) {
        *head = (*head)->next;
        free(headcopy);
        return;
    }

    NODE *prev = *head;
    while (headcopy != NULL) {
        score = 0;
        for (int i = 0; i < headcopy->player_number; i++) {
            score += headcopy->player_info[i].points;
        }
        if (score == v) {
            prev->next = headcopy->next;
            free(headcopy);
            return;
        } else {
            prev = headcopy;
            headcopy = headcopy->next;
        }
    }
}

void bubbleSort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}