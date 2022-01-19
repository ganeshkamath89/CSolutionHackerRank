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
 * The function accepts 2D_INTEGER_ARRAY steps as parameter.
 */
typedef unsigned long long ull;
ull solve(ull steps_rows, ull steps_columns, ull** steps) {
    ull minX = ULLONG_MAX, minY = ULLONG_MAX;
    for (ull i = 0; i < steps_rows; i++) {
        for (ull j = 0; j < steps_columns; j++) {
            if (j == 0)
            {
                minX = (minX < steps[i][j]) ? minX : steps[i][j];
            }
            else if (j == 1)
            {
                minY = (minY < steps[i][j]) ? minY : steps[i][j];
            }
        }
    }
    return minX*minY;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int n = parse_int(ltrim(rtrim(readline())));
    char* eptr;
    ull** steps = malloc(n * sizeof(ull*));
    for (ull i = 0; i < n; i++) {
        *(steps + i) = malloc(2 * (sizeof(int)));
        char** steps_item_temp = split_string(rtrim(readline()));
        for (ull j = 0; j < 2; j++) {
            ull steps_item = strtoll(*(steps_item_temp + j), &eptr, 10);
            *(*(steps + i) + j) = steps_item;
        }
    }
    ull result = solve(n, 2, steps);
    fprintf(fptr, "%llu\n", result);
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
