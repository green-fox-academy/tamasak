#ifndef BASICS_H_INCLUDED
#define BASICS_H_INCLUDED
void print_list (void);
void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
char getch(void);
void set_username(info_storeage *storeage);
void list_users(info_storeage *storeage);
void init(info_storeage *storeage);



#endif // BASICS_H_INCLUDED
