#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} PLAYER;

typedef struct Node {
    PLAYER *player_info;
    char *team_name;
    int player_number;
    struct Node *next;
} NODE;

void print(NODE *);

void addToBeginning(NODE **, char *, int, PLAYER*);

