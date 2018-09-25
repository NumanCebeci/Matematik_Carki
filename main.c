//NUMAN CEBECİ 140202008
//CANSU ŞAHİN 140202012

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int lambda_dizisi[100];
int matris1[100][100];

void cark()
{
int sayi,rastgele,i;
int tut,mod=4,islem;

    printf("sayi giriniz : ");  scanf("%d",&sayi);

    srand(time(NULL));
    for(i=1;i<=sayi;i++)
    {
        rastgele=0+rand()%241;
        printf("%d  ",rastgele);
        tut=rastgele;
    }

    printf("\nislem yapilcak sayi : %d",tut);
    islem=tut%mod;
    printf("\nyapilacak islem :%d\n\n",islem);

    if(islem==0)
    {
        ozDegerBul();
    }

    else if(islem==1)
    {
        schurBul();
    }
    else if(islem==2)
    {
        ozVektorBul();
    }
    else
    {
        nilpotentBul();
    }
}

int determinant_alma(int matris1[100][100], int N)
{
    FILE *det;
    det=fopen("det.txt","w");
    int a,b,c;
    int d1,d2;
    int K=1,m2[100][100];
    int determinant=0;

    if(N==2)
    {
        determinant = matris1[0][0]*matris1[1][1]-matris1[0][1]*matris1[1][0];
        return determinant;
    }
    else
    {
        for(a=0;a<N;a++)
        {
            d1=0;
            d2=0;
            for(b=0;b<N;b++)
            {
                for(c=0;c<N;c++)
                {
                    if(b!=0&&c!=a)
                    {
                        m2[d1][d2]=matris1[b][c];
                        d2++;
                        if(d2>N-2)
                        {
                            d1++;
                            d2=0;
                        }
                    }
                }
            }
            determinant=determinant+K*(matris1[0][a]*determinant_alma(m2,N-1)); //toplam determinantý bulmak için
            K= -1*K; //determinant formülünden dolayý bi + bi - yazmamýz gerektiði için
        }
    }
    fprintf(det,"determinant : %d\n",determinant);
    return determinant;
}

int ozDegerBul()
{
    FILE *matris;
    matris=fopen("matris.txt","w");
    int sonuc,x,i,j;
    int birimMatris[100][100];
    int iz_toplami=0;
    int k,l,N;

    printf("\nmatris boyutunu giriniz :");  scanf("%d",&N);
    printf("Matris degerlerini giriniz\n");
    for(k=0;k<N;k++)
    {
        for(l=0;l<N;l++)
        {
            scanf("%d",&matris1[k][l]);
        }
    }

    for(k=0;k<N;k++)
    {
        for(l=0;l<N;l++)
        {
           printf("%d ",matris1[k][l]);
           fprintf(matris,"%d ",matris1[k][l]);
        }
        fprintf(matris,"\n");
        printf("\n");
    }

    fprintf(matris,"\n");
    for(k=0;k<N;k++)
    {
        for(l=0;l<N;l++)
        {
            if(k==l)

                {
                     birimMatris[k][l]=1;
                     fprintf(matris,"%d ",birimMatris[k][l]);
                }
            else
                {
                    birimMatris[k][l]=0;
                    fprintf(matris,"%d ",birimMatris[k][l]);
                }
                printf("\n");
        }    fprintf(matris,"\n");
    }

    for(i=0;i<N;i++)
    {
        iz_toplami= iz_toplami+matris1[i][i];
    }

    FILE*lambda;
    lambda=fopen("lambda.txt","w");
    int det;
    det=determinant_alma(matris1,N);
    int a=0;
    if(N==2)
        {
            printf("bulmak istedigimiz denklem: x^2 - iz*x - det(A)\n");
            fprintf(lambda,"bulmak istedigimiz denklem: x^2 - iz*x - det(A)\n");
            for(x=-1000;x<1000;x++)
            {
                sonuc=(x*x)-(iz_toplami*x)+det;
                    if(sonuc==0)
                    printf("lambda degeri: %d\n",x);
                    fprintf(lambda,"lambda degeri: %d\n",x);
            }
        }

    int temp[100][100];

        for(x=-100;x<100;x++)
        {
             for(i=0;i<N;i++)
                    {
                        for(j=0;j<N;j++)
                            {
                                temp[i][j]=matris1[i][j];
                            }
                    }

                    for(i=0,j=0;i<N,j<N;i++,j++)
                     {
                         fprintf(lambda,"matris a'nın  %d %d elemani %d ve lambda %d\n\n",i,j,temp[i][j],x);
                         temp[i][j]= matris1[i][j]-x;
                         fprintf(lambda,"matris a'nın  %d %d elemaninin islemden sonraki hali %d\n\n",i,j,temp[i][j]);
                     }

                det=determinant_alma(temp,N);
                if(det==0)
                    {
                        printf("lambda degeri: %d \n",x);
                        fprintf(lambda,"lambda degeri: %d \n",x);
                        lambda_dizisi[a]= x;
                        a++;
                    }
        }
        return N;
}
int schurBul()
{
    FILE *schur;
    schur=fopen("schur.txt","w");
    int N=ozDegerBul();
    int i,j,toplamMatris=0,toplamLambda=0;


    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            toplamMatris=toplamMatris+pow(matris1[i][j],2);
        }
    }
    printf("matrisin kareleri toplami : %d\n",toplamMatris);
    fprintf(schur,"matrisin kareleri toplami : %d\n",toplamMatris);


    for(i=0;i<N;i++)
    {
        toplamLambda=toplamLambda+pow(lambda_dizisi[i],2);
    }

    printf("lambdalarin kareleri toplami : %d\n",toplamLambda);
    fprintf(schur,"lambdalarin kareleri toplami : %d\n",toplamLambda);

    if(toplamMatris<toplamLambda)
        printf("Schur MATRISTIR");

    else
        printf("Schur MATRIS DEGILDIR!!!");

}

