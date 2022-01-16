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
 * The function accepts 2D_INTEGER_ARRAY dates as parameter.
 */

long long solve(long long dates_rows, long long dates_columns, long long** dates) {    
   // long long cnt[100000] = {0};    
    long long* cnt = (long long*)malloc(100000*sizeof(long long));
    memset(cnt, '\0', 100000);
    
    for(long long i = 0; i< dates_rows; i++)
    {
        long long m = dates[i][0];
        long long d = dates[i][1];
        
        long long tmp = d;
        bool valid = true;
        while (tmp)
        {
            if (tmp % 10 >= m)
            {
                valid = false;
            }
            tmp /= 10;
        }
        if (!valid)
        {
            continue;
        }
        long long val = 0;
        tmp = d;
        long long tt = 1;
        while (tmp)
        {
            val += (tmp % 10) * tt;
            tt *= m;
            tmp /= 10;
        }
        cnt[val]++;
    }
    
    long long ans = 0;
    for (long long i = 0; i < 100000; i++)
    {
        ans += cnt[i] * (cnt[i] - 1) / 2;
    }
    printf("%llu", ans);
    return ans;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    char* eptr;
    long long n = strtoll(ltrim(rtrim(readline())), &eptr, 10);
    long long** dates = (long long**) malloc(n * sizeof(long long*));

    for (long long i = 0; i < n; i++) {
        *(dates + i) = malloc(2 * (sizeof(long long)));
        char** dates_item_temp = split_string(rtrim(readline()));
        for (long long j = 0; j < 2; j++) {
            long long dates_item = parse_int(*(dates_item_temp + j));
            *(*(dates + i) + j) = dates_item;
        }
    }

    long long result = solve(n, 2, dates);

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
