#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  char buf[1000000] = {0};
  int n = 0, k = 0;
  scanf("%d", &n);
  char **undos = (char**)calloc(sizeof(char *), n);
  undos[k] = (char *)malloc(sizeof(char));
  strcpy(undos[k], "");
  while (n > 0) {
    int option = 0;
    scanf("%d", &option);
        switch (option) {
            case 1:
            {
                scanf("%1000000s\n", buf);
                ++k;
                undos[k] = (char*)malloc(sizeof(char) * (strlen(undos[k - 1]) + strlen(buf) + 1));
                strcpy(undos[k], undos[k - 1]);
                strcat(undos[k], buf);
            }
            break;
            case 2:
            {
                int input = 0;
                scanf("%d", &input);
                ++k;
                undos[k] = (char*)malloc(sizeof(char) * (strlen(undos[k - 1]) - input + 1));
                size_t len = strlen(undos[k - 1]);
                memcpy(undos[k], undos[k - 1], strlen(undos[k - 1]) - input);
                undos[k][len - input] = 0;
            }
            break;
            case 3:
            {
                int input = 0;
                scanf("%d", &input);
                printf("%c\n", undos[k][input - 1]);
            }
            break;
            case 4:
            {
              --k;
            }
            break;
            default:
            break;
        }
        n--;
    }
    return 0;
}
