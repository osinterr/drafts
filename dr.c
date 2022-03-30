#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS				  0
#define NUM_THREADS           4
#define SIZE				100



/*int main(){
    time_t t0 = time(0);
    
    // some code
    
    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("%lf", time_in_seconds);
}*/


char** subString (const char* input)
{
    char** message = malloc(NUM_THREADS*sizeof(char*));
	int input_len = strlen(input);
	int offset = 0;
	int len = input_len / NUM_THREADS;
    int end = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        len = input_len / NUM_THREADS;
		end += len;

        if(i == NUM_THREADS-1){
            char* newstr = (char*)malloc((len+1)*sizeof(char));
            for(int j = offset; j < input_len; j++)
                newstr[j-offset] = input[j]; 
            message[i] = newstr;
            //printf("Message: %s", message[i]);
            return message;
        }

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
    //return message;
}


int main() {
    char* sstr = (char*)malloc(SIZE*sizeof(char));
    //sstr = "aaabbcrrmmlljjpsslluuuiiiiiiiiikkzxcvbnm";
    sstr = "qwertyuio";
	char** messages = subString(sstr);

    for(int i = 0; i < NUM_THREADS; ++i){
        printf("%s ", messages[i]);
    }

}

