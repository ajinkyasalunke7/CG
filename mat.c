#include <stdio.h>

void PrintMatrix(int given_array[3][3], int range);

int main() {
   int input[3][3];
   int transaltion_mat[3][3];
   int tx, ty, output[3][3];

   printf("Enter elements for matrix A (3x3) representing points in homogeneous coordinates:\n");
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         // printf("%d %d", i, j);
         if (i == 2) {
            input[2][j] = 1;
         } else {
            printf("Enter element A[%d][%d]: ", i, j);
            scanf("%d", & input[i][j]);
         }
      }
   }

   		/*  if ((i == 0 | i == 1 | i == 2) && j == 2) {
            input[i][j] = 1;
         } else {
            printf("Enter element A[%d][%d]: ", i, j);
            scanf("%d", & input[i][j]);
         }
         */

   printf("Enter translation factor of X: ");
   scanf("%d", & tx);
   printf("Enter translation factor of Y: ");
   scanf("%d", & ty);

   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         if (i == j) {
            transaltion_mat[i][j] = 1;
         } else {
            transaltion_mat[i][j] = 0;
         }
      }
   }
   transaltion_mat[0][2] = tx;
   transaltion_mat[1][2] = ty;

   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         output[i][j] = 0;
         for (int k = 0; k < 3; k++) {
            output[i][j] = output[i][j] + transaltion_mat[i][k] * input[k][j];
         }
      }
   }

   PrintMatrix(input, 3);
   PrintMatrix(transaltion_mat, 3);
   PrintMatrix(output, 3);

   return 0;
}

void PrintMatrix(int given_array[3][3], int range) {
   for (int i = 0; i < range; i++) {
      for (int j = 0; j < range; j++) {
         printf("%d \t", given_array[i][j]);
      }
      printf("\n");
   }
}