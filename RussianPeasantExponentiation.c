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
long parse_long(char*);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER a
 *  2. INTEGER b
 *  3. LONG_INTEGER k
 *  4. INTEGER m
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
typedef unsigned long long ull;

void mulcomp (ull a, ull b, ull c, ull d, ull *e, ull *f, ull MOD){
    *e = (((a%MOD)*(c%MOD))%MOD - ((b%MOD)*(d%MOD))%MOD + MOD)%MOD;
    *f = (((a%MOD)*(d%MOD))%MOD + ((b%MOD)*(c%MOD))%MOD)%MOD;
}

ull* f(ull real, ull img, ull exp, ull MOD) {
    real%=MOD; img%=MOD;
    ull *ptrReal = &real, *ptrImg = &img;
    ull ar = 1, ai = 0;
    ull* ptrAr = &ar, *ptrAi = &ai;
    while (exp > 0){
        if (exp & 1){
            mulcomp(ar, ai, real, img, ptrAr, ptrAi, MOD);
        }
        mulcomp(real, img, real, img, ptrReal, ptrImg, MOD);
        exp>>=1;
    }
    ull* pair = (ull *)malloc(2*sizeof(ull));
    pair[0] = ar;
    pair[1] = ai;
    return pair;
}
ull* solve(ull a, ull b, ull k, ull m, ull* result_count) { 
    * result_count = 2;   
    return f(a,b,k,m);
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    char* eptr;
    int q = parse_int(ltrim(rtrim(readline())));
    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));
        ull a = strtoull(*(first_multiple_input + 0),&eptr,10);
        ull b = strtoull(*(first_multiple_input + 1),&eptr,10);
        ull k = strtoull(*(first_multiple_input + 2),&eptr,10);
        ull m = strtoull(*(first_multiple_input + 3),&eptr,10);
        ull result_count;
        ull* result = solve(a, b, k, m, &result_count);
        for (ull i = 0; i < result_count; i++) {
            fprintf(fptr, "%llu", *(result + i));
            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }
        fprintf(fptr, "\n");
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

long parse_long(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
