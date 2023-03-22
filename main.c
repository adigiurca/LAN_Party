#include "functions.h"

int main(){
    NODE *head;
    head = NULL;
    FILE* teams;
    teams = fopen("C:\\Users\\agiur\\OneDrive\\Documents\\GitHub\\LAN_Party\\d.in", "r");
    if (teams == NULL)
        puts ("Fisierul nu a putut fi deschis");
    char c = getc(teams);
    while (c != EOF){
        putchar(c);
        c = getc(teams);
    }
}

