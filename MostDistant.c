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
 * The function is expected to return a DOUBLE.
 * The function accepts 2D_INTEGER_ARRAY coordinates as parameter.
 */

double solve(int coordinates_rows, int coordinates_columns, int** coordinates) {
    int x, y, max_x = 0, max_y = 0, min_x = 1e9, min_y = 1e9;
    for(int i=0; i < coordinates_rows; i++)
    {
        x = coordinates[i][0];
        y = coordinates[i][1];
        max_x = (max_x > x ? max_x : x); 
        min_x = (min_x < x ? min_x : x); 
        max_y = (max_y > y ? max_y : y); 
        min_y = (min_y < y ? min_y : y); 
    }

    double max_distance = max_x - min_x > max_y - min_y ? max_x - min_x : max_y - min_y;
    double sqrtMaxX_MaxY = sqrt(max_x*1LL*max_x + max_y*1LL*max_y);
    double sqrtMaxX_MinY = sqrt(max_x*1LL*max_x + min_y*1LL*min_y);
    double sqrtMinX_MaxY = sqrt(min_x*1LL*min_x + max_y*1LL*max_y);
    double sqrtMinX_MinY = sqrt(min_x*1LL*min_x + min_y*1LL*min_y);    
    
    max_distance = max_distance > sqrtMaxX_MaxY ? max_distance : sqrtMaxX_MaxY;
    max_distance = max_distance > sqrtMaxX_MinY ? max_distance : sqrtMaxX_MinY;
    max_distance = max_distance > sqrtMinX_MaxY ? max_distance : sqrtMinX_MaxY;
    max_distance = max_distance > sqrtMinX_MinY ? max_distance : sqrtMinX_MinY;
    return max_distance;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int n = parse_int(ltrim(rtrim(readline())));
    int** coordinates = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        *(coordinates + i) = malloc(2 * (sizeof(int)));
        char** coordinates_item_temp = split_string(rtrim(readline()));
        for (int j = 0; j < 2; j++) {
            int coordinates_item = parse_int(*(coordinates_item_temp + j));
            *(*(coordinates + i) + j) = coordinates_item;
        }
    }

    double result = solve(n, 2, coordinates);
    fprintf(fptr, "%lf\n", result);
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
