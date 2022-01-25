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
 *  1. INTEGER_ARRAY balls
 *  2. INTEGER k
 */

typedef long long LL;


#define MAXN 100005
#define MOD 1000000007

int N,K,a[MAXN] = {0};
long long fact[MAXN] = {0},inv_fact[MAXN] = {0};

int mod_pow(long long a, int b){
    long long ret = 1;    
    while(b){
        if(b & 1)
        {
            ret = ret * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }    
    return ret;
}

long long comb(int n, int m){
    return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int array[], int low, int high)
{
  int pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pivot = partition(array, low, high);
    quickSort(array, low, pivot - 1);
    quickSort(array, pivot + 1, high);
  }
}

LL solve(int n, int* a, int k) {    

    quickSort(a,0,n-1);
    int N = n, K = k;
    
    fact[0] = inv_fact[0] = 1;
    
    for(int i = 1;i <= N;++i){
        fact[i] = fact[i - 1] * i % MOD;
        inv_fact[i] = mod_pow(fact[i],MOD - 2);
    }
    
    int ans = 0;
    
    for(int i = 0;i < N;){
        int e = i;
        
        while(e < N && a[e] == a[i]) ++e;
        
        if(e >= K)
            ans = (ans + (comb(e,K) - comb(i,K)) * a[i]) % MOD;
        
        i = e;
    }
    
    for(int i = N - 1;i >= 0;){
        int e = i;
        
        while(e >= 0 && a[e] == a[i]) --e;
        
        if(N - 1 - e >= K)
            ans = (ans - (comb(N - 1 - e,K) - comb(N - 1 - i,K)) * a[i]) % MOD;
        
        i = e;
    }
    
    if(ans < 0) ans += MOD;
    return ans;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** balls_temp = split_string(rtrim(readline()));

    int* balls = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int balls_item = parse_int(*(balls_temp + i));

        *(balls + i) = balls_item;
    }

    LL result = solve(n, balls, k);

    fprintf(fptr, "%lld\n", result);

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
