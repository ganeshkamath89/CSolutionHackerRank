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

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
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
char* timeConversion(char* s) {
    int strlenS = strlen(s);
    char* time = (char*)calloc(9, sizeof(char));
    bool isAM = (s[strlenS - 2] == 'A');
    printf("%s\n", isAM ? "YES" : "NO");
    for (int i = 0; i < 8; i++)
    {
        time[i] = s[i];
    }
    if (isAM)
    {
        if (time[0] == '1' && time[1] == '2')
        {
            time[0] = '0';
            time[1] = '0';
            return time;
        }
        else
        {
            return time;
        }
    }
    else
    {
        if (time[0] == '1')
        {
            if (time[1] == '0')
            {
                time[0] = '2';
                time[1] = '2';
                return time;
            }
            else if (time[1] == '1')
            {
                time[0] = '2';
                time[1] = '3';
                return time;
            }
            else if (time[1] == '2')
            {
                time[0] = '1';
                time[1] = '2';
                return time;
            }
        }
        else
        {
            if (time[1] == '1')
            {
                time[0] = '1';
                time[1] = '3';
                return time;
            }
            else if (time[1] == '2')
            {
                time[0] = '1';
                time[1] = '4';
                return time;
            }
            else if (time[1] == '3')
            {
                time[0] = '1';
                time[1] = '5';
                return time;
            }
            else if (time[1] == '4')
            {
                time[0] = '1';
                time[1] = '6';
                return time;
            }
            else if (time[1] == '5')
            {
                time[0] = '1';
                time[1] = '7';
                return time;
            }
            else if (time[1] == '6')
            {
                time[0] = '1';
                time[1] = '8';
                return time;
            }
            else if (time[1] == '7')
            {
                time[0] = '1';
                time[1] = '9';
                return time;
            }
            else if (time[1] == '8')
            {
                time[0] = '2';
                time[1] = '0';
                return time;
            }
            else if (time[1] == '9')
            {
                time[0] = '2';
                time[1] = '1';
                return time;
            }
        }
    }
    return time;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = timeConversion(s);

    fprintf(fptr, "%s\n", result);

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
