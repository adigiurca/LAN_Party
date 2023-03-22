#include "functions.h"

int main(){
    NODE *head;
    head = NULL;

    //Reading from d.in
    FILE* teams;
    teams = fopen("C:\\Users\\agiur\\OneDrive\\Documents\\GitHub\\LAN_Party\\d.in", "r");
    if (teams == NULL)
        puts ("Fisierul nu a putut fi deschis");

    //Testing teams file content
//    char c = getc(teams);
//    while (c != EOF){
//        putchar(c);
//        c = getc(teams);
//    }



    //read_names_from_file_and_add_at_beginning(teams, (*head));

}

