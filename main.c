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

    FILE *tasks = fopen(argv[1], "r");


    if (tasks == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    char task_buffer[10];
    fgets(task_buffer, sizeof(task_buffer), tasks);
    char *task1, *task2, *task3, *task4, *task5;
    printf("AICI->%s\n", task_buffer);

    task1 = strtok(task_buffer, " ");
    task2 = strtok(NULL, " ");
    task3 = strtok(NULL, " ");
    task4 = strtok(NULL, " ");
    task5 = strtok(NULL, " ");

    NODE *head = NULL;
    NODE *team;
    team = (NODE *) malloc(sizeof(NODE));
    team->team_name = (char *) malloc(30);

    char *buffer = NULL;
    buffer = (char *) malloc(100);
    char *line;

    int number_of_teams = atoi(fgets(buffer, sizeof(buffer), file));

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
    printf("AICI->%s\n",task1);
    NODE *current;
    if (strcmp(task1,"1") == 0) {
        current = head;
        while (current != NULL) {
            fprintf(output_file, "%s\n", current->team_name);
            current = current->next;
        }
        free(current);
    }

    bubble_sort(teams_sum, number_of_teams);

    int x;
    for (x = 2; 1; x = x * 2)
        if (x > number_of_teams) {
            x /= 2;
            break;
        }
    for (int i = 0; i < number_of_teams - x; i++) {
        delete_node_by_value(&head, teams_sum[i]);
    }
    if((strcmp(task2,"1")) == 0 || strcmp(task3 ,"1") == 0) {
        current = head;
        while (current != NULL) {
            fprintf(output_file, "%s\n", current->team_name);
            fprintf(output_file, "\n");
            fprintf(output_file, "\n");
            current = current->next;
        }
        free(current);
    }

    QUEUE *matchQueue = (QUEUE *) malloc(sizeof(QUEUE));
    matchQueue->front = NULL;
    matchQueue->rear = NULL;

    STACK *winnersStack = (STACK *) malloc(sizeof(STACK));
    winnersStack->top = NULL;

    STACK *losersStack = (STACK *) malloc(sizeof(STACK));
    losersStack->top = NULL;

    add_nodes_to_queue(matchQueue, head);
    if (task3 == '1')
        play_2v2_matches(matchQueue, winnersStack, losersStack, output_file, head, number_of_teams, 1);

    fclose(file);
    fclose(output_file);
    fclose(tasks);
    return 0;
}