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

QUEUE_NODE *createNODE(PLAYER *players, char *team_name, int player_number) {
    QUEUE_NODE *newNODE = (QUEUE_NODE *) malloc(sizeof(QUEUE_NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return NULL;
    }
    newNODE->players = (PLAYER *) malloc(player_number * sizeof(PLAYER));
    newNODE->players = players;
    newNODE->team_name = strdup(team_name);
    newNODE->player_number = player_number;
    newNODE->next = NULL;

    return newNODE;
}

int isEmpty(QUEUE *q) {
    return (q->front == NULL);
}

void enQueue(QUEUE *q, char* team_name, PLAYER *players, int player_number) {
    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    newNODE->team_name = (char *) malloc(30);
    newNODE->player_info = (PLAYER *) malloc(sizeof(PLAYER));
    newNODE->player_info->firstName = (char *) malloc(15);
    newNODE->player_info->secondName = (char *) malloc(15);
    newNODE->player_info = players;
    newNODE->team_name = team_name;
    newNODE->player_number = player_number;
    newNODE->next = NULL;
// nodurile noi se adauga la finalul cozii
    if (q->rear == NULL) q->rear = newNODE;
// daca nu exista niciun nod in coada
    else {
        (q->rear)->next = newNODE;
        (q->rear) = newNODE;
    }
// daca exita un singur element in coada
    if (q->front == NULL) q->front = q->rear;
}

// Functie pentru adaugarea unui nod nou la coada
void add_nodes_to_queue(QUEUE *matchQueue, NODE *head) {
    NODE *currentNODE = head;

    while (currentNODE != NULL) {
        enQueue(matchQueue, currentNODE->team_name, currentNODE->player_info, currentNODE->player_number);
        currentNODE = currentNODE->next;
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

    QUEUE_NODE *currentNODE = queue->front;
    while (currentNODE != NULL) {
        printf("Echipa: %s, Numarul de jucatori: %d\n", currentNODE->team_name, currentNODE->player_number);
        currentNODE = currentNODE->next;
    }
}

// Functie pentru crearea unui nod nou pentru stiva
STACK_NODE *createStackNODE(NODE *team) {
    STACK_NODE *newNODE = (STACK_NODE *) malloc(sizeof(STACK_NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return NULL;
    }
    newNODE->team_name = (char *) malloc(50);
    newNODE->player_info = (PLAYER *) malloc(sizeof(PLAYER));
    strcpy(newNODE->team_name, team->team_name);
    newNODE->score = team->score;
    newNODE->player_number = team->player_number;
    newNODE->player_info = team->player_info;
    newNODE->next = NULL;

    return newNODE;
}

// Functie pentru adaugarea unui nod nou la stiva
void push(STACK *stack, NODE *team) {
    STACK_NODE *newNODE = createStackNODE(team);
    if (newNODE == NULL) {
        return;
    }

    newNODE->next = stack->top;
    stack->top = newNODE;
}

// Functie pentru extragerea unui nod din stiva
char *pop(STACK *stack) {
    if (stack->top == NULL) {
        return NULL; // Stiva este goala
    }

    STACK_NODE *topNODE = stack->top;
    stack->top = stack->top->next;

    char *team_name = topNODE->team_name;
    free(topNODE);

    return team_name;
}

// Functie pentru eliberarea memoriei ocupate de stiva
void freeStack(STACK *stack) {
    STACK_NODE *currentNODE = stack->top;
    while (currentNODE != NULL) {
        STACK_NODE *nextNODE = currentNODE->next;
        free(currentNODE->team_name);
        free(currentNODE);
        currentNODE = nextNODE;
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