#include "functions.h"

void print(NODE *head) {
    while (head != NULL) {
        printf("%d ", head->player_number);
        printf("%s", head->team_name);
        printf("%d\n", head->score);
        for (int i = 0; i < head->player_number; i++) {
            printf("%s  %s  %d \n", head->player_info[i].firstName, head->player_info[i].secondName,
                   head->player_info[i].points);
        }
        head = head->next;
        printf("\n");
    }
}


void add_to_beginning(NODE **head, char *team_name, int number_of_players, PLAYER *player, int score) {
    // Alocare memorie pentru noul nod
    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }

    newNODE->team_name = (char *) malloc(30);
    strcpy(newNODE->team_name, team_name);
    newNODE->player_number = number_of_players;
    newNODE->score = score;

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

QUEUE_NODE *createNode(PLAYER *players, char *team_name, int player_number) {
    QUEUE_NODE *newNode = (QUEUE_NODE *) malloc(sizeof(QUEUE_NODE));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei!");
        return NULL;
    }

    newNode->players = players;
    newNode->team_name = strdup(team_name);
    newNode->player_number = player_number;
    newNode->next = NULL;

    return newNode;
}

void enQueue(QUEUE *queue, PLAYER *players, char *team_name, int player_number) {
    QUEUE_NODE *newNode = createNode(players, team_name, player_number);
    if (newNode == NULL) {
        return;
    }

    if (queue->rear == NULL) {
        // Daca coada este goala
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Daca coada nu este goala
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Functie pentru adaugarea unui nod nou la coada
void add_nodes_to_queue(QUEUE *matchQueue, NODE *head) {
    NODE *currentNode = head;

    while (currentNode != NULL) {
        enQueue(matchQueue, currentNode->player_info, currentNode->team_name, currentNode->player_number);
        currentNode = currentNode->next;
    }
}

// Functie pentru extragerea unui nod din coada
QUEUE_NODE *deQueue(QUEUE *queue) {
    if (queue->front == NULL) {
        return NULL; // Coada este goala
    }

    QUEUE_NODE *frontNode = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        // Daca coada a devenit goala, actualizam si rear
        queue->rear = NULL;
    }

    return frontNode;
}

// Functie pentru afisarea continutului cozii
void printQueue(QUEUE *queue) {
    if (queue->front == NULL) {
        printf("Coada este goala.\n");
        return;
    }

    QUEUE_NODE *currentNode = queue->front;
    while (currentNode != NULL) {
        printf("Echipa: %s, Numarul de jucatori: %d\n", currentNode->team_name, currentNode->player_number);
        currentNode = currentNode->next;
    }
}

// Functie pentru crearea unui nod nou pentru stiva
STACK_NODE *createStackNode(char *team_name) {
    STACK_NODE *newNode = (STACK_NODE *) malloc(sizeof(STACK_NODE));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei!");
        return NULL;
    }

    newNode->team_name = strdup(team_name);
    newNode->next = NULL;

    return newNode;
}

// Functie pentru adaugarea unui nod nou la stiva
void push(STACK *stack, char *team_name) {
    STACK_NODE *newNode = createStackNode(team_name);
    if (newNode == NULL) {
        return;
    }

    newNode->next = stack->top;
    stack->top = newNode;
}

// Functie pentru extragerea unui nod din stiva
char *pop(STACK *stack) {
    if (stack->top == NULL) {
        return NULL; // Stiva este goala
    }

    STACK_NODE *topNode = stack->top;
    stack->top = stack->top->next;

    char *team_name = topNode->team_name;
    free(topNode);

    return team_name;
}

// Functie pentru eliberarea memoriei ocupate de stiva
void freeStack(STACK *stack) {
    STACK_NODE *currentNode = stack->top;
    while (currentNode != NULL) {
        STACK_NODE *nextNode = currentNode->next;
        free(currentNode->team_name);
        free(currentNode);
        currentNode = nextNode;
    }

    stack->top = NULL;
}

// Functie pentru adaugarea echipei in coada de meciuri
void addMatchToQueue(QUEUE *matchQueue, STACK *winnersStack, char *team_name) {
    if (matchQueue->rear == NULL) {
        // Adaugam echipa in coada de meciuri
        enQueue(matchQueue, NULL, team_name, 0);
    } else {
        // Adaugam echipa in stiva de castigatori
        push(winnersStack, team_name);
    }
}

// Functie pentru efectuarea meciurilor
void playMatches(QUEUE *teamQueue, QUEUE *matchQueue, STACK *winnersStack, STACK *losersStack, int num_teams) {
    while (teamQueue->front != NULL) {
        // Extragem primele doua echipe din coada de echipe
        QUEUE_NODE *team1 = deQueue(teamQueue);
        QUEUE_NODE *team2 = deQueue(teamQueue);

        // Adaugam meciul in coada de meciuri
        addMatchToQueue(matchQueue, winnersStack, team1->team_name);
        addMatchToQueue(matchQueue, winnersStack, team2->team_name);

        if (team1->score == team2->score) {
            push(losersStack, team2->team_name);
            team1->score++;
        } else {
            if (team1->score < team2->score) {
                team2->score++;
                push(losersStack, team1->team_name);
            } else {
                push(losersStack, team2->team_name);
            }
        }

        free(team1->team_name);
        free(team1);
        free(team2->team_name);
        free(team2);

        // Daca toate echipele au fost adaugate in coada de meciuri
        if (matchQueue->rear != NULL && matchQueue->rear->player_number == num_teams) {
            // Extragem echipele din stiva de castigatori si le adaugam in coada de echipe
            while (winnersStack->top != NULL) {
                char *team_name = pop(winnersStack);
                enQueue(teamQueue, NULL, team_name, 0);
            }

            // Eliberam stiva de invinsi
            freeStack(losersStack);

            // Golim coada de meciuri
            while (matchQueue->front != NULL) {
                QUEUE_NODE *matchNode = deQueue(matchQueue);
                free(matchNode->team_name);
                free(matchNode);
            }
        }
    }
}