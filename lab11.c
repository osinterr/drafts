#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <conio.h>
#include <string.h>
 
#define ERROR_CREATE_THREAD 1
#define ERROR_JOIN_THREAD 2
#define BAD_MESSAGE 3
#define SUCCESS 0
#define NUM_THREADS 4
#define SIZE 100




typedef struct someArgs_tag {
    int id;
    const char *msg;
} someArgs_t;

static int arr1[100] = {0};
//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void amount_different(const char *sstr){        // заполняет массив
    int current = 1;
    for(int i = 0; i < strlen(sstr); ++i){
        if(sstr[i] == sstr[i+1])
            current++;
        else{
            arr1[current]++;
            current = 1;
        }
    }
}

int maxinmum_lenth(){                           // находит в массиве самую частую длину
    int lenth = 0, maximum = 0;
    for(int i = 0; i < SIZE; ++i){
        if(arr1[i] > maximum){
            maximum = arr1[i];
            lenth = i;
        }
    }
    return lenth;
}

char find_symbol(char* sstr, int lenth){        // находит символ самой частой длины
    int current = 1;
    char symb;
    for(int i = 0; i < strlen(sstr); ++i){
        if(sstr[i] == sstr[i+1])
            current++;
        else{
            if(current == lenth){
                symb = sstr[i];
                return symb;
            }
            current = 1;
        }
    }
    return symb;
}

void print_ans(char symb, int lenth){               // выводит ответ
    for(int i = 0; i < lenth; ++i)
        printf("%c", symb);
}

void* helloWorld(void *args) {                      // функция для потоков
    someArgs_t *arg = (someArgs_t*) args;
    //pthread_mutex_lock(&mutex);
    amount_different(arg->msg);
    //pthread_mutex_unlock(&mutex);
    return SUCCESS;
}


/*void* helloWorld1(void *args) {                   // функция для потоков с сайта точно работает
    someArgs_t *arg = (someArgs_t*) args;
    int len;
 
    if (arg->msg == NULL) {
        return 0;
        //return BAD_MESSAGE;
    }
 
    len = strlen(arg->msg);
    printf("%s\n", arg->msg);
    arg->out = len;
 
    return SUCCESS;
}*/

int main() {
    pthread_t threads[NUM_THREADS];
    int status;
    int i;
    int status_addr;
    someArgs_t args[NUM_THREADS];
    char sstr[] = {'a', 'a', 'a',                   // общая строка для main, потом разобью
                'b', 'b', 
                'c', 
                'w', 'w', 'w', 
                'p', 'p', 
                'd', 'd', 
                'p', 'p', 
                'u', 'u', 'j'
    };
    const char *messages[] = {                      // разбитая строка
        "aaabbc",
        "wwwppdd",
        NULL,
        "ppuuj"
    };

    //pthread_t* threads = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));
	//someArgs_t* args = (someArgs_t*) malloc(NUM_THREADS * sizeof(someArgs_t));

    for (i = 0; i < NUM_THREADS; i++) {                 // заполняем структуру i номер потока msg строка
        args[i].id = i;
        args[i].msg = messages[i];
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("%d, %s\n", args[i].id, args[i].msg);
    }

    for (i = 0; i < NUM_THREADS; i++) {                 // создание потока
        //printf("Im here\n");
        status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(ERROR_CREATE_THREAD);
        }
        //printf("Im here\n");

    }



    for (i = 0; i < NUM_THREADS; i++) {                 // ждем завершения потока
        printf("Im here, %d\n", i);
        status = pthread_join(threads[i], (void**)&status_addr);
        if (status != SUCCESS) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(ERROR_JOIN_THREAD);
        }
        printf("joined with address %d\n", status_addr);
    }

    for(int i = 0; i < SIZE; ++i)                       // просто посмотреть на массив итоговый
        printf("%d ", arr1[i]);

    int lenth1 = maxinmum_lenth();                      
    char symb1 = find_symbol(sstr, lenth1);
    print_ans(symb1, lenth1);
}