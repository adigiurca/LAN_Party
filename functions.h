#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} PLAYER;

typedef struct List_Node {
    PLAYER *player_info;
    char *team_name;
    int player_number;
    struct List_Node *next;
} NODE;

typedef struct Queue_Node {
    PLAYER* players;
    char* team_name;
    int player_number;
    struct Queue_Node* next;
} QUEUE_NODE;

typedef struct Queue {
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
}QUEUE;

void print(NODE *);

void add_to_beginning(NODE **, char *, int, PLAYER*);

void delete_node_by_value(NODE**, int);

void bubble_sort(int*, int);

QUEUE_NODE* create_node(PLAYER*, char*, int);

void enQueue(QUEUE*, PLAYER*, char*, int);

void print_queue(QUEUE*);

void free_queue(QUEUE*);
