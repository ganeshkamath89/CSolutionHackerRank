#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// Complete the solve function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//
typedef long long ll;

ll gcd(ll a, ll b)
{
    if(a < 0)
    {
        a = -a;
    }
    if(b < 0)
    {
        b = -b;
    }
    return b ? gcd(b, a % b) : a;
}

ll* solve(ll a_count, ll* a, ll queries_count, ll* queries, ll* result_count, ll d) {
    *result_count = queries_count;
    ll* result = (ll*)malloc(queries_count*sizeof(ll));
    for(ll i = 0; i< queries_count; i++)
    {
        result[i] = gcd(d, a[0] + queries[i]);
    }
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nq = split_string(readline());

    char* n_endptr;
    char* n_str = nq[0];
    ll n = strtoll(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* q_endptr;
    char* q_str = nq[1];
    ll q = strtoll(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '\0') { exit(EXIT_FAILURE); }

    char** a_temp = split_string(readline());
    ll* a = (ll*)malloc(n * sizeof(ll));
    for (ll i = 0; i < n; i++) {
        char* a_item_endptr;
        char* a_item_str = *(a_temp + i);
        ll a_item = strtoll(a_item_str, &a_item_endptr, 10);
        if (a_item_endptr == a_item_str || *a_item_endptr != '\0') { exit(EXIT_FAILURE); }
        *(a + i) = a_item;
    }

    int a_count = n;
    ll* queries = malloc(q * sizeof(ll));
    for (int i = 0; i < q; i++) {
        char* queries_item_endptr;
        char* queries_item_str = readline();
        ll queries_item = strtol(queries_item_str, &queries_item_endptr, 10);

        if (queries_item_endptr == queries_item_str || *queries_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(queries + i) = queries_item;
    }

    ll queries_count = q;    
    ll d = 0;
    for(ll i = 0; i < queries_count; ++i)
    {
        d = gcd(d, a[i] - a[1]);
    }

    ll result_count;
    ll* result = solve(a_count, a, queries_count, queries, &result_count, d);
    for (ll i = 0; i < result_count; i++) {
        fprintf(fptr, "%llu", *(result + i));
        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }
    fprintf(fptr, "\n");
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
