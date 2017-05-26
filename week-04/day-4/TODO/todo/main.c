#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

typedef struct
{
    char name[200];
    int priority;
    //int date;
} todo;

typedef struct
{
    todo *array;
    int length;
} todo_storeage;

int add_new_task(todo_storeage *storeage, char *input, int prio);
int list_task(todo_storeage *storeage);
int write_to_file(todo_storeage *storeage, char *input);
int read_from_file(todo_storeage *storeage, char *input);
int empty_the_list(todo_storeage *storeage);
void show_command();
void deinit(todo_storeage *storage);
int remove_task (todo_storeage *storeage, char *input);
int add_priority (todo_storeage *storeage, char *input);

void init(todo_storeage *storeage)
{
    storeage->array = NULL;
    storeage->length = 0;
    show_command();
}

int main()
{
    todo_storeage storeage;
    init(&storeage);

    int prio = 100;
    while (1) {
        char input[250];
        gets(input);
        FILE *file = fopen("todo.log","a");
        fprintf(file, "%s\n", input);
        fclose(file);
        char input2[250];
        strcpy(input2, input);
        char *task = strtok(input, " ");

        int ret;
        if ((ret = strcmp (task, "-a")) == 0) {
            int cont;
            if (cont = strstr(input2, "\"") != 0) {
                (add_new_task(&storeage, input2, prio) == 1);
                printf("Task has been added.\n\n");
            } else {
                printf("Unable to add: No task is provided.\n");
            }
        }
        if ((ret = strcmp (task, "-l")) == 0) {
            list_task(&storeage);
        }else if ((ret = strcmp (task, "-wr")) == 0) {
            write_to_file(&storeage, input2);
            printf("The tasks has been saved file.\n");
        }else if ((ret = strcmp (task, "-rd")) == 0) {
            read_from_file(&storeage, input2);
            printf("The tasks has been red.\n");
        }else if ((ret = strcmp (task, "-e")) == 0) {
            empty_the_list(&storeage);
            system("clear");
            printf("No todos for today! :).\n");
        }else if ((ret = strcmp (task, "-h")) == 0) {
            show_command();
        }else if ((ret = strcmp (task, "-r")) == 0) {
            int cont;
            if (cont = strstr(input2, " ") != 0) {
                remove_task (&storeage, input2);
            } else {
                printf("Unable to remove: No index is provided.\n");
            }
        }else if ((ret = strcmp (task, "-p")) == 0) {
            add_priority (&storeage, input2);
        }else if ((ret = strcmp (task, "-h")) == 0) {
            show_command();
        }else if ((ret = strcmp (task, "q")) == 0) {
            break;
        }else {
            printf("Unsupported argument.\n");
        }
    }
    deinit(&storeage);
    return 0;
}

int add_new_task(todo_storeage *storeage, char *input, int prio)
{
    int length_new = storeage->length + 1;
    storeage->array = realloc(storeage->array, length_new * sizeof(todo));
    storeage->length = length_new;

    char *name;
    name = strtok(input, "\"");
    name = strtok(NULL, "\"");
    /*char *prior;
    prior = strtok(NULL, "\"");
    if (atoi(prior) != NULL) {
        prio = atoi(prior);
    }
    else {
        prio = 100;
    }*/
    //prio = atoi(prior);
    if (name) {
        strcpy(storeage->array[length_new - 1].name, name);
        storeage->array[length_new - 1].priority = prio;
        return 1;
    } else {
        printf("Unable to add: No task is provided.\n");
        return 0;
    }
}

int list_task(todo_storeage *storeage)
{
    printf("TODO list:\n");
    printf("Num  |\tTask\t\t|  Prio\n");
    for (int i = 0; i < storeage->length; i++) {
        printf("%d\t%s\t\t   %d\n", (i+1), storeage->array[i].name, storeage->array[i].priority);
    }
    printf("\n");
    //printf("%d\n", sizeof(storeage->array[0].name));
    return 0;
}

int write_to_file(todo_storeage *storeage, char *input)
{
    char *path;
    path = strtok(input, "\"");
    path = strtok(NULL, "\"");
    FILE *file = fopen(path,"w");
    for (int i = 0; i < storeage->length; i++)
        fprintf(file, "%d %s\n", storeage->array[i].priority, storeage->array[i].name);
    fclose(file);
    return 0;
}

int read_from_file(todo_storeage *storeage, char *input)
{
    char name[200];
    char *path;
    path = strtok(input, "\"");
    path = strtok(NULL, "\"");
    FILE *file = fopen(path,"r");
    char output[200];
    int prio;
    while (fscanf(file, "%d %s\n", &prio, name) == 2) {
        strcpy (output,"-a\"");
        strcat (output, name);
        strcat (output,"\"");
        add_new_task(storeage, output, prio);
    }
    fclose(file);
    return 0;
}

int empty_the_list(todo_storeage *storeage)
{
    storeage->array = NULL;
    storeage->length = 0;
    return 0;
}

void show_command()
{
    system("clear");
    printf("Todo Application\n====================\nCommands:\n");
    printf("-a\tAdds a new task\n-wr\tWrite current todos to file\n-rd\tRead todos from a file\n");
    printf("-l\tLists all the tasks\n-e\tEmpty the list\n-r\tRemoves a task\n-p\tSet priority\n");
    printf("-h\tShow commands\nq\tQuit program\n\n");
}

void deinit(todo_storeage *storeage)
{
    free(storeage->array);
    empty_the_list(storeage);
}
int remove_task (todo_storeage *storeage, char *input)
{
    char *task;
    task = strtok(input, " ");
    task = strtok(NULL, " ");
    int num = atoi(task);
    if ((num <= storeage->length) && (num > 0)) {
        FILE *file = fopen("backup","w");
        for (int i = 0; i < storeage->length; i++) {
            if (i != (num-1))
            fprintf(file, "%s\n", storeage->array[i].name);
        }
        fclose(file);
        empty_the_list(storeage);
        char output[200];
        strcpy (output,"-rd\"");
        strcat (output, "backup");
        strcat (output,"\"");
        read_from_file(storeage, output);
        //char filename[] = "backup";
        //int remove(filename);
        printf("Task %d has been removed.\n", num);
    } else {
        printf("Unable to remove: Index is out of bound.\n");
    }
    return 0;
}
int add_priority (todo_storeage *storeage, char *input)
{

    char *numb;
    numb = strtok(input, " ");
    numb = strtok(NULL, " ");
    char *prior;
    prior = strtok(NULL, " ");
    int num = atoi(numb);
    int prio = atoi(prior);

    storeage->array[num-1].priority = prio;
    printf("Priority of the %d. task has been changed to %d.", num, prio);
    return 0;
}
