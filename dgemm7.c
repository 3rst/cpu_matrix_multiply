// jik 4x4 register block
void dgemm7(double *C,double *A,double *B,int n)
{
    int i,j,k,ii,jj,kk;
    register int b=76;
    for(j=0;j<n;j+=b)
        for(i=0;i<n;i+=b)
            for(k=0;k<n;k+=b)
            {
                for(jj=j;jj<j+b;jj+=4)
                    for(ii=i;ii<i+b;ii+=4)
                    {
                        register int row1 = ii*n+jj;
               
                        register double c00 = C[row1];
                        register double c01 = C[row1+1];
                        register double c02 = C[row1+2];
                        register double c03 = C[row1+3];
                        register double c10 = C[row1+n];
                        register double c11 = C[row1+n+1];
                        register double c12 = C[row1+n+2];
                        register double c13 = C[row1+n+3];
                        register double c20 = C[row1+n+n];
                        register double c21 = C[row1+n+n+1];
                        register double c22 = C[row1+n+n+2];
                        register double c23 = C[row1+n+n+3];
                        register double c30 = C[row1+n+n+n];
                        register double c31 = C[row1+n+n+n+1];
                        register double c32 = C[row1+n+n+n+2];
                        register double c33 = C[row1+n+n+n+3];

                        for (kk = k; kk < k+b; kk++)                  //Skipping k will just be linear loop unrolling and will not contribute to performance gains, hence we iterate through k one by one
                        {
                                register int r1 = ii*n + kk;       //i,k
                                register int c1 = kk*n + jj;       //k,j

                                register double a00 = A[r1];     //i,k
                                register double a10 = A[r1+n];   //i+1,k
                                register double a20 = A[r1+n+n]; //i+2,k
                                register double a30 = A[r1+n+n+n];

                                register double b00 = B[c1];     //k,j
                                register double b01 = B[c1+1];   //k,j+1
                                register double b02 = B[c1+2];   //k,j+2
                                register double b03 = B[c1+3];

                                c00 += a00*b00;
                                c01 += a00*b01;
                                c02 += a00*b02;
                                c03 += a00*b03;
                                c10 += a10*b00;
                                c11 += a10*b01;
                                c12 += a10*b02;
                                c13 += a10*b03;
                                c20 += a20*b00;
                                c21 += a20*b01;
                                c22 += a20*b02;
                                c23 += a20*b03;
                                c30 += a30*b00;
                                c31 += a30*b01;
                                c32 += a30*b02;
                                c33 += a30*b03;
                        }
                        C[row1]=c00;
                        C[row1+1]=c01;
                        C[row1+2]=c02;
                        C[row1+3]=c03;
                        C[row1+n]=c10;
                        C[row1+n+1]=c11;
                        C[row1+n+2]=c12;
                        C[row1+n+3]=c13;
                        C[row1+n+n]=c20;
                        C[row1+n+n+1]=c21;
                        C[row1+n+n+2]=c22;
                        C[row1+n+n+3]=c23;
                        C[row1+n+n+n]=c30;
                        C[row1+n+n+n+1]=c31;
                        C[row1+n+n+n+2]=c32;
                        C[row1+n+n+n+3]=c33;
                    }
            }
}

//ikj 4x4 register block
// void dgemm7(double *C,double *A,double *B,int n)
// {
//     // complete the missing code here
//     //b=16 time = 6.839005
//     //b=20 time = 6.481803
//     //b=36, time = 6.331473
//     //b=44, time = 6.522208
//     //b=48, time = 6.434431
//     //b=52, time = 6.583137
//     //b=72, time = 6.565516

//     int i,j,k,ii,jj,kk;
//     register int b=36;
//     for(i=0;i<n;i+=b)
//         for(k=0;k<n;k+=b)
//             for(j=0;j<n;j+=b)
//             {
//                 for(ii=i;ii<i+b;ii+=4)
//                     for (kk = k; kk < k+b; kk+=4)
//                     {
//                         register int row1 = ii*n+kk;
               
//                         register double a00 = A[row1];
//                         register double a01 = A[row1+1];
//                         register double a02 = A[row1+2];
//                         register double a03 = A[row1+3];
//                         register double a10 = A[row1+n];
//                         register double a11 = A[row1+n+1];
//                         register double a12 = A[row1+n+2];
//                         register double a13 = A[row1+n+3];
//                         register double a20 = A[row1+n+n];
//                         register double a21 = A[row1+n+n+1];
//                         register double a22 = A[row1+n+n+2];
//                         register double a23 = A[row1+n+n+3];
//                         register double a30 = A[row1+n+n+n];
//                         register double a31 = A[row1+n+n+n+1];
//                         register double a32 = A[row1+n+n+n+2];
//                         register double a33 = A[row1+n+n+n+3];

