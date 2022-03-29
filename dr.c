#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
 
#define ERROR_CREATE_THREAD 1
#define ERROR_JOIN_THREAD 2
#define BAD_MESSAGE 3
#define SUCCESS 0
#define NUM_THREADS 4
#define SIZE 100

char** subString (const char* input)
{
    char** message = malloc(NUM_THREADS*sizeof(char*));
	int input_len = strlen(input);
	int offset = 0;
	int len = input_len / NUM_THREADS;
    int end = len;

    for(int i = 0; i < NUM_THREADS; i++){
        len = input_len / NUM_THREADS;
        printf("offset = %d, inpu[offset] = %c\n", offset, input[offset]);
        if(i == NUM_THREADS-1){
            char* newstr = (char*)malloc((len+1)*sizeof(char*));
            for(int j = offset; j < input_len; j++){
                newstr[j-offset] = input[j];
                //printf("attention: %c\n", newstr[j-offset]);
            }
            newstr[input_len-offset] = '\0';
            message[i] = newstr;
            //return ;
        }

        else{
            while(input[end-2] == input[end-1]){
                printf("%c == %c, %d == %d\n", input[end-1], input[end], end-1, end);
                len++; end++;
            }

            char* newstr = (char*)malloc((len+1)*sizeof(char*));
            for(int j = offset; j < offset+len; j++){
                newstr[j-offset] = input[j];
            }
            newstr[len] = '\0';
            offset += len;
            end += len;
            message[i] = malloc(len*sizeof(char));
            message[i] = newstr;
            //printf("print from func^ message[i] = %s\n", message[i]);
        }
	}
    return message;
}

int main() {
    const char *sstr = "aaabbcrrmmlljjkslluuuiiiiiiipp";
    //const char *sstr = "aaaaaaaaaaaaa";
    //const char *sstr = "ffqwerrbguityhuiiipppoooooooop";
    // aaabbcrr     mmlljjk     slluuuiiiiiiii      kk


    char** message = subString(sstr);


	for(int i = 0; i < NUM_THREADS; i++){
		printf("from main: %d %s\n", i, message[i]);
	}
}


/*
aaabbcrrmmlljjkslluuuiiiiiiikk
0  1  2  3  4  5  6  7      8  9  10 11 12 13 14    15 16 17 18 19 20 21 22 23 24 25 26 27      28 29
a  a  a  b  b  c  r  r      m  m  l  l  j  j  k     s  l  l  u  u  u  i  i  i  i  i  i  i       k  k
*/

