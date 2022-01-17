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
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER r
 *  3. INTEGER m
 */

typedef long long LL;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

LL binomial_coefficient(int n, int k)
{
    if(n < k) return 0;
    LL ans = 1;
    k = k < (n - k) ? k : (n - k);
    for(int i = 1; i <= k; i++,n--)
    {
        if(n % i == 0)
        {
            ans *= n/i;
        }
        else if(ans % i == 0)
        {
            ans = (ans / i) * n;
        }
        else
        {
            ans = (ans * n)/i;
        }
    }
    return ans;
}

LL lucas_theorem(int n, int k, int p)
{
    LL ans = 1;
    while(k > 0)
    {
        int tmp_n = n % p;
        int tmp_k = k % p;
        ans *= binomial_coefficient(tmp_n, tmp_k) % p;
        ans %= p;
        n /= p;
        k /= p;
    }
    return ans;
}

LL get_reminder_squarefree(int n, int k, int m)
{
    LL ans = -1;
    LL last = 1;
    int primes_length = sizeof(primes)/sizeof(int);

    if(m == 1) return 0;

    for(int i = 0; i < primes_length && m > 1; i++)
    {
        if(m % primes[i] != 0)
        {
            continue;
        }
        LL rem = lucas_theorem(n, k, primes[i]);
        if(ans == -1)
        {
            ans = rem;
        }
        else
        {
            for(int j = 0; j < 50; j++)
            {
                if( (ans + (last * j)) % primes[i] == rem)
                {
                    ans = (ans + (last * j));
                    break;
                }
            }
        }
        last *= primes[i];
        m /= primes[i];
    }
    return ans;
}

int solve(int n, int r, int m) {
    return get_reminder_squarefree(n, r, m);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int r = parse_int(*(first_multiple_input + 1));

        int m = parse_int(*(first_multiple_input + 2));

        int result = solve(n, r, m);

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
