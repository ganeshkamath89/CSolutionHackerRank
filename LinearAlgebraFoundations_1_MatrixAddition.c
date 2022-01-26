#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int r, c, i, j;
    int a[3][3] = {
        {1,2,3},
        {2,3,4},
        {1,1,1}
    }, b[3][3] = {
        {4,5,6},
        {7,8,9},
        {4,5,7}
    }, sum[3][3];

    r = 3, c = 3;

  // adding two matrices
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j) {
      sum[i][j] = a[i][j] + b[i][j];
    }

  // printing the result
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j) {
      printf("%d\n", sum[i][j]);
    }

  return 0;
}
