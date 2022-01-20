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
 * The function is expected to return a STRING.
 * The function accepts 2D_INTEGER_ARRAY coordinates as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
 
int x_min = INT_MAX , x_max = INT_MIN , y_min = INT_MAX , y_max = INT_MIN ;
bool checkOnRectangular(int x_coord, int y_coord) {

    bool firstPossibility = false;
    bool secondPossibility = false;
    if (((x_coord == x_min || x_coord == x_max))) {
        if ((y_coord >= y_min && y_coord <= y_max)) {
            firstPossibility = true;
        }
    } else if (((y_coord == y_min || y_coord == y_max))) {
        if ((x_coord >= x_min && x_coord <= x_max)) {
            secondPossibility = true;
        }
    }
    if (!firstPossibility && !secondPossibility) {
        return false;
    }
    return true;
}

void findMax_and_Min_X_and_Y(int x_coord, int y_coord) {
    if (x_min > x_coord) {
        x_min = x_coord;
    }
    if (x_max < x_coord) {
        x_max = x_coord;
    }
    if (y_min > y_coord) {
        y_min = y_coord;
    }
    if (y_max < y_coord) {
        y_max = y_coord;
    }
}
char* solve(int coordinates_rows, int coordinates_columns, int** coordinates) {
    int* x = (int*)malloc(coordinates_rows*sizeof(int));
    int* y = (int*)malloc(coordinates_rows*sizeof(int));
    x_min = INT_MAX , x_max = INT_MIN , y_min = INT_MAX , y_max = INT_MIN ;
    for (int i = 0; i < coordinates_rows; i++) {
        for (int j = 0; j < coordinates_columns; j++) {
            if (j == 0)
            {
                x[i] = *(*(coordinates + i) + j);
            }
            else
            {
                y[i] = *(*(coordinates + i) + j);
                findMax_and_Min_X_and_Y(x[i], y[i]);
            }
        }
    }
    
    
        bool onRectangle = true;
        for (int j = 0; j < coordinates_rows; j++) {
            if (!checkOnRectangular(x[j], y[j])) {
                onRectangle = false;
                return "NO";
            }
        }
        if (onRectangle) {
            return"YES";
        }
    return "NO";
    
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
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

        char* result = solve(n, 2, coordinates);

        fprintf(fptr, "%s\n", result);
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
