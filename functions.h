#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct BST_Node {
    char *team_name;
    float score;
    struct BST_Node *left;
    struct BST_Node *right;
} BSTNode;

typedef struct AVLNode {
    char *team_name;
    float score;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

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
} TEAM;

typedef struct List_Node {
    PLAYER *player_info;
    char *team_name;
    float score;
    int player_number;
    struct List_Node *next;
} NODE;

typedef struct Stack {
    NODE *top;
} STACK;

typedef struct Queue {
    NODE *front;
    NODE *rear;
} QUEUE;

void print(NODE *);

void print_top8(NODE *);

void add_to_beginning(NODE **, char *, int, PLAYER *, float);

void add_top8_to_beginning(NODE **, NODE *);

void delete_node_by_value(NODE **, float);

void bubble_sort(float *, int);

TEAM *deQueue(QUEUE *);

void freeStack(STACK *);

void add_nodes_to_queue(QUEUE *, NODE *);

void play_2v2_matches(QUEUE *, STACK *, STACK *, FILE *, NODE *, int, NODE **);

void trim_leading_whitespace(char *);

void trim_trailing_whitespace(char *);

BSTNode *insert_BST_node(BSTNode *, NODE *);

void print_BST_to_file(BSTNode *, FILE *);

AVLNode *insert_AVL_node(AVLNode *, NODE *);

void print_AVL_at_level_2(AVLNode *, int, FILE *);

void level_order_traversal(AVLNode *, FILE *);