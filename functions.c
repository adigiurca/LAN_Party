
#include "functions.h"

void add_at_beginning(NODE **head, PLAYER v) {
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    strcpy(newNode->player_info.firstName, v.firstName);
    strcpy(newNode->player_info.secondName, v.secondName);
    newNode->player_info.points = v.points;
    newNode->next = *head;
    *head = newNode;
}

void read_names_from_file_and_add_at_beginning(char *file, NODE head) {
    char first_name[50], last_name[50];
    FILE *fp = fopen(file, "r");

    if (fp == NULL) {
        printf("Fisierul nu a putut fi deschis.\n");
        exit(0);
    }

    while (fscanf(fp, "%s %s", head.player_info.firstName, head.player_info.secondName) != EOF) {
        add_at_beginning(&head, head.player_info);
    }

    fclose(fp);
}
