#include "functions.h"

int main(int argc, char **argv) {
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    FILE *output_file = fopen(argv[3], "w");
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
    char task1, task2, task3, task4, task5;
    task1 = task_buffer[0];
    task2 = task_buffer[2];
    task3 = task_buffer[4];
    task4 = task_buffer[6];
    task5 = task_buffer[8];

    NODE *team, *head = NULL;
    team = (NODE *) malloc(sizeof(NODE));
    team->team_name = (char *) malloc(30);

    char *buffer = NULL; //buffer pentru citirea din fisier
    buffer = (char *) malloc(100); //alocarea memoriei pentru buffer
    char *line; //linie pentru strtok

    int number_of_teams = atoi(fgets(buffer, sizeof(buffer), file));

    float *teams_sum;
    teams_sum = (float *) calloc(number_of_teams, sizeof(float));

    //Citirea valorilor din fisier si adaugarea lor la inceputul listei
    for (int i = 0; i < number_of_teams; i++) {
        int sum = 0;
        char team_name[70];
        memset(team_name, 0, 70);
        fgets(buffer, 100, file);
        line = strtok(buffer, " ");
        int number_of_players = atoi(line);
        line = strtok(NULL, " ");
        while (line != NULL) {
            strcat(team_name, line);
            strcat(team_name, " ");
            line = strtok(NULL, " ");
        }

        team_name[strlen(team_name) - 2] = '\0'; //stergerea spatiului si a \n-ului de la finalul numelui echipei

        PLAYER players[number_of_players];

        //Citirea numelui jucatorilor si a punctelor lor
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
        teams_sum[i] = (float) sum / number_of_players; //scrierea in vector a mediei punctelor
        fgets(buffer, 5, file); //citirea liniei goale dintre echipe
        add_to_beginning(&head, team_name, number_of_players, players, teams_sum[i]); //adaugarea echipei in lista
    }

    NODE *current;
    if (task1 == '1' && task2 == '0') {
        current = head;
        while (current != NULL) {
            fprintf(output_file, "%s\n", current->team_name);
            current = current->next; //parcurgerea listei si scrierea in fisier a numelor echipelor
        }
        free(current);
    }

    bubble_sort(teams_sum, number_of_teams); //sortarea vectorului cu mediile punctelor

    int x; //x = 2^k, unde k este cel mai mare numar pentru care 2^k < numarul de echipe
    for (x = 2; 1; x = x * 2)
        if (x > number_of_teams) {
            x /= 2;
            break;
        }
    for (int i = 0; i < number_of_teams - x; i++) //stergerea echipelor care nu au meci
        delete_node_by_value(&head, teams_sum[i]);

    QUEUE *matchQueue = (QUEUE *) malloc(sizeof(QUEUE));
    matchQueue->front = NULL;
    matchQueue->rear = NULL;

    STACK *winnersStack = (STACK *) malloc(sizeof(STACK));
    winnersStack->top = NULL;

    STACK *losersStack = (STACK *) malloc(sizeof(STACK));
    losersStack->top = NULL;

    NODE *top8_list = (NODE *) malloc(sizeof(NODE));
    top8_list = NULL;

    NODE *temp = (NODE *) malloc(sizeof(NODE));

    BSTNode *top8_BST = NULL;

    AVLNode *top8_AVL = (AVLNode *) malloc(sizeof(AVLNode));
    top8_AVL = NULL;

    add_nodes_to_queue(matchQueue, head); //adaugarea nodurilor din lista in coada

    //parcurgerea cozii si scrierea in fisier a meciurilor
    if (task2 == '1' && task1 == '1') {
        current = head;
        while (current != NULL) {
            trim_leading_whitespace(current->team_name); //stergerea spatiilor de la inceputul si sfarsitul numelor echipelor
            trim_trailing_whitespace(current->team_name); //pentru a nu avea probleme la scrierea in fisier
            fprintf(output_file, "%s\n", current->team_name);
            current = current->next;
        }
        free(current);
    }
    //parcurgerea cozii si scrierea in fisier a meciurilor
    if (task3 == '1' && task2 == '1' && task1 == '1')
        play_2v2_matches(matchQueue, winnersStack, losersStack, output_file, head, 1, &top8_list);

    //parcurgerea listei cu echipele de top 8 si adaugarea lor in BST
    if (task4 == '1' && task3 == '1' && task2 == '1' && task1 == '1') {
        fprintf(output_file, "\n");
        fprintf(output_file, "TOP 8 TEAMS:\n");
        temp = top8_list; //parcurgerea listei cu echipele de top 8
        while (temp != NULL) {
            top8_BST = insert_BST_node(top8_BST, temp); //adaugarea nodurilor din lista in BST
            temp = temp->next; //pentru a putea fi parcurse in ordine
        }
        free(temp);
        print_BST_to_file(top8_BST, output_file);
    }
    //parcurgerea listei cu echipele de top 8 si adaugarea lor in AVL
    if (task5 == '1' && task4 == '1' && task3 == '1' && task2 == '1' && task1 == '1') {
        fprintf(output_file, "\n");
        fprintf(output_file, "THE LEVEL 2 TEAMS ARE:\n");
        temp = top8_list;
        while (temp != NULL) {
            top8_AVL = insert_AVL_node(top8_AVL, temp);
            temp = temp->next;
        }
        free(temp);
        print_AVL_at_level_2(top8_AVL, 1, output_file);
        fprintf(output_file, "\n");
        level_order_traversal(top8_AVL, output_file);
    }
    //inchiderea fisierelor
    fclose(file);
    fclose(output_file);
    fclose(tasks);
    return 0;
}