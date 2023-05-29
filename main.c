#include "functions.h"

int main(int argc, char **argv) {
    FILE *file = fopen(argv[2], "r");
    FILE *output_file = fopen(argv[3], "w");
    FILE *tasks = fopen(argv[1], "r");
    if (file == NULL || output_file == NULL || tasks == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 1;
    }

    char task_buffer[10];
    fgets(task_buffer, sizeof(task_buffer), tasks);
    char task1, task2, task3, task4, task5;
    task1 = task_buffer[0]; task2 = task_buffer[2]; task3 = task_buffer[4]; task4 = task_buffer[6]; task5 = task_buffer[8];

    NODE *team, *head = NULL;
    team = (NODE *) malloc(sizeof(NODE));
    team->team_name = (char *) malloc(30);

    char *buffer = NULL; //buffer pentru citirea din fisier
    buffer = (char *) malloc(100); //alocarea memoriei pentru buffer

    int number_of_teams = atoi(fgets(buffer, sizeof(buffer), file));

    float *teams_sum;
    teams_sum = (float *) calloc(number_of_teams, sizeof(float));

    //Citirea valorilor din fisier si adaugarea lor la inceputul listei
    for (int i = 0; i < number_of_teams; i++) {
        int sum = 0;
        char *team_name;
        int number_of_players;
        process_team(file, &team_name, &number_of_players, &sum); //citirea numelui echipei si a numarului de jucatori

        PLAYER players[number_of_players];

        //Citirea numelui jucatorilor si a punctelor lor
        process_players(file, players, number_of_players, &sum);

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
    }

    bubble_sort(teams_sum, number_of_teams); //sortarea crescatoare a vectorului cu mediile punctelor

    int x = 1; //x = 2^k, unde k este cel mai mare numar pentru care 2^k < numarul de echipe
    while (x <= number_of_teams) {
        x *= 2;
    }
    x /= 2;
    for (int i = 0; i < number_of_teams - x; i++) //stergerea primelor number_of_teams - x echipe
        delete_node_by_value(&head, teams_sum[i]);

    QUEUE *matchQueue = calloc(1, sizeof(QUEUE));
    STACK *winnersStack = calloc(1, sizeof(STACK));
    STACK *losersStack = calloc(1, sizeof(STACK));
    NODE *top8_list = NULL;
    NODE *temp = NULL;
    BSTNode *top8_BST = NULL;
    AVLNode *top8_AVL = NULL;

    add_nodes_to_queue(matchQueue, head); //adaugarea nodurilor din lista in coada

    //parcurgerea cozii si scrierea in fisier a meciurilor
    if (task2 == '1' && task1 == '1')
        print_and_free_teams(head, output_file);
    //parcurgerea cozii si scrierea in fisier a meciurilor
    if (task3 == '1' && task2 == '1' && task1 == '1')
        play_2v2_matches(matchQueue, winnersStack, losersStack, output_file, head, 1, &top8_list);

    //parcurgerea listei cu echipele de top 8 si adaugarea lor in BST
    if (task4 == '1' && task3 == '1' && task2 == '1' && task1 == '1') {
        fprintf(output_file, "\nTOP 8 TEAMS:\n");
        temp = top8_list; //parcurgerea listei cu echipele de top 8
        while (temp != NULL) {
            top8_BST = insert_BST_node(top8_BST, temp); //adaugarea nodurilor din lista in BST
            temp = temp->next;
        }
        free(temp);
        print_BST_to_file(top8_BST, output_file);
        free_BST(top8_BST);
    }
    //parcurgerea listei cu echipele de top 8 si adaugarea lor in AVL
    if (task5 == '1' && task4 == '1' && task3 == '1' && task2 == '1' && task1 == '1') {
        fprintf(output_file, "\nTHE LEVEL 2 TEAMS ARE:\n");
        temp = top8_list;
        while (temp != NULL) {
            top8_AVL = insert_AVL_node(top8_AVL, temp);
            temp = temp->next;
        }
        free(temp);
        print_AVL_at_level_2(top8_AVL, 1, output_file);
        free_AVL(top8_AVL);
    }
    //inchiderea fisierelor
    fclose(file);
    fclose(output_file);
    fclose(tasks);
    return 0;
}