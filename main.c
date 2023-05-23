#include "functions.h"

int main(int argc, char **argv) {
    FILE *file = fopen("C:\\Users\\agiur\\OneDrive\\Documents\\GitHub\\LAN_Party\\d.in", "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    NODE *head = NULL;
    NODE *team;
    team = (NODE *) malloc(sizeof(NODE));
    team->team_name = (char *) malloc(30);

    char *buffer = NULL;
    buffer = (char *) malloc(100);
    char *line;

    printf("Numar echipe:\n");
    int number_of_teams = atoi(fgets(buffer, sizeof(buffer), file));
    printf("%d\n", number_of_teams);
    printf("----------------\n");

    float *teams_sum;
    teams_sum = (int *) calloc(number_of_teams, sizeof(int));

    //Citirea valorilor din fisier si adaugarea lor la inceputul listei
    for (int i = 0; i < number_of_teams; i++) {
        int sum = 0;
        char team_name[50];
        memset(team_name, 0, 50);
        fgets(buffer, 100, file);
        line = strtok(buffer, " ");
        int number_of_players = atoi(line);
        //printf("%d ", number_of_players);
        line = strtok(NULL, " ");
        while (line != NULL) {
            strcat(team_name, line);
            strcat(team_name, " ");
            line = strtok(NULL, " ");
        }
        team_name[strlen(team_name) - 1] = '\0';
        //printf("%s", team_name);

        PLAYER players[number_of_players];

        for (int j = 0; j < number_of_players; j++) {
            fgets(buffer, 100, file);
            line = strtok(buffer, " ");
            players[j].firstName = (char *) malloc(strlen(line) + 5);
            strcpy(players[j].firstName, line);
            //printf("%s ", players[j].firstName);
            line = strtok(NULL, " ");
            players[j].secondName = (char *) malloc(strlen(line) + 5);
            strcpy(players[j].secondName, line);
            //printf("%s ", players[j].secondName);
            line = strtok(NULL, " ");
            players[j].points = atoi(line);
            //printf("%d\n", players[j].points);
            sum += players[j].points;
        }
        teams_sum[i] = (float)sum/number_of_players;
        //printf("\n");
        fgets(buffer, 5, file);
        add_to_beginning(&head, team_name, number_of_players, players, teams_sum[i]);
    }
    bubble_sort(teams_sum, number_of_teams);
    for (int i = 0; i < number_of_teams; i++) {
        printf("%f ", teams_sum[i]);
    }
    fclose(file);
    //print(head);
    printf("\n\nLista dupa eliminarea echipelor cu cel mai mic punctaj:\n\n");
    int x;
    for (x = 2; 1; x = x * 2)
        if (x > number_of_teams) {
            x /= 2;
            break;
        }
    for (int i = 0; i < number_of_teams - x; i++) {
        delete_node_by_value(&head, teams_sum[i]);
    }

    print(head);

    QUEUE* matchQueue = (QUEUE*)malloc(sizeof(QUEUE));
    matchQueue->front = NULL;
    matchQueue->rear = NULL;

    STACK* winnersStack = (STACK*)malloc(sizeof(STACK));
    winnersStack->top = NULL;

    STACK* losersStack = (STACK*)malloc(sizeof(STACK));
    losersStack->top = NULL;

    add_nodes_to_queue(matchQueue, head);

    //play_2v2_matches(matchQueue, winnersStack, losersStack);

    printQueue(matchQueue);

    //freeStack(losersStack);
    //free(matchQueue);
    return 0;
}