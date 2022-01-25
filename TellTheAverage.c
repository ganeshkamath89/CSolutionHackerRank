#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef unsigned long long ull;
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    ull n = 0;
    ull a = 0, b = 0;
    scanf("%llu", &n);
    for(ull i = 0; i<n; i++)
    {
        scanf("%llu", &b);
        a = a + b + a*b%1000000007;
    }
    printf("%llu", a%1000000007);
    return 0;
}
