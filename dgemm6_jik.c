void dgemm6_jik(double *C,double *A,double *B,int n)
{
    int i,j,k;
    for(j=0;j<n;j++)
        for(i=0;i<n;i++)
        {
            register double r=C[i*n+j];
            for(k=0;k<n;k++)
                r+=A[i*n+k]*B[k*n+j];
            C[i*n+j]=r;
        }
}

void dgemm6_jik2(double *C,double *A,double *B,int n)
{
    int i,j,k,ii,jj,kk;
    int b=100;
    for(j=0;j<n;j+=b)
        for(i=0;i<n;i+=b)
            for(k=0;k<n;k+=b)
                for(jj=j;jj<j+b;jj++)
                    for(ii=i;ii<i+b;ii++)
                    {
                        register double r=C[ii*n+jj];
                        for(kk=k;kk<k+b;kk++)
                            r+=A[ii*n+kk]*B[kk*n+jj];
                        C[ii*n+jj]=r;
                    }
}