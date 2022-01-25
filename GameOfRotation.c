#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int n = 0;
    scanf("%d", &n);
    
    int*a = (int*)malloc(n*sizeof(int));
    
    long long sum = 0;
    for(int i = 0; i<n; i++)
    {
        scanf("%d", &a[i]);        
        sum += a[i];
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans += (long long) (i + 1) * a[i];

    long long maxSum = ans;
    for (int i = 0; i < n; i++)
    {
        ans -= sum;
        ans += (long long) n * a[i];
        if (ans > maxSum)
          maxSum = ans;
    }
    printf("%lld", maxSum);
    return 0;
}
