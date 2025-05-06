void dgemm2(double *C,double *A,double *B,int n)
{
     int i,j,k;
     for (i = 0; i < n; i += 2)
          for (j = 0; j < n; j += 2)
          {
               int row1 = i*n+j;
               register double c00 = C[row1];
               register double c01 = C[row1+1];
               register double c10 = C[row1+n];
               register double c11 = C[row1+n+1];

               for (k = 0; k < n; k += 2)
               {
                    // printf("Accessing indices: i=%d,%d, j=%d,%d, k=%d,%d\n", i, i+1, j, j+1, k, k+1);
                    register int r1 = i*n + k; //i,k
                    register int c1 = k*n + j; //k,j

                    register double a00 = A[r1];
                    register double a01 = A[r1+1];
                    register double a10 = A[r1+n];
                    register double a11 = A[r1+n+1];

                    register double b00 = B[c1];
                    register double b01 = B[c1+1];
                    register double b10 = B[c1+n];
                    register double b11 = B[c1+n+1];

                    // printf("register values: a00=%f, a01=%f, a10=%f, a11=%f, b00=%f, b01=%f, b10=%f, b11=%f\n",a00,a01,a10,a11,b00,b01,b10,b11);

                    c00 += a00*b00 + a01*b10;
                    c01 += a00*b01 + a01*b11;
                    c10 += a10*b00 + a11*b10;
                    c11 += a10*b01 + a11*b11;
                    // printf("final values: c00=%f, c01=%f, c10=%f,c11=%f\n", c00,c01,c10,c11);
               }
               C[row1]=c00;
               C[row1+1]=c01;
               C[row1+n]=c10;
               C[row1+n+1]=c11;
          }
}