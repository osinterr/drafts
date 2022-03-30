#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void amount_different(int *arr, char *sstr){
    int current = 1;
    for(int i = 0; i < sizeof(sstr); ++i){
        if(sstr[i] == sstr[i+1])
            current++;
        else{
            arr[current]++;
            current = 1;
        }
    }
}

int maxinmum_lenth(int *arr){
    int lenth = 0, maximum = 0;
    for(int i = 0; i < SIZE; ++i){
        if(arr[i] > maximum){
            maximum = arr[i];
            lenth = i;
        }
    }
    return lenth;
}

char find_symbol(char* sstr, int lenth){
    int current = 1;
    char symb;
    for(int i = 0; i < sizeof(sstr); ++i){
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

void print_ans(char symb, int lenth){
    for(int i = 0; i < lenth; ++i)
        printf("%c", symb);
}

int main(){
    int arr1[SIZE] = {0};
    /*char sstr[] = {'u', 'u', 'u',
                '1', 
                'w', 'w', 'w', 
                'p', 'p', 
                'j', 
                'p', 'p', 'p', 'p', 'p', 'p', 
                'k', 
                'o', 'o', 'o',
                'j', 
                'f', 'f', 'f', 
                'y', 'y', 'y'
    };*/

    char *sstr1 = (char*)malloc(10*sizeof(char));

    char *str1 = (char*)malloc(100*sizeof(char));

    /*for(int i = 0; i < sizeof(sstr1); i++)
        printf("%c", sstr1[i]);*/


    amount_different(arr1, sstr1);
    int lenth1 = maxinmum_lenth(arr1);
    char symb1 = find_symbol(sstr1, lenth1);
    print_ans(symb1, lenth1);


    /*amount_different(arr, sstr);
    int lenth = maxinmum_lenth(arr);
    char symb = find_symbol(sstr, lenth);
    print_ans(symb, lenth);*/

    return 0;
}