#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define BAD_MESSAGE			-13
#define SUCCESS				  0
#define NUM_THREADS           4
#define SIZE				100

typedef struct someArgs_tag {
	int id;
	const char *msg;
} someArgs_t;

static int arr[SIZE] = {0};
//static pthread_mutex_t mutexes[SIZE];

void* helloWorld(void *args) {
	someArgs_t *arg = (someArgs_t*) args;

	if (arg->msg == NULL) {
		return BAD_MESSAGE;
	}

	printf("Message is: %s, strken = %d\n", arg->msg, strlen(arg->msg));

    int current = 1;
    for(int i = 0; i < strlen(arg->msg); ++i){
        if(arg->msg[i] == arg->msg[i+1]){
			printf("%c == %c\n", arg->msg[i], arg->msg[i+1]);
            current++;
		}
        else if((arg->msg[i] != arg->msg[i+1]) || (arg->msg[i+1] == '\0')){
			//pthread_mutex_lock(&mutexes[current]);
            arr[current]++;
			printf("arr[%d] = %d\n", current, arr[current]);
			//pthread_mutex_unlock(&mutexes[current]);
            current = 1;
        }
    }
	return SUCCESS;
}

char** subString (const char* input)
{
    const char** message = malloc(NUM_THREADS*sizeof(char*));
	int input_len = strlen(input);
	int offset = 0;
	int len = input_len / NUM_THREADS;
    int end = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        len = input_len / NUM_THREADS;
		end += len;
		//aaa bb c rr mm ll jj p ss ll uuu iiiiiiiii kk
        while(input[end-1] == input[end]){
            len++; end++;
        }
        char* newstr = (char*)malloc((len+1)*sizeof(char));
        for(int j = offset; j < offset+len; j++){
            newstr[j-offset] = input[j];
        }
        newstr[len] = '\0';
        offset += len;
		message[i] = newstr;
	}
    return message;
}


int main() {
	pthread_t threads[NUM_THREADS];
	int status;
	int i;
	int status_addr;
	someArgs_t args[NUM_THREADS];
	//for (int i = 0; i < SIZE; i++)
        //pthread_mutex_init(&mutexes[i], NULL);
	const char *sstr = "aaabbcrrmmlljjpsslluuuiiiiiiiiikk";
	//const char *sstr = "qwertyuio";
	// aaa bb c rr mm ll jj p ss ll uuu iiiiiii kk
	// aaa bb c rr		mm ll jj p ss		ll uuu iiiiiiiii		ikk
	char** messages = subString(sstr);
	/*const char *messages[] = {
		"aaabbc",
        "rrmmll",
		"jjksll",
		"uuuiiiiiiikk"
	};*/

	for (i = 0; i < NUM_THREADS; i++) {
		args[i].id = i;
		args[i].msg = messages[i];
		//printf("message = %s\n", args[i].msg);
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