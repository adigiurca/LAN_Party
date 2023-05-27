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

void print_top8(NODE *head) {
    while (head != NULL) {
        printf("%s\n", head->team_name);
        head = head->next;
    }
}

void trim_leading_whitespace(char *str) {
    int i = 0;
    while (str[i] != '\0' && isspace((unsigned char) str[i])) {
        i++;
    }
    memmove(str, str + i, strlen(str) - i + 1);
}

// Trim trailing whitespace from a string
void trim_trailing_whitespace(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && isspace((unsigned char) str[i])) {
        str[i] = '\0';
        i--;
    }
}

void add_to_beginning(NODE **head, char *team_name, int number_of_players, PLAYER *player, float score) {
    // Alocare memorie pentru noul nod
    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }

    newNODE->team_name = (char *) malloc(50);
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
            return;
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

int isEmpty(QUEUE *q) {
    return (q->front == NULL);
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

// Functie pentru adaugarea unui nod nou la stiva
void push(STACK *stack, NODE *team) {
    if (team == NULL) {
        return;
    }

    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    if (newNODE == NULL) {
        printf("Error allocating memory!");
        return;
    }

    newNODE->team_name = strdup(team->team_name);
    newNODE->player_number = team->player_number;
    newNODE->score = team->score;
    newNODE->player_info = malloc(team->player_number * sizeof(PLAYER));
    for (int i = 0; i < team->player_number; i++) {
        newNODE->player_info[i].firstName = strdup(team->player_info[i].firstName);
        newNODE->player_info[i].secondName = strdup(team->player_info[i].secondName);
    }

    newNODE->next = stack->top;
    stack->top = newNODE;
}


// Functie pentru extragerea unui nod din stiva
NODE *pop(STACK *stack) {
    if (stack->top == NULL) {
        return NULL; // Stiva este goala
    }

    NODE *topNODE = stack->top;
    stack->top = stack->top->next;

    NODE *node;
    node = (NODE *) malloc(sizeof(NODE));
    if (node == NULL) {
        printf("Error allocating memory!");
        return NULL;
    }
    node->team_name = (char *) malloc(70);
    node->team_name = strdup(topNODE->team_name);
    node->player_number = topNODE->player_number;
    node->score = topNODE->score;
    node->player_info = malloc(topNODE->player_number * sizeof(PLAYER));

    free(topNODE->team_name);
    free(topNODE);

    return node;
}

// Functie pentru eliberarea memoriei ocupate de stiva
void freeStack(STACK *stack) {
    NODE *currentNODE = stack->top;
    while (currentNODE != NULL) {
        NODE *nextNODE = currentNODE->next;
        free(currentNODE->team_name);
        free(currentNODE);
        currentNODE = nextNODE;
    }

    stack->top = NULL;
}

BSTNode *newNode(NODE *team) {
    BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
    node->team_name = (char *) malloc(70);
    strcpy(node->team_name, team->team_name);
    node->score = team->score;
    node->left = node->right = NULL;
    return node;
}

BSTNode *insertBSTNode(BSTNode *node, NODE *key) {

    if (node == NULL) return newNode(key);

    if (key->score > node->score || (key->score == node->score && strcmp(key->team_name, node->team_name) > 0))
        node->left = insertBSTNode(node->left, key);
    else
        node->right = insertBSTNode(node->right, key);
    return node;
}

void printBSTToFile(BSTNode *root, FILE *output_file) {
    if (root == NULL) {
        return;
    }

    printBSTToFile(root->left, output_file);

    root->team_name[strlen(root->team_name) - 1] = '\0';
    fprintf(output_file, "%s", root->team_name);
    for (int i = 0; i < 34 - strlen(root->team_name); i++)
        fprintf(output_file, " ");
    fprintf(output_file, "-  ");
    fprintf(output_file, "%.2f\n", root->score);

    printBSTToFile(root->right, output_file);
}

int getSize(STACK *stack) {
    int size = 0;
    NODE *current = stack->top;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void add_top8_to_beginning(NODE **head, NODE *team) {
    // Alocare memorie pentru noul nod
    NODE *newNODE = (NODE *) malloc(sizeof(NODE));
    if (newNODE == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }

    newNODE->team_name = (char *) malloc(50);
    strcpy(newNODE->team_name, team->team_name);
    newNODE->player_number = team->player_number;
    newNODE->score = team->score;

    newNODE->player_info = (PLAYER *) malloc(team->player_number * sizeof(PLAYER));

    for (int i = 0; i < team->player_number; i++) {
        newNODE->player_info[i].firstName = (char *) malloc(15);
        newNODE->player_info[i].secondName = (char *) malloc(15);
        newNODE->player_info[i] = team->player_info[i];
        //strcpy(newNODE->player_info[i].firstName, player->firstName);
        //strcpy(newNODE->player_info[i].secondName, player->secondName);
        //newNODE->player_info[i].points = player->points;
    }

    newNODE->next = *head;

    *head = newNODE;
}

void play_2v2_matches(QUEUE *queue, STACK *winner_stack, STACK *loser_stack, FILE *output_file, NODE *head, int round,
                      NODE **top8) {
    if (isEmpty(queue) || queue->front == queue->rear)
        return;

    fprintf(output_file, "\n");
    fprintf(output_file, "--- ROUND NO:%d\n", round);

    while (!isEmpty(queue)) {
        NODE *first_team = deQueue(queue);
        NODE *second_team = deQueue(queue);

        if (first_team->score > second_team->score) {
            first_team->score = first_team->score + 1;
            push(winner_stack, first_team);
            push(loser_stack, second_team);
        } else if (first_team->score <= second_team->score) {
            second_team->score = second_team->score + 1;
            push(winner_stack, second_team);
            push(loser_stack, first_team);
        }

        char *spacing1;
        char *spacing2;
        spacing1 = (char *) malloc(70);
        spacing2 = (char *) malloc(70);
        strcpy(spacing1, first_team->team_name);
        strcpy(spacing2, second_team->team_name);

        spacing1[strlen(spacing1) - 1] = '\0';
        spacing2[strlen(spacing2) - 1] = '\0';

        if (spacing1[strlen(spacing1) - 1] == '\n') {
            spacing1[strlen(spacing1) - 1] = '\0';
        }
        trim_leading_whitespace(spacing1);
        trim_trailing_whitespace(spacing1);

        if (spacing2[strlen(spacing2) - 1] == '\n') {
            spacing2[strlen(spacing2) - 1] = '\0';
        }
        trim_leading_whitespace(spacing2);
        trim_trailing_whitespace(spacing2);

        fprintf(output_file, "%s", spacing1);

        for (int i = 0; i < 33 - strlen(spacing1); i++)
            fprintf(output_file, " ");

        fprintf(output_file, "-");

        for (int i = 0; i < 33 - strlen(spacing2); i++)
            fprintf(output_file, " ");
        fprintf(output_file, "%s\n", spacing2);
    }

    if (getSize(winner_stack) == 8) {
        NODE *temporary = winner_stack->top;
        while (temporary != NULL) {
            add_top8_to_beginning(top8, temporary);
            temporary = temporary->next;
        }
    }

    fprintf(output_file, "\n");

    fprintf(output_file, "WINNERS OF ROUND NO:%d\n", round);

    while (!isEmpty(winner_stack)) {
        enQueue(queue, winner_stack->top);
        NODE *temp = pop(winner_stack);
        temp->team_name[strlen(temp->team_name) - 1] = '\0';
        fprintf(output_file, "%s", temp->team_name);

        for (int i = 0; i < 34 - strlen(temp->team_name); i++)
            fprintf(output_file, " ");

        fprintf(output_file, "-  ");

        fprintf(output_file, "%.2f\n", temp->score);
    }

    freeStack(loser_stack);
    play_2v2_matches(queue, winner_stack, loser_stack, output_file, head, ++round, top8);
}

AVLNode *new_AVL_Node(NODE *node) {
    AVLNode *AVL_node = (AVLNode *) malloc(sizeof(AVLNode));
    AVL_node->team_name = (char *) malloc(70);
    strcpy(AVL_node->team_name, node->team_name);
    AVL_node->score = node->score;
    AVL_node->height = 1;
    AVL_node->left = NULL;
    AVL_node->right = NULL;
    return AVL_node;
}

int get_height(AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int get_balance(AVLNode *node) {
    if (node == NULL)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

AVLNode *RightRotation(AVLNode *z) {
    AVLNode *y = z->left;
    AVLNode *T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = max(get_height(z->left), get_height(z->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

AVLNode *LeftRotation(AVLNode *z) {
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = max(get_height(z->left), get_height(z->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

AVLNode *insertAVLNode(AVLNode *root, NODE *team) {
    if (root == NULL)
        return new_AVL_Node(team);

    if (team->score > root->score || (team->score == root->score && strcmp(team->team_name, root->team_name) > 0))
        root->left = insertAVLNode(root->left, team);
    else
        root->right = insertAVLNode(root->right, team);

    root->height = max(get_height(root->left), get_height(root->right)) + 1;

    int balance = get_balance(root);

    if (balance > 1 && team->score < root->left->score)
        return RightRotation(root);

    if (balance < -1 && team->score > root->right->score)
        return LeftRotation(root);

    if (balance > 1 && team->score > root->left->score) {
        root->right = RightRotation(root->right);
        return LeftRotation(root);
    }

    if (balance < -1 && team->score < root->right->score) {
        root->left = LeftRotation(root->left);
        return RightRotation(root);
    }

    return root;
}

void printAVLAtLevel2(AVLNode *root, int level, FILE *output_file) {
    if (root == NULL)
        return;

    if (level == 2) {
        fprintf(output_file, "%s\n", root->team_name);
        return;
    }

    printAVLAtLevel2(root->left, level + 1, output_file);
    printAVLAtLevel2(root->right, level + 1, output_file);
}