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

#define ll long long
char** split_str;

double const EPS = 1e-6, PI = 3.14;
const int N = 1e3 + 9, OO = 1e9;

char arr[109][109];

double areaOfTri(double x1, double y1, double x3, double y3, double x2, double y2) {
  return fabs(x1 * (y3 - y2) + x3 * (y2 - y1) + x2 * (y1 - y3)) / 2;
}


int main()
{
    char** first_multiple_input = split_string(rtrim(readline()));

    int h = parse_int(*(first_multiple_input + 0));

    int w = parse_int(*(first_multiple_input + 1));

    char** second_multiple_input = split_string(rtrim(readline()));

    int circleX = parse_int(*(second_multiple_input + 0));

    int circleY = parse_int(*(second_multiple_input + 1));

    int r = parse_int(*(second_multiple_input + 2));

    char** third_multiple_input = split_string(rtrim(readline()));

    int x1 = parse_int(*(third_multiple_input + 0));

    int y1 = parse_int(*(third_multiple_input + 1));

    int x3 = parse_int(*(third_multiple_input + 2));

    int y3 = parse_int(*(third_multiple_input + 3));

    // Write your code here

    for (int i = 0; i < 103; ++i)
    {
        for (int j = 0; j < 103; ++j)
        {
            arr[i][j] = '.';
        }
    }
    ll dist;
    r *= r;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j) {
            dist = (i - circleX) * (i - circleX) + (j - circleY) * (j - circleY);
            if (dist <= r)
            {
                arr[j][i] = '#';
            }
        }
    }
    double x2 = x1 + x3 + y1 - y3;
    double y2 = x3 - x1 + y1 + y3;
    double x4 = x1 + x3 + y3 - y1;
    double y4 = x1 - x3 + y1 + y3;
    x2 /= 2, y2 /= 2, x4 /= 2, y4 /= 2;
    double areaRect = areaOfTri(x1, y1, x2, y2, x3, y3) + areaOfTri(x1, y1, x4, y4, x3, y3);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            double totalArea = 
                areaOfTri(x1, y1, i, j, x4, y4) + 
                areaOfTri(x4, y4, i, j, x3, y3) + 
                areaOfTri(x3, y3, i, j, x2, y2) + 
                areaOfTri(i, j, x2, y2, x1, y1);
            if(fabs(totalArea - areaRect) <= EPS)
            {
                arr[j][i] = '#';
            }
        }
    }
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            printf("%c", arr[i][j]);
        }
        printf("%c", '\n');
    }
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
