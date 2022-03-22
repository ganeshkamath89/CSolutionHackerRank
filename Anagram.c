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
 * Complete the 'anagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */
 
 void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char* arr, int beg, int end)
{
    char pivot = arr[end];
    int partitionIndex = beg - 1;
    for(int i = beg; i<=(end - 1); i++)
    {
        if (arr[i] < pivot)
        {
            partitionIndex++;
            swap(&arr[i], &arr[partitionIndex]);
        }
    }
    swap(&arr[end], &arr[partitionIndex+1]);
    return partitionIndex + 1;
}

void quick_sort(char* arr, int beg, int end)
{
    if (beg < end)
    {
        int partitionIndex = partition(arr, beg, end);
        quick_sort(arr, beg, partitionIndex - 1);
        quick_sort(arr, partitionIndex + 1, end);
    }
}

int anagram(char* s) {
    int len = strlen(s);
    int half = len/2;
    int freq1[26] = {0}, freq2[26] = {0};
    
    for(int i = 0; i<len; i++)
    {
        int index = s[i] - 'a';
        if (i < half)
        {
            freq1[index]++;
        }
        else
        {
            freq2[index]++;
        }
    }
    
    int count = 0, diff = 0;
    for(int i = 0; i<26; i++)
    {
        int f1 = freq1[i], f2 = freq2[i];
        if (f1 >0 || f2>0)
        {
            diff = f1 > f2 ? f1 - f2 : f2 - f1;
            count+=diff;   
        }
    }
    return (count%2 == 1 ? -1 : count / 2);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* s = readline();

        int result = anagram(s);

        fprintf(fptr, "%d\n", result);
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
