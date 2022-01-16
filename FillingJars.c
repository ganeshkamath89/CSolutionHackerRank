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
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY operations
 */

long solve(long n, long operations_rows, int operations_columns, long** operations) {
    
    long *arr = (long *) malloc (n*sizeof(long));
    memset(arr, 0, n);
    long sum = 0;
    for (long i = 0; i<operations_rows; i++) 
    {
        long arrValue[3] = {0};
        for(int j=0; j<operations_columns; j++)
        {
            arrValue[j] = *(*(operations + i) + j);
        }
        for(long k=arrValue[0]-1; k<=arrValue[1]-1; k++)
        {
            sum+=arrValue[2];
        }        
    }
    return sum/n;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    char* eptr;

    char** first_multiple_input = split_string(rtrim(readline()));

    long n = strtoll(*(first_multiple_input + 0), &eptr, 10);
    long m = strtoll(*(first_multiple_input + 1), &eptr, 10);

    long** operations = malloc(m * sizeof(long*));

    for (long i = 0; i < m; i++) {
        *(operations + i) = malloc(3 * (sizeof(long)));

        char** operations_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            long operations_item = strtoll(*(operations_item_temp + j), &eptr, 10);

            *(*(operations + i) + j) = operations_item;
        }
    }
    long result = solve(n, m, 3, operations);
    fprintf(fptr, "%lu\n", result);

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
