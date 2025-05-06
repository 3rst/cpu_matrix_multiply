//Submatrix is 3x3, total 15 double registers are used
void dgemm3(double *C,double *A,double *B,int n)
{
     int i,j,k;
     for (i = 0; i < n; i += 3)
          for (j = 0; j < n; j += 3)
          {
               register int row1 = i*n+j;
               
               register double c00 = C[row1];
               register double c01 = C[row1+1];
               register double c02 = C[row1+2];
               register double c10 = C[row1+n];
               register double c11 = C[row1+n+1];
               register double c12 = C[row1+n+2];
               register double c20 = C[row1+n+n];
               register double c21 = C[row1+n+n+1];
               register double c22 = C[row1+n+n+2];

               for (k = 0; k < n; k++)               //Skipping k will just be linear loop unrolling and will not contribute to performance gains, hence we iterate through k one by one
               {
                    register int r1 = i*n + k;       //i,k
                    register int c1 = k*n + j;       //k,j

                    register double a00 = A[r1];     //i,k
                    register double a10 = A[r1+n];   //i+1,k
                    register double a20 = A[r1+n+n]; //i+2,k

                    register double b00 = B[c1];     //k,j
                    register double b01 = B[c1+1];   //k,j+1
                    register double b02 = B[c1+2];   //k,j+2

                    c00 += a00*b00;
                    c01 += a00*b01;
                    c02 += a00*b02;
                    c10 += a10*b00;
                    c11 += a10*b01;
                    c12 += a10*b02;
                    c20 += a20*b00;
                    c21 += a20*b01;
                    c22 += a20*b02;
               }
               C[row1]=c00;
               C[row1+1]=c01;
               C[row1+2]=c02;
               C[row1+n]=c10;
               C[row1+n+1]=c11;
               C[row1+n+2]=c12;
               C[row1+n+n]=c20;
               C[row1+n+n+1]=c21;
               C[row1+n+n+2]=c22;
          }
}


// Submatrix is 4x2, total 14 registers are used
// void dgemm3(double *C,double *A,double *B,int n)
// {
//      int i,j,k;
//      for (i = 0; i < n; i += 4)
//           for (j = 0; j < n; j += 2)
//           {
//                register int row1 = i*n+j;
//                //Divide it into multiple 3x3 matrices, 9 registers are used here
//                register double c00 = C[row1];
//                register double c01 = C[row1+1];
//                register double c10 = C[row1+n];
//                register double c11 = C[row1+n+1];
//                register double c20 = C[row1+n+n];
//                register double c21 = C[row1+n+n+1];
//                register double c30 = C[row1+n+n+n];
//                register double c31 = C[row1+n+n+n+1];

//                for (k = 0; k < n; k++)         //Skipping k will just be linear loop unrolling and will not contribute to performance gains, hence we iterate through k one by one
//                {
//                     register int r1 = i*n + k; //i,k
//                     register int c1 = k*n + j; //k,j

//                     register double a00 = A[r1];     //i,k
//                     register double a10 = A[r1+n];   //i+1,k
//                     register double a20 = A[r1+n+n]; //i+2,k
//                     register double a30 = A[r1+n+n+n];

//                     register double b00 = B[c1];     //k,j
//                     register double b01 = B[c1+1];   //k,j+1

//                     c00 += a00*b00;
//                     c01 += a00*b01;
//                     c10 += a10*b00;
//                     c11 += a10*b01;
//                     c20 += a20*b00;
//                     c21 += a20*b01;
//                     c30 += a30*b00;
//                     c31 += a30*b01;
//                }
//                C[row1]=c00;
//                C[row1+1]=c01;
//                C[row1+n]=c10;
//                C[row1+n+1]=c11;
//                C[row1+n+n]=c20;
//                C[row1+n+n+1]=c21;
//                C[row1+n+n+n]=c30;
//                C[row1+n+n+n+1]=c31;
//           }
// }

//Submatrix is 2x4, 14 registers are used
// void dgemm3(double *C,double *A,double *B,int n)
// {
//      int i,j,k;
//      for (i = 0; i < n; i += 2)
//           for (j = 0; j < n; j += 4)
//           {
//                register int row1 = i*n+j;
               
//                //Divide it into multiple 3x3 matrices, 9 registers are used here
//                register double c00 = C[row1];
//                register double c01 = C[row1+1];
//                register double c02 = C[row1+2];
//                register double c03 = C[row1+3];
//                register double c10 = C[row1+n];
//                register double c11 = C[row1+n+1];
//                register double c12 = C[row1+n+2];
//                register double c13 = C[row1+n+3];

//                for (k = 0; k < n; k++)         //Skipping k will just be linear loop unrolling and will not contribute to performance gains, hence we iterate through k one by one
//                {
//                     register int r1 = i*n + k; //i,k
//                     register int c1 = k*n + j; //k,j

//                     register double a00 = A[r1];     //i,k
//                     register double a10 = A[r1+n];   //i+1,k

//                     register double b00 = B[c1];     //k,j
//                     register double b01 = B[c1+1];   //k,j+1
//                     register double b02 = B[c1+2];   //k,j+2
//                     register double b03 = B[c1+3];   //k,j+3

//                     c00 += a00*b00;
//                     c01 += a00*b01;
//                     c02 += a00*b02;
//                     c03 += a00*b03;
//                     c10 += a10*b00;
//                     c11 += a10*b01;
//                     c12 += a10*b02;
//                     c13 += a10*b03;
//                }
//                C[row1] = c00;
//                C[row1+1] = c01;
//                C[row1+2] = c02;
//                C[row1+3] = c03;
//                C[row1+n] = c10;
//                C[row1+n+1] = c11;
//                C[row1+n+2] = c12;
//                C[row1+n+3] = c13;
//           }
// }