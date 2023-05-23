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


void add_to_beginning(NODE **head, char *team_name, int number_of_players, PLAYER *player, float score) {
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


void delete_node_by_value(NODE **head, float points) {

    if (*head == NULL) return;

    if ((*head)->score == points) {
        NODE *headcopy = *head;
        *head = (*head)->next;
        free(headcopy);
        return;
    }

    NODE *prev = *head;
    NODE *headcopy = (*head)->next;
    while (headcopy != NULL) {
        if (headcopy->score == points) {
            prev->next = headcopy->next;
            NODE *temp = headcopy;
            headcopy = headcopy->next;
            free(temp);
        } else {
            prev = headcopy;
            headcopy = headcopy->next;
        }
    }
}

void bubble_sort(float arr[], int size) {
    int i, j;
    float temp;
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

void printStack(STACK *stack) {

    NODE *current = stack->top;
    while (current != NULL) {
        printf("%s\n", current->team_name);
        current = current->next;
    }
    printf("\n");
}


int isEmpty(QUEUE *q) {
    return (q->front == NULL);
}

int isTeamInStack(STACK *stack, TEAM *team) {
    NODE *current = stack->top;
    while (current != NULL) {
        if (strcmp(current->team_name, team->team_name) == 0) {
            return 1;  // Team found in the queue
        }
        current = current->next;
    }
    return 0;  // Team not found in the queue
}


void enQueue(QUEUE *q, NODE *team) {
    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }
    newNODE->team_name = (char *) malloc(70);
    strcpy(newNODE->team_name, team->team_name);
    newNODE->player_number = team->player_number;
    newNODE->score = team->score;
    newNODE->player_info = (PLAYER *) malloc(team->player_number * sizeof(PLAYER));
    for (int i = 0; i < team->player_number; i++) {
        newNODE->player_info[i].firstName = (char *) malloc(15);
        newNODE->player_info[i].secondName = (char *) malloc(15);
        newNODE->player_info[i] = team->player_info[i];
    }
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
//    NODE *currentNODE = head;

    while (head != NULL) {
        enQueue(matchQueue, head);
        head = head->next;
    }
}

// Functie pentru extragerea unui nod din coada
TEAM *deQueue(QUEUE *queue) {
    if (isEmpty(queue))
        return NULL;

    NODE *aux = queue->front;
    TEAM *d = (TEAM *) malloc(sizeof(TEAM));
    if (d == NULL) {
        printf("Eroare la alocarea memoriei!");
        return NULL;
    }

    d->team_name = (char *) malloc(70);
    strcpy(d->team_name, aux->team_name);
    d->player_number = aux->player_number;
    d->score = aux->score;

    d->player_info = (PLAYER *) malloc(d->player_number * sizeof(PLAYER));
    for (int i = 0; i < d->player_number; i++) {
        d->player_info[i].firstName = (char *) malloc(15);
        d->player_info[i].secondName = (char *) malloc(15);
        d->player_info[i] = aux->player_info[i];
    }

    queue->front = aux->next;
    if (queue->front == NULL)
        queue->rear = NULL;

    free(aux);
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
        printf("Echipa: %s\n", currentNODE->team_name);
        printf("Numarul de jucatori: %d\n", currentNODE->player_number);
        printf("Punctajul echipei: %f\n", currentNODE->score);
        printf("\n");
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
    newNODE->team_name = (char *) malloc(70);
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
        NODE *first_team = deQueue(queue);
        NODE *second_team = deQueue(queue);
        if (first_team->score == second_team->score) {
            first_team->score++;
            push(winner_stack, first_team);
            push(loser_stack, second_team);
        };
        if (first_team->score > second_team->score) {
            first_team->score++;
            push(winner_stack, first_team);
            push(loser_stack, second_team);
            if (first_team->score < second_team->score) {
                second_team->score++;
                push(winner_stack, second_team);
                push(loser_stack, first_team);
            }
        }
    }
}