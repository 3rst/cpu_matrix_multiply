void dgemm6_kij(double *C,double *A,double *B,int n)
{
    int i,j,k;
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
        {
            register double r=A[i*n+k];
            for(j=0;j<n;j++)
                C[i*n+j]+=r*B[k*n+j];
        }
}

void dgemm6_kij2(double *C,double *A,double *B,int n)
{
    int i,j,k,ii,jj,kk;
    int b=100;
    for(k=0;k<n;k+=b)
        for(i=0;i<n;i+=b)
            for(j=0;j<n;j+=b)
                for(kk=k;kk<k+b;kk++)
                    for(ii=i;ii<i+b;ii++)
                    {
                        register double r=A[ii*n+kk];
                        for(jj=j;jj<j+b;jj++)
                            C[ii*n+jj]+=r*B[kk*n+jj];
                    }
}