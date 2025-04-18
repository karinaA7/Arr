#include <stdio.h>
#include "newarr.h"

int main() {
    // совпадают
    int row1_1[] = {1, 2}; // first stroka 1 massiva
    int row1_2[] = {2, 1}; // second 1 mass
    int* A1[] = {row1_1, row1_2};
    int sizes1[] = {2, 2}; // len 1 i 2 stroki massiva
    
    int row2_1[] = {2, 1};
    int row2_2[] = {1, 2};
    int* A2[] = {row2_1, row2_2};
    int sizes2[] = {2, 2};
    
    printf("Matching arrays - (true): %s\n", arrays_match_bidirectional(A1, sizes1, 2, A2, sizes2, 2) ? "true" : "false");
    
    // совпадают
    int row3_1[] = {1, 2, 3};
    int row3_2[] = {2, 1};
    int* A3[] = {row3_1, row3_2};
    int sizes3[] = {3, 2};
    
    int row4_1[] = {1, 2};
    int row4_2[] = {3, 1, 2};
    int* A4[] = {row4_1, row4_2};
    int sizes4[] = {2, 3};
    
    printf("Matching jagged arrays - (true): %s\n", arrays_match_bidirectional(A3, sizes3, 2, A4, sizes4, 2) ? "true" : "false");
    
    // не совпадают
    int row5_1[] = {1, 2};
    int row5_2[] = {2, 1};
    int* A5[] = {row5_1, row5_2};
    int sizes5[] = {2, 2};
    
    int row6_1[] = {2};
    int row6_2[] = {1, 2};
    int* A6[] = {row6_1, row6_2};
    int sizes6[] = {1, 2};
    
    printf("Dont match(1- ok, 2 - jugged) - (false): %s\n", arrays_match_bidirectional(A5, sizes5, 2, A6, sizes6, 2) ? "true" : "false");
    
    // не совпадают
    int row7_1[] = {1, 2, 3};
    int row7_2[] = {2, 1};
    int* A7[] = {row7_1, row7_2};
    int sizes7[] = {3, 2};
    
    int row8_1[] = {3, 2, 1};
    int row8_2[] = {2, 1};
    int row8_3[] = {2, 1};
    int* A8[] = {row8_1, row8_2, row8_3};
    int sizes8[] = {3, 2, 2};
    
    printf("Different number of rows - (false): %s\n", arrays_match_bidirectional(A7, sizes7, 2, A8, sizes8, 3) ? "true" : "false");
    
    // true
    int** empty1 = NULL;
    int* empty_sizes1 = NULL;
    int** empty2 = NULL;
    int* empty_sizes2 = NULL;
    printf("Both are empty - (true): %s\n", arrays_match_bidirectional(empty1, empty_sizes1, 0, empty2, empty_sizes2, 0) ? "true" : "false");

    // false
    int row1[] = {1};
    int* non_empty[] = {row1};
    int sizes[] = {1};
    printf("One is empty, other is not - (false): %s\n", arrays_match_bidirectional(non_empty, sizes, 1, empty2, empty_sizes2, 0) ? "true" : "false");

    // true
    int* zero_row1 = NULL;
    int* zero_row2 = NULL;
    int* A9[] = {zero_row1};
    int* A10[] = {zero_row2};
    int zero_sizes[] = {0};
    printf("Both rows have a size of 0 - (true): %s\n", arrays_match_bidirectional(A9, zero_sizes, 1, A10, zero_sizes, 1) ? "true" : "false");
     
    // false
    int row1_n[] = {1, 2};
    int* testA1_1[] = {row1_n};
    int bad_sizes1[] = {-1}; // отрицательный размер
    int* testA1_2[] = {row1_n}; 
    int good_sizes2[] = {2};
    
    printf("Negative size A1 - (false): %s\n", arrays_match_bidirectional(testA1_1, bad_sizes1, 1, testA1_2, good_sizes2, 1) ? "true" : "false"); // должно быть false

    // false
    int row2_n[] = {3, 4};
    int* testA2_1[] = {row2_n};
    int good_sizes1[] = {2};
    int* testA2_2[] = {row2_n};
    int bad_sizes2[] = {-5}; // отрицательный размер
    
    printf("Negative size A2 - (false): %s\n", arrays_match_bidirectional(testA2_1, good_sizes1, 1, testA2_2, bad_sizes2, 1) ? "true" : "false"); // должно быть false

    // false
    int row_dup1[] = {1, 1}; 
    int row_dup2[] = {1};
    int* A11[] = {row_dup1};
    int* A12[] = {row_dup2};
    int sizes_dup[] = {2, 1};
    printf("Dplicates - (false): %s\n", arrays_match_bidirectional(A11, sizes_dup, 1, A12, sizes_dup, 1) ? "true" : "false"); // false

    // true
    int* A13[] = {NULL};
    int* A14[] = {NULL};
    int zero_sizes2[] = {0};
    printf("Null rows with 0 size - (true): %s\n", arrays_match_bidirectional(A13, zero_sizes2, 1, A14, zero_sizes2, 1) ? "true" : "false"); // true

    return 0;
} 
