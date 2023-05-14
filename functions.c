
#include "functions.h"

void print(NODE *head) {
    while (head != NULL) {
        printf("%s \t %s \t %d \n", head->player_info->firstName, head->player_info->secondName,
               head->player_info->points);
        head = head->next;
    }
}

void addToBeginning(NODE** head, NODE* team) {
    // Alocare memorie pentru noul nod
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (newNode == NULL) {
        printf("Eroare la alocarea memoriei!");
        return;
    }

    // Initializare date pentru noul nod
    newNode->player_number = team->player_number;
    strcpy(newNode->team_name, team->team_name);
    strcpy(newNode->player_info->firstName, team->player_info->firstName);
    strcpy(newNode->player_info->secondName, team->player_info->secondName);
    newNode->player_info->points = team->player_info->points;
    newNode->next = *head;

    // Actualizare pointer catre inceputul listei
    *head = newNode;
}

//void read_from_file_and_add_at_beginning(FILE* fp,NODE** head, NODE* team){
//    while (fscanf(fp, "r") == 1) {
//        addToBeginning(&head, team);
//    }
//
//    fclose(fp);
//
//}
