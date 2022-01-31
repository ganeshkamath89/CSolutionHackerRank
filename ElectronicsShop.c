#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

/*
 * Complete the getMoneySpent function below.
 */
long getMoneySpent(long keyboards_count, long* keyboards, long drives_count, long* drives, long b) {
    /*
     * Write your code here.
     */
    long max = 0;
    bool isSet = false;
    for(long i = 0; i<keyboards_count; i++)
    {
        for(long j = 0; j<drives_count; j++)
        {
            long sum = keyboards[i] + drives[j];
            if (max < sum && sum <=b)
            {
                isSet = true;
                max = sum;
            }
        }
    }
    return isSet ? max : -1;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** bnm = split_string(readline());

    char* b_endptr;
    char* b_str = bnm[0];
    long b = strtol(b_str, &b_endptr, 10);

    if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = bnm[1];
    long n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* m_endptr;
    char* m_str = bnm[2];
    long m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char** keyboards_temp = split_string(readline());

    long* keyboards = malloc(n * sizeof(long));

    for (long keyboards_itr = 0; keyboards_itr < n; keyboards_itr++) {
        char* keyboards_item_endptr;
        char* keyboards_item_str = *(keyboards_temp + keyboards_itr);
        long keyboards_item = strtol(keyboards_item_str, &keyboards_item_endptr, 10);

        if (keyboards_item_endptr == keyboards_item_str || *keyboards_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(keyboards + keyboards_itr) = keyboards_item;
    }

    long keyboards_count = n;

    char** drives_temp = split_string(readline());

    long* drives = malloc(m * sizeof(long));

    for (long drives_itr = 0; drives_itr < m; drives_itr++) {
        char* drives_item_endptr;
        char* drives_item_str = *(drives_temp + drives_itr);
        long drives_item = strtol(drives_item_str, &drives_item_endptr, 10);

        if (drives_item_endptr == drives_item_str || *drives_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(drives + drives_itr) = drives_item;
    }

    long drives_count = m;

    /*
     * The maximum amount of money she can spend on a keyboard and USB drive, or -1 if she can't purchase both items
     */

    long moneySpent = getMoneySpent(keyboards_count, keyboards, drives_count, drives, b);

    fprintf(fptr, "%ld\n", moneySpent);

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

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
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
