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
    newNode->players = (PLAYER *) malloc(player_number * sizeof(PLAYER));
    newNode->players = players;
    newNode->team_name = strdup(team_name);
    newNode->player_number = player_number;
    newNode->next = NULL;

    return newNode;
}

int isEmpty(QUEUE *q) {
    return (q->front == NULL);
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
TEAM *deQueue(QUEUE *queue) {
    NODE *aux = (NODE *) malloc(sizeof(NODE));
    TEAM *d = (TEAM *) malloc(sizeof(TEAM));
    aux->team_name = (char *) malloc(30);
    d->team_name = (char *) malloc(30);
    aux->player_info = (PLAYER *) malloc(sizeof(PLAYER));
    d->player_info = (PLAYER *) malloc(sizeof(PLAYER));\
    if (isEmpty(queue)) return 0;
    aux = queue->front;
    strcpy(d->team_name, aux->team_name);
    d->player_info = aux->player_info;
    d->player_number = aux->player_number;
    d->score = aux->score;
    queue->front = (queue->front)->next;
    free(aux);
    free(d);
    return d;
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
STACK_NODE *createStackNode(NODE *team) {
    STACK_NODE *newNode = (STACK_NODE *) malloc(sizeof(STACK_NODE));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei!");
        return NULL;
    }
    newNode->team_name = (char *) malloc(50);
    newNode->player_info = (PLAYER *) malloc(sizeof(PLAYER));
    strcpy(newNode->team_name, team->team_name);
    newNode->score = team->score;
    newNode->player_number = team->player_number;
    newNode->player_info = team->player_info;
    newNode->next = NULL;

    return newNode;
}

// Functie pentru adaugarea unui nod nou la stiva
void push(STACK *stack, NODE *team) {
    STACK_NODE *newNode = createStackNode(team);
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

void play_2v2_matches(QUEUE *queue, STACK *winner_stack, STACK *loser_stack) {
    while (isEmpty(queue) != 1) {
        TEAM *first_team = deQueue(queue);
        TEAM *second_team = deQueue(queue);
        if (first_team->score == second_team->score) {
            push(winner_stack, &first_team);
            push(loser_stack, &second_team);
            first_team->score++;
            free(first_team);
            free(second_team);
        };
        if (first_team->score > second_team->score) {
            push(winner_stack, &first_team);
            first_team->score++;
            push(loser_stack, &second_team);
            free(first_team);
            free(second_team);
        } else {
            push(winner_stack, &second_team);
            second_team->score++;
            push(loser_stack, &second_team);
            free(first_team);
            free(second_team);
        }
    }
}