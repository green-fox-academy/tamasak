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

todo add_new_task();

void init(todo_storeage *storeage)
{
    storeage->array = NULL;
    storeage->length = 0;
    printf("Todo Application\n====================\nCommands:\n");
    //Implemented commands: ...or at least planned
    printf("-a\tAdds a new task\n-wr\tWrite current todos to file\n-rd\tRead todos from a file\n");
    printf("-l\tLists all the tasks\n-e\tEmpty the list\n-r\tRemoves a task\n-c\tCompletes a task\nq\tQuit program\n\n");
}

int main()
{
    todo_storeage storeage;
    init(&storeage);

    int prio = 100;
    while (1) {
        char input[250];
        gets(input);
        char input2[250];
        strcpy(input2, input);
        char *task = strtok(input, " ");

        int ret;
        if ((ret = strcmp (task, "-a")) == 0) {
            add_new_task(&storeage, input2, prio);
        }
        if ((ret = strcmp (task, "-l")) == 0)
            list_task(&storeage);
        if ((ret = strcmp (task, "q")) == 0)
            break;
    }

    return 0;
}

todo add_new_task(todo_storeage *storeage, char *input, int prio)
{
    int length_new = storeage->length + 1;
    storeage->array = realloc(storeage->array, length_new * sizeof(todo));
    storeage->length = length_new;

    char *name;
    name = strtok(input, "\"");
    name = strtok(NULL, "\"");
    //uj struct
    strcpy(storeage->array[length_new - 1].name, name);
    storeage->array[length_new - 1].priority = prio;
    printf("Task has been added.\n\n");
    //printf("Write \"-wr\" to write changes into file.\n");

    //return 0;
}

void list_task(todo_storeage *storeage)
{
    printf("TODO list:\n");
    for (int i = 0; i < storeage->length; i++) {
        printf("%d\t%s\n", (i+1), storeage->array[i].name);
    printf("\n");
    }
}

void write_to_file(todo_storeage *storeage, char *path)
{

}
