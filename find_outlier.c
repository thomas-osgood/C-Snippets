#include <stdlib.h>

int find_outlier(const int *values, size_t count);
int find_odd_even(const int *values, size_t count);

int find_outlier(const int *values, size_t count) {
    int outlier = 0;
    int odd_even = 0; // 0 = even, 1 = odd
    int i = 0;
    int curr = 0;
    
    odd_even = find_odd_even(values,count);
    
    if ( (values[0] % 2) != odd_even)
        return values[0];
    
    //printf("Array Is: %d | Size: %d\n", odd_even, count);
    
    for (i = 0; i < count; i++) {
        curr = (abs(values[i])%2);
        if (curr != odd_even) {
            outlier = values[i];
        }
    }
    return outlier;
}

int find_odd_even(const int *values, size_t count) {
    int result = 0;
    
    if ((values[0]%2) == 1) {
        if (((values[1]%2) == 1) || ((values[2]%2) == 1)) {
          result = 1; 
        } else {
          result = 0;
        }
    }
    
    if ((values[0]%2) == 0) {
        if (((values[1]%2) == 0) || ((values[2]%2) == 0)) {
          result = 0; 
        } else {
          result = 1;
        }
    }
    
    return result;
}
