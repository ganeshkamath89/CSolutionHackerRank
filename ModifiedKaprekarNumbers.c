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

int parse_int(char*);

/*
 * Complete the 'kaprekarNumbers' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER p
 *  2. INTEGER q
 */
#define SIZE 100000

int K[SIZE] = {0};

void kaprekar() {
    long i, j, n, sq, dNo, mid, left, right, d[12];
   
    for(n = 1; n < SIZE; n++) {
        sq = n * n;
        
        dNo = 0;
        while(sq) {
            d[++dNo] = sq % 10;
            sq /= 10;
        }
        
        mid = dNo / 2;
        for(j = dNo, i = 1; i <= dNo/2; i++, j--) d[i] ^= d[j] ^= d[i] ^= d[j];
        
        for(left = j = 0, i = mid; i >= 1; i--, j++) left += d[i] * pow(10, j);
        for(right = j = 0, i = dNo; i >= mid + 1; i--, j++) right += d[i] * pow(10, j);
        
        if(left + right == n) K[n] = 1;
        else                  K[n] = 0;
    }
}

void kaprekarNumbers(int p, int q) {

    kaprekar();
    
    int i, flag = 1;
    
    for(flag = 1, i = p; i <= q; i++) {
        if(K[i]) {
            printf("%d ", i);
            flag = 0;
        }
    }
    if (flag == 1)
    {
        printf("INVALID RANGE");
    }
}

int main()
{
    int p = parse_int(ltrim(rtrim(readline())));

    int q = parse_int(ltrim(rtrim(readline())));

    kaprekarNumbers(p, q);

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
