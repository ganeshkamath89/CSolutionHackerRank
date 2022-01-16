#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
 */
#define MOD 1000000007
 long long int expn(long long int N, long long int K)
{
    if(K==0) return 1;
    if(K==1) return N%MOD;
    if(K%2 ==0)
    {
        long long int temp = expn(N,K/2);
        return (temp*temp)%MOD;
    }
    else
    {
        long long int temp = expn(N,K/2);
        temp = (temp*temp)%MOD;
        return (temp*N)%MOD;
    }
}

long long int solve(char* a, char* b) {

    int arr[100009] = {0}, brr[100009] ={0};
    long long int M = 1000000007;
    long long int N = 1000000006;
    long long int temp1, temp2;
    for(long long int i = 0; a[i] != '\0'; i++)
    {
        arr[i] = a[i] - '0';
    }
    for(long long int j = 0; b[j] != '\0'; j++)
    {
        brr[j] = b[j] - '0';
    }        
    temp1 = arr[0] % M;
    for(long long int k=1 ; k< strlen(a) ; k++)
    {
        temp1 = (10*temp1 + arr[k] )% M; 
    }
    temp2 = brr[0] % N;
    for(long long int l=1 ; l< strlen(b) ; l++)
    {
        temp2 = (10*temp2 + brr[l] )% N; 
    }         
    return expn(temp1,temp2);    
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        char* a = *(first_multiple_input + 0);
        char* b = *(first_multiple_input + 1);
        long long int result = solve(a, b);
        fprintf(fptr, "%llu\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
