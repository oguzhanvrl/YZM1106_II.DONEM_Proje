# YZM1106_II.DONEM_Proje
CBU - YZM1106 2.Dönem Proje Ödevi
#include <locale.h>

typedef struct
{
    char harf;
    int adet;
}structHarf;

int main()
{
    setlocale(LC_ALL,"Turkish");
    int i=0,j=0,top=0;
    char c;
    structHarf dizi[29],temp;
    FILE *fp,*fHarf;
    fHarf=fopen("harfler.txt","r");
    for(i=0;i<29;i++)
    {
        dizi[i].harf=fgetc(fHarf);
        dizi[i].adet=0;
    }
    fclose(fHarf);
    fp=fopen("m.txt","rb");
    for(;;)
    {
        c=toupper(fgetc(fp));
        if(feof(fp)!=0)
            break;
        if(c==' ')
                continue;
            top++;
        for(i=0;i<29;i++)
        {
            if(c=='I')
            {
                dizi[11].adet++;
                break;
            }
            else if(c=='İ')
            {
                dizi[10].adet++;
                break;
            }

            else if(c==dizi[i].harf)
            {
                dizi[i].adet++;
                break;
            }
        }

    }

    for(i=0;i<29;i++)
    {
        for(j=0;j<28-i;j++)
        {
            if(dizi[j].adet<dizi[j+1].adet)
            {
                temp=dizi[j];
                dizi[j]=dizi[j+1];
                dizi[j+1]=temp;
            }
        }
    }
    printf("TOPLAM %d TANE HARF VAR .\n",top);
    for(i=0;i<29;i++)
        printf("%c :  %d\n",dizi[i].harf,dizi[i].adet);
    return 0;
}
