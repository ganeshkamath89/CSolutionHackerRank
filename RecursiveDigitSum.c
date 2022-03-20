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
 * Complete the 'superDigit' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING n
 *  2. INTEGER k
 */

/*
// Alternatively we can multiply by K after finding sum on one string digit to minimize computation
int superDigit(char* n, int k) {
    long sumN = 0;
    for(long i = 0; i< strlen(n); i++)
    {
        if (n[i]>='0' && n[i]<='9')
        {
            sumN += n[i] - '0';
        }
    }    
    long smallSum = 0;
    while(sumN > 0)
    {
        smallSum += sumN%10; 
        sumN /= 10;
        if (sumN ==0 && smallSum > 9)
        {
            sumN = smallSum;
            smallSum = 0;
        }
    }
    sumN = smallSum*k;
    smallSum = 0;
    while(sumN > 0)
    {
        smallSum += sumN%10; 
        sumN /= 10;
        if (sumN ==0 && smallSum > 9)
        {
            sumN = smallSum;
            smallSum = 0;
        }
    }
    return smallSum;
}
*/
 
int superDigit(char* n, long k) {
    long len = strlen(n);
    long sum = 0;
    for(int i = 0; i<len; i++)
    {
        sum = sum + n[i] - '0';
    }
    sum *= k;
    
    while(sum > 10)
    {
        int temp = 0;
        while (sum > 0)
        {
            temp += sum % 10;
            sum = sum / 10;
        }
        sum = temp;
    }
    return sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    char* n = *(first_multiple_input + 0);
    char* eptr;
    long k = strtol(*(first_multiple_input + 1), &eptr, 10);

    int result = superDigit(n, k);

    fprintf(fptr, "%d\n", result);

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
