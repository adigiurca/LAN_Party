
#include "functions.h"

void print(NODE *head) {
    while (head != NULL) {
        printf("%s \t %s \t %d \n", head->player_info->firstName, head->player_info->secondName,
               head->player_info->points);
        head = head->next;
    }
}

void add_at_beginning_team_info(NODE **head, PLAYER v) {
    NODE *newNode = (NODE *) malloc(sizeof(NODE));

    /*
     *fscanf pentru numarul de jucatori si numele echipei
     * malloc la players (PLAYER *player_info = malloc (nr_de_jucatori * sizeof (PLAYER))
     * dupa se face un for de la 0 la nr de jucatori;
     * se da maloc la nume si prenume
     * fscanf pentru nume prenume si puncte
     * ----------
     * */

    newNode->next = *head;
    *head = newNode;
}

void read_names_from_file_and_add_at_beginning(char *file, NODE *head) {
    char first_name[50], last_name[50];
    FILE *fp = fopen("C:\\Users\\agiur\\OneDrive\\Documents\\GitHub\\LAN_Party\\d.in", "r+");

    if (fp == NULL) {
        printf("Fisierul nu a putut fi deschis.\n");
        exit(1);
    }
    int teams_number = 0;
    char test[20];
    int test1;
    fscanf(fp, "%d", &teams_number);
    printf("%d\n",teams_number);
//    for (int i = 0; i < teams_number; i++) {
//
//    }


//    while (fscanf(fp, "%s %s", head->player_info.firstName, head->player_info.secondName) != EOF) {
//        add_at_beginning(&head, head->player_info);
//    }

    fclose(fp);
}

//void addNode(NODE **head_ref, PLAYER info) {
//    NODE *new_node = (struct Node *) malloc(sizeof(struct Node));
//
//    new_node->player_info.firstName = info.firstName;
//    new_node->player_info.secondName = info.secondName;
//    new_node->player_info.points = info.points;
//    new_node->next = *head_ref;
//
//    *head_ref = new_node;
//}
//
//void addNodeRecursively(NODE** head_ref, PLAYER new_data) {
//    if (*head_ref == NULL) {
//        addNode(head_ref, new_data);
//    }
//    else {
//        addNodeRecursively(&((*head_ref)->next), new_data);
//        (*head_ref)->next = *head_ref;
//    }
//}

