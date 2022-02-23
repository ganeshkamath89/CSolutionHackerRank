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
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */

/* Global Variables*/
int *heap_array = NULL;
int heap_max_size = 0;
int heap_current_size = 0;

#define SIZE_OF_BLOCK_ALLOCATION  1000 

void heap_heapify_from_top (int counter) {
    int temp_val = 0;
    int child_counter;
    int has_left_child = 0;
    int has_right_child = 0;

    if ((2 * counter + 1) < heap_current_size)
        has_left_child = 1;

    if ((2 * counter + 2) < heap_current_size)
        has_right_child = 1;

    /* Now, let us find the lowest of the two children */
    if (has_left_child && has_right_child) {
        if (heap_array[2* counter + 1] < heap_array[2*counter + 2])
            child_counter = 2 * counter + 1;
        else
            child_counter = 2 * counter + 2;
    } else if (has_left_child) {
        child_counter = 2 * counter + 1;
    } else if (has_right_child) {
        child_counter = 2 * counter + 2;
    } else {
        return;
    }

    if (heap_array[counter] > heap_array[child_counter]) {
        temp_val = heap_array[counter];
        heap_array[counter] = heap_array[child_counter];
        heap_array[child_counter] = temp_val;
        heap_heapify_from_top(child_counter);
    }
    return;
}

int heap_extract () {
    int t = 0;
    if (heap_current_size == 0) {
        printf("The heap is empty\n");
        return -1;
    }

    t = heap_array[0];
    heap_array[0] = heap_array[heap_current_size-1];
    heap_current_size--;

    if (heap_current_size != 1) {
        heap_heapify_from_top(0);
    }
    return t;
}

 void heap_insert_heapify_from_bottom (int counter) {
     int parent = (int) floor((double)(counter-1)/2);
     int temp_val;

     if (counter == 0) {
         return;
     }

     if (heap_array[parent] > heap_array[counter]) {
         temp_val = heap_array[counter];
         heap_array[counter] = heap_array[parent];
         heap_array[parent] = temp_val;
     }

     heap_insert_heapify_from_bottom(parent);
 }

 int heap_add (int value) {
     if (heap_current_size == heap_max_size) {
         heap_max_size += SIZE_OF_BLOCK_ALLOCATION;
         heap_array = (void*)realloc(heap_array,
                         heap_max_size * sizeof(int));
         if (!heap_array) {
             printf("realloc failed\n");
             return -1;
         }
     }
     heap_array[heap_current_size] = value;
     heap_insert_heapify_from_bottom(heap_current_size);
     heap_current_size++;
     return 0;
 }

int cookies(int k, int A_count, int* A) {
    int i, temp=0, temp2=0, num_oper=0, temp_k;
    bool no_entry_with_max = true;
    for (int i = 0; i <A_count; i++) {
        heap_add(A[i]);
    }
        temp = heap_extract();
    if (temp >= k) {
        printf("0\n");
        return 0;
    }
    while (temp < k && heap_current_size) {
        temp2 = heap_extract();
        temp_k = temp + 2 * temp2;
        num_oper += 1;
        heap_add(temp_k);
        if (temp_k >= k) {
            no_entry_with_max = false;
        }
        temp = heap_extract();
    }
    if (no_entry_with_max == true) {
        return -1;
    } else {
        return(num_oper);
    }
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** A_temp = split_string(rtrim(readline()));

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int A_item = parse_int(*(A_temp + i));

        *(A + i) = A_item;
    }

    int result = cookies(k, n, A);

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
