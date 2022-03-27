#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define BAD_MESSAGE			-13
#define SUCCESS				  0
#define NUM_THREADS           4

typedef struct someArgs_tag {
	int id;
	const char *msg;
} someArgs_t;

static int arr[100] = {0};

void* helloWorld(void *args) {
	someArgs_t *arg = (someArgs_t*) args;

	if (arg->msg == NULL) {
		return BAD_MESSAGE;
	}

    int current = 1;
    for(int i = 0; i < strlen(arg->msg)-1; ++i){
        if(arg->msg[i] == arg->msg[i+1])
            current++;
        else{
            arr[current]++;
            current = 1;
        }
    }
	return SUCCESS;
}


int main() {
	pthread_t threads[NUM_THREADS];
	int status;
	int i;
	int status_addr;
	someArgs_t args[NUM_THREADS];
	const char *messages[] = {
		"aaabbc",
        "rrmmll",
		"jjksll",
		"uuuiiiiiiikk"
	};

	for (i = 0; i < NUM_THREADS; i++) {
		args[i].id = i;
		args[i].msg = messages[i];
	}

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
		if (status != 0) {
			printf("main error: can't create thread, status = %d\n", status);
			exit(ERROR_CREATE_THREAD);
		}
	}

	printf("Main Message\n");

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_join(threads[i], (void**)&status_addr);
		if (status != SUCCESS) {
			printf("main error: can't join thread, status = %d\n", status);
			exit(ERROR_JOIN_THREAD);
		}
		printf("joined with address %d\n", status_addr);
	}


    printf("Array is: ");
    for(int i = 0; i < 100; ++i){
        printf("%d ", arr[i]);
    }

	return 0;
}