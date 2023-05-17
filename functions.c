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


void add_to_beginning(NODE **head, char *team_name, int number_of_players, PLAYER *player) {
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

void bubble_sort(int arr[], int size) {
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

//QUEUE_NODE* create_node(PLAYER* players, char* team_name, int player_number) {
//    QUEUE_NODE* newNode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
//    if (newNode == NULL) {
//        printf("Eroare la alocarea memoriei!");
//        return NULL;
//    }
//
//    newNode->players = players;
//    newNode->team_name = strdup(team_name);
//    newNode->player_number = player_number;
//    newNode->next = NULL;
//
//    return newNode;
//}
//
//void enQueue(QUEUE* queue, PLAYER* players, char* team_name, int player_number) {
//    QUEUE_NODE* newNode = create_node(players, team_name, player_number);
//    if (newNode == NULL) {
//        return;
//    }
//
//    if (queue->rear == NULL) {
//        queue->front = newNode;
//        queue->rear = newNode;
//    } else {
//        queue->rear->next = newNode;
//        queue->rear = newNode;
//    }
//}
//
//void print_queue(QUEUE* queue) {
//    if (queue->front == NULL) {
//        printf("Coada este goala.\n");
//        return;
//    }
//
//    QUEUE_NODE* currentNode = queue->front;
//    while (currentNode != NULL) {
//        printf("Echipa: %s, Numarul de jucatori: %d\n", currentNode->team_name, currentNode->player_number);
//        currentNode = currentNode->next;
//    }
//}
//
//void free_queue(QUEUE* queue) {
//    QUEUE_NODE* currentNode = queue->front;
//    while (currentNode != NULL) {
//        QUEUE_NODE* nextNode = currentNode->next;
//        free(currentNode->team_name);
//        free(currentNode);
//        currentNode = nextNode;
//    }
//
//    queue->front = NULL;
//    queue->rear = NULL;
//}