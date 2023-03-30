#include "functions.h"

int main() {
    NODE *head = NULL;
//    head = (NODE*) malloc(sizeof(NODE));
//    head->next = NULL;
//    head->player_info->firstName = NULL;
//    head->player_info->secondName = NULL;
//    head->player_info->points = 0;
    char* teams;

    //Testing teams file content
//    char c = getc(teams);
//    while (c != EOF){
//        putchar(c);
//        c = getc(teams);
//    }

    read_names_from_file_and_add_at_beginning(&teams, head);

}

