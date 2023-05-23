#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} PLAYER;

typedef struct Team {
    PLAYER *player_info;
    char *team_name;
    float score;
    int player_number;
}TEAM;

typedef struct List_Node {
    PLAYER *player_info;
    char *team_name;
    float score;
    int player_number;
    struct List_Node *next;
} NODE;

typedef struct Queue_Node {
    PLAYER *players;
    char *team_name;
    float score;
    int player_number;
    struct Queue_Node *next;
} QUEUE_NODE;

typedef struct Queue {
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
} QUEUE;

typedef struct Stack_Node {
    PLAYER *player_info;
    char *team_name;
    float score;
    int player_number;
    struct Stack_Node *next;
} STACK_NODE;

typedef struct Stack {
    STACK_NODE *top;
} STACK;

void print(NODE *);

void add_to_beginning(NODE **, char *, int, PLAYER *, float);

void delete_node_by_value(NODE **, float);

void bubble_sort(float *, int);

TEAM *deQueue(QUEUE *);

void freeStack(STACK *);

void add_nodes_to_queue(QUEUE *, NODE *);

void play_2v2_matches(QUEUE *, STACK *, STACK *);

void printQueue(QUEUE*);

void printStack(STACK*);

int isTeamInStack(STACK*, TEAM*);