//                         for(jj = j; jj < j+b; jj++)            //Skipping k will just be linear loop unrolling and will not contribute to performance gains, hence we iterate through k one by one
//                         {
//                             register int r1 = ii*n + jj;       //i,k
//                             register int c1 = kk*n + jj;       //k,j

//                             register double c00 = C[r1];       //i,j
//                             register double c10 = C[r1+n];     //i+1,j
//                             register double c20 = C[r1+n+n];   //i+2,j
//                             register double c30 = C[r1+n+n+n]; //i+3,j

//                             register double b00 = B[c1];       //k,j
//                             register double b10 = B[c1+n];     //k,j+1
//                             register double b20 = B[c1+n+n];   //k,j+2
//                             register double b30 = B[c1+n+n+n]; //k,j+3

//                             C[r1] += a00*b00 + a01*b10 + a02*b20 + a03*b30;
//                             C[r1+n] += a10*b00 + a11*b10 + a12*b20 + a13*b30;
//                             C[r1+n+n] += a20*b00 + a21*b10 + a22*b20 + a23*b30;
//                             C[r1+n+n+n] += a30*b00 + a31*b10 + a32*b20 + a33*b30;
//                         }
//                     }
//             }
// }

// jik 3x3 register block
// void dgemm7(double *C,double *A,double *B,int n)
// {
//     // complete the missing code here
//     //b=20 time = 7 seconds
//     //b=16 time = 7.2 seconds
//     //b=36, time = 6.8 seconds
//     //b=44, time = 6.6 seconds
//     //b=48, time = 6.1 seconds
//     //b=52, time = 6.6 seconds

//     int i,j,k,ii,jj,kk;
//     register int b=120;
//     for(j=0;j<n;j+=b)
//         for(i=0;i<n;i+=b)
//             for(k=0;k<n;k+=b)
//             {
//                 for(jj=j;jj<j+b;jj+=3)
//                     for(ii=i;ii<i+b;ii+=3)
//                     {
//                         register int row1 = ii*n+jj;
               
//                         register double c00 = C[row1];
//                         register double c01 = C[row1+1];
//                         register double c02 = C[row1+2];
//                         // register double c03 = C[row1+3];
//                         register double c10 = C[row1+n];
//                         register double c11 = C[row1+n+1];
//                         register double c12 = C[row1+n+2];
//                         // register double c13 = C[row1+n+3];
//                         register double c20 = C[row1+n+n];
//                         register double c21 = C[row1+n+n+1];
//                         register double c22 = C[row1+n+n+2];
//                         // register double c23 = C[row1+n+n+3];
//                         // register double c30 = C[row1+n+n+n];
//                         // register double c31 = C[row1+n+n+n+1];
//                         // register double c32 = C[row1+n+n+n+2];
//                         // register double c33 = C[row1+n+n+n+3];

//                         for (kk = k; kk < k+b; kk++)                  //Skipping k will just be linear loop unrolling and will not contribute to performance gains, hence we iterate through k one by one
//                         {
//                                 register int r1 = ii*n + kk;       //i,k
//                                 register int c1 = kk*n + jj;       //k,j

//                                 register double a00 = A[r1];     //i,k
//                                 register double a10 = A[r1+n];   //i+1,k
//                                 register double a20 = A[r1+n+n]; //i+2,k
//                                 // register double a30 = A[r1+n+n+n];

//                                 register double b00 = B[c1];     //k,j
//                                 register double b01 = B[c1+1];   //k,j+1
//                                 register double b02 = B[c1+2];   //k,j+2
//                                 // register double b03 = B[c1+3];

//                                 c00 += a00*b00;
//                                 c01 += a00*b01;
//                                 c02 += a00*b02;
//                                 // c03 += a00*b03;
//                                 c10 += a10*b00;
//                                 c11 += a10*b01;
//                                 c12 += a10*b02;
//                                 // c13 += a10*b03;
//                                 c20 += a20*b00;
//                                 c21 += a20*b01;
//                                 c22 += a20*b02;
//                                 // c23 += a20*b03;
//                                 // c30 += a30*b00;
//                                 // c31 += a30*b01;
//                                 // c32 += a30*b02;
//                                 // c33 += a30*b03;
//                         }
//                         C[row1]=c00;
//                         C[row1+1]=c01;
//                         C[row1+2]=c02;
//                         // C[row1+3]=c03;
//                         C[row1+n]=c10;
//                         C[row1+n+1]=c11;
//                         C[row1+n+2]=c12;
//                         // C[row1+n+3]=c13;
//                         C[row1+n+n]=c20;
//                         C[row1+n+n+1]=c21;
//                         C[row1+n+n+2]=c22;
//                         // C[row1+n+n+3]=c23;
//                         // C[row1+n+n+n]=c30;
//                         // C[row1+n+n+n+1]=c31;
//                         // C[row1+n+n+n+2]=c32;
//                         // C[row1+n+n+n+3]=c33;
//                     }
//             }
                
// }