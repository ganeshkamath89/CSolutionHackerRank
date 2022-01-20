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
 * The function accepts following parameters:
 *  1. INTEGER x1
 *  2. INTEGER y1
 *  3. INTEGER x2
 *  4. INTEGER y2
 *  5. INTEGER xm
 *  6. INTEGER ym
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

 
struct Point
{
    int x;
    int y;
};

bool onSegment(struct Point p,struct  Point q,struct  Point r)
{
    if (q.x <= ((p.x > r.x) ?p.x : r.x) && q.x >= ((p.x < r.x) ?p.x : r.x) &&
        q.y <= ((p.y > r.y) ?p.y : r.y) && q.y >= ((p.y < r.y) ?p.y : r.y))
    {
       return true;
    }
    else
    { 
        return false;
    }
}

int orientation(struct Point p,struct  Point q,struct  Point r)
{
    long long int first = (long long int)((long long int)(q.y - p.y) * (long long int)(r.x - q.x));
    long long int second = (long long int)((long long int)(q.x - p.x) * (long long int)(r.y - q.y));
    long long int val =  (long long int)(first - second);
    return (val == 0)? 0: ((val > 0)? 1: 2);
}

bool doIntersect(struct Point p1,struct Point q1,struct Point p2,struct Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4)
    {
        return true;
    }
 
    if ((o1 == 0 && onSegment(p1, p2, q1)) ||
        (o2 == 0 && onSegment(p1, q2, q1)) ||
        (o3 == 0 && onSegment(p2, p1, q2)) ||
        (o4 == 0 && onSegment(p2, q1, q2)))
    {
        return true;
    }
    else
    { 
        return false;
    }
}
 
char* solve(int x1, int y1, int x2, int y2, int xm, int ym) {
    struct Point p1 = {x1, y1};
    struct Point q1 = {x2, y2};
    struct Point pm = {xm, ym};
    struct Point Zero = {0, 0};
    return((doIntersect(Zero, pm, p1, q1)) ? "NO" : "YES");
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int x1 = parse_int(*(first_multiple_input + 0));

        int y1 = parse_int(*(first_multiple_input + 1));

        int x2 = parse_int(*(first_multiple_input + 2));

        int y2 = parse_int(*(first_multiple_input + 3));

        int xm = parse_int(*(first_multiple_input + 4));

        int ym = parse_int(*(first_multiple_input + 5));

        char* result = solve(x1, y1, x2, y2, xm, ym);

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