int ozVektorBul()
{
    int N = ozDegerBul();
    int i,j,k,a=0,x;
    int toplam=0;
    int temp2[100][100];
    int matrisCarp[N][1];
    int sonuc[N][N];
    int ozVektor_dizisi[50];

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            matrisCarp[i][j]=matris1[i][j];
        }
    }
    for(k=0; k<N; k++)
    {
        printf("\n\n %d . lambda : (%d) degeri icin matrisimizin yeni hali: \n\n",k+1, lambda_dizisi[k]);

        for(i =0, j=0 ; i<N, j<N; i++, j++)
        {
            temp2[i][j]= matris1[i][j] - lambda_dizisi[k];
        }
        for(i=0; i<N ; i++)
        {
            for(j=0; j<N ; j++)
            {
                printf(" %d ", temp2[i][j]);
            }
            printf("\n");
        }
    }

    for(i=0;i<N;i++)
    {
        for(j=0;j<1; j++)
        {
            for( k=0;k<N;k++)
            {
                toplam=toplam+(temp2[i][k]*matrisCarp[k][j]);
            }
            sonuc[i][j] = toplam;
            if(sonuc[i][j]==0)
            {   printf("Oz Vektor Degeri : %d",x);
                ozVektor_dizisi[a]=x;
                a++;
            }
            toplam = 0;
        }
    }

return 0;
}

void nilpotentBul()
{   int sayi,i,j,rastgele,k,sayac=1,sayac1=0;
    int toplam = 0;
    int orjMatris[sayi][sayi];
    int matrisCarp[sayi][sayi];
    int sonuc[sayi][sayi];
    FILE *nilpotent;
    nilpotent=fopen("Nilpotent.txt","w");

    printf("Nilpotent icin matris boyutunu giriniz : ");
    scanf("%d",&sayi);
    printf("Nilpotent icin matris degerlerini giriniz : \n");


    srand(time(NULL));
    for(i=0;i<sayi;i++)
    {
       for(j=0;j<sayi;j++)
         {
           rastgele=-15+rand()%31;
           orjMatris[i][j]=rastgele;
           matrisCarp[i][j]=orjMatris[i][j];
           printf("%d ",orjMatris[i][j]);
         }  printf("\n");
    }
/*
    for(i=0;i<sayi;i++)
    {
       for(j=0;j<sayi;j++)
         {
           scanf("%d",&orjMatris[i][j]);
           matrisCarp[i][j]=orjMatris[i][j];
         }
         printf("\n");
    }
*/

    printf("\nMATRISLERIN CARPIMI\n\n");
    fprintf(nilpotent,"\nMATRISLERIN CARPIMI\n\n");
    int a=1;

while(a==1 && sayac<sayi)
    {
        printf("Matrisin kendisiyle %d. carpimi\n",sayac);
        fprintf(nilpotent,"Matrisin kendisiyle %d. carpimi\n",sayac);
    for(i=0;i<sayi;i++)
    {
        for(j=0;j<sayi; j++)
        {
            for( k=0;k<sayi;k++)
            {
                toplam=toplam+(matrisCarp[i][k]*orjMatris[k][j]);
            }
            sonuc[i][j] = toplam;
            toplam = 0;
            printf("%d ",sonuc[i][j]);
            fprintf(nilpotent,"%d ",sonuc[i][j]);

            if(sonuc[i][j]==0)
            {
                sayac1++;
            }
        }
        printf("\n");
        fprintf(nilpotent,"\n");
    }
    fprintf(nilpotent,"\n");
    for(i=0 ; i<sayi ; i++)
        for(j=0 ; j<sayi ; j++)
            matrisCarp[i][j] = sonuc[i][j];

    printf("\n");
    sayac++;
           if(sayac1==(sayi*sayi))
            {
                printf("MATRIS NILPOTENT MATRISTIR!!!\n");
                fprintf(nilpotent,"MATRIS NILPOTENT MATRISTIR!!!\n");
                a=0;
            }
    }
        if(sayac1!=sayi*sayi)
            printf("Nilpotent Degildir\n");
            fprintf(nilpotent,"Nilpotent Degildir\n");

}

int main()
{
    printf("0 OZDEGER BULMA\n");
    printf("1 SCHUR TEOREMI BULMA\n");
    printf("2 OZVEKTOR BULMA\n");
    printf("3 NILPOTENT BULMA\n\n");

    cark();

    return 0;
}
