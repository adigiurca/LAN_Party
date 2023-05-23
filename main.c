#include "functions.h"

int main(int argc, char **argv) {
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    FILE *output_file = fopen(argv[3], "w"); // Open file for writing
    if (output_file == NULL) {
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

        team_name[strlen(team_name) - 2] = '\0';

        PLAYER players[number_of_players];

        for (int j = 0; j < number_of_players; j++) {
            fgets(buffer, 100, file);
            line = strtok(buffer, " ");
            players[j].firstName = (char *) malloc(strlen(line) + 5);
            strcpy(players[j].firstName, line);
            line = strtok(NULL, " ");
            players[j].secondName = (char *) malloc(strlen(line) + 5);
            strcpy(players[j].secondName, line);
            line = strtok(NULL, " ");
            players[j].points = atoi(line);
            sum += players[j].points;
        }
        teams_sum[i] = (float) sum / number_of_players;
        fgets(buffer, 5, file);
        add_to_beginning(&head, team_name, number_of_players, players, teams_sum[i]);
    }
    bubble_sort(teams_sum, number_of_teams);
    for (int i = 0; i < number_of_teams; i++) {
        printf("%f ", teams_sum[i]);
    }
    NODE *current = head;
    while (current != NULL) {
        fprintf(output_file, "%s\n", current->team_name);
        current = current->next;
    }

    //print(head);
    printf("\n\nLista dupa eliminarea echipelor cu cel mai mic punctaj:\n\n");
    int x;
    for (x = 2; 1; x = x * 2)
        if (x > number_of_teams) {
            x /= 2;
            break;
        }
    printf("%d\n", number_of_teams - x);
    for (int i = 0; i < number_of_teams - x; i++) {
        delete_node_by_value(&head, teams_sum[i]);
    }

    print(head);

    QUEUE *matchQueue = (QUEUE *) malloc(sizeof(QUEUE));
    matchQueue->front = NULL;
    matchQueue->rear = NULL;

    STACK *winnersStack = (STACK *) malloc(sizeof(STACK));
    winnersStack->top = NULL;

    STACK *losersStack = (STACK *) malloc(sizeof(STACK));
    losersStack->top = NULL;

    add_nodes_to_queue(matchQueue, head);

    play_2v2_matches(matchQueue, winnersStack, losersStack, output_file, head, number_of_teams);

    fclose(file);
    fclose(output_file);
    return 0;
}