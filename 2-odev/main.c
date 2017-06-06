#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int kayitEkle();
int kayitListele();
int kayitGuncelle();
int nukayitBul();
int iskayitBul();
int kayitSil();
int kayitSayisi=0;

typedef struct{
    char isim[100];
    long long numara;
    long long kod;
}telefon;

int main()
{
    setlocale(LC_ALL, "Turkish"); system("color 7c"); time_t t = time(NULL); struct tm *tm = localtime(&t);
    printf("\tTelefon Rehberi v1.0\n\t***************\n\n");
    printf("\n\t*\t1-Kayit EKLE\n\t*\t2-Kayit LISTELE\n\t*\t3-Kayit GUNCELLE\n\t*\t4-Kayit BUL (numara)\n\t*\t5-Kayit BUL (isim)\n\t*\t6-Kayit SIL\n\n\t*\t0-Rehberden CIK!\n\t________________________\n\t%s",asctime(tm));
    char secim;
    printf("\n\n\t\tGiris : ");
    scanf("%c",&secim);
    if(secim =='1') kayitEkle();
    else if(secim =='2') kayitListele();
    else if(secim =='3') kayitGuncelle();
    else if(secim =='4') nukayitBul();
    else if(secim =='5') iskayitBul();
    else if(secim =='6') kayitSil();
    else if(secim =='0') exit(1);
    else {
    system("cls");
    printf("\t0-6 arasinda deger giriniz!");
    return main();
    }
    return 0;
}///--------------------------------------


    int kayitEkle(){
    telefon tel= { "", 0, 0 };
    FILE *fp;
    fp=fopen("TelefonRehber.txt","at");
    printf("\n\tIsminiz : ");
    scanf("%s",&tel.isim);
    printf("\n\tTelefon Numarasi : ");
    scanf("%lld",&tel.numara);

    long long randomsayi;
    srand(time(NULL));
    randomsayi=100000+rand()%899999;
    printf("\n\tOzel Rehber Kodunuz : %lld",randomsayi);
    tel.kod=randomsayi;

    kayitSayisi++;
    fseek(fp,sizeof(tel)*kayitSayisi,0);
    if(fwrite(&tel,sizeof(telefon),1,fp)!=1) exit(1);
    char s;
    printf("\n\n\t--> Menuye donmek icin bir tusa basin : ");
    scanf("%s",&s);
    rewind(fp);
    return main();
}///-------------------------------------------------------

    int kayitListele(){
    FILE *fp;
    telefon tel;
    fp=fopen("TelefonRehber.txt","rt");
    if(fp==NULL) exit(1);
    fseek(fp,0,0);
    fread(&tel,sizeof(telefon),1,fp);
    printf("\n\tISIM \t\tNUMARA \t\tOZEL KOD");
    while(!feof(fp))
    {
        if(strcmp(tel.isim,""))
            printf("\n\t%s \t\t%lld \t\t%lld",tel.isim,tel.numara,tel.kod);
            fread(&tel,sizeof(telefon),1,fp);
    }
    fclose(fp);
    char s;
    printf("\n\n\t-->menuye donmek icin bir tusa basiniz : ");
    scanf("%s",&s);
    return main();
}///-------------------------------------------------------

    int kayitGuncelle(){
    FILE *fp;
    telefon tel;
    fp=fopen("TelefonRehber.txt","rt+");
    if(fp==NULL) exit(1);
    char is[100];
    int index=0;
    printf("\n\tGuncellenecek Kaydin Isminin Giriniz : ");
    scanf("%s",is);
    printf("\n\tINDEX\t\t\tISIM \t\tNUMARA \t\tOZEL KOD");
    while(fread(&tel,sizeof(tel),1,fp))
    {
        index++; if(!strcmp(tel.isim,is)){printf("\n\t<INDEX-%d>\t\t%s \t\t%lld \t\t%lld",index,tel.isim,tel.numara,tel.kod); break;}
    }
    printf("\n\tOZEL REHBER KODUNUZ asla DEGISTIRILMEZ!!!");
    printf("\tGuncel Verileri Eksiksiz Giriniz!");
    printf("\n\tYeni Isminiz : ");
    scanf("%s",&tel.isim);
    printf("\n\tYeni Telefon Numarasi : ");
    scanf("%lld",&tel.numara);
    printf("\n\tOzel Rehber Kodunuz : %lld",tel.kod);
    fseek(fp,(index-1)*sizeof(tel),SEEK_SET);
    fwrite(&tel,sizeof(tel),1,fp);
    fclose(fp);

    char s;
    printf("\n\n\t-->menuye donmek icin bir tusa basiniz : ");
    scanf("%s",&s);
    return main();
}///-------------------------------------------------

    int nukayitBul(){
    telefon tel;
    int i;
    FILE *fp;
    fp=fopen("TelefonRehber.txt","rt");
    fseek(fp,0,0);
    fread(&tel,sizeof(telefon),1,fp);
    long long num;
    printf("\n\tAranacak Tel Numarasi : ");
    scanf("%lld",&num);
    printf("\n\tISIM \tNUMARA \tOZEL KOD");
    while(!feof(fp))
    {
        if(tel.numara==num)
        printf("\n\t%s \t%lld \t%lld",tel.isim,tel.numara,tel.kod);
        fread(&tel,sizeof(telefon),1,fp);

    }
    fclose(fp);
    char s;
    printf("\n\n\t-->menuye donmek icin bir tusa basiniz : ");
    scanf("%s",&s);
    return main();
}///------------------------------------------------------

    int iskayitBul(){
    telefon tel;
    int i;
    FILE *fp;
    fp=fopen("TelefonRehber.txt","rt");
    fseek(fp,0,0);
    fread(&tel,sizeof(telefon),1,fp);
    char is[100];
    printf("\n\tAranacak Isim : ");
    scanf("%s",&is);
    printf("\n\tISIM \t\tNUMARA \t\tOZEL KOD");
    while(!feof(fp))
    {
        if(!strcmp(tel.isim,is))
        printf("\n\t%s \t\t%lld \t\t%lld",tel.isim,tel.numara,tel.kod);
        fread(&tel,sizeof(telefon),1,fp);
    }
    fclose(fp);
    char s;
    printf("\n\n\t-->menuye donmek icin bir tusa basiniz : ");
    scanf("%s",&s);
    return main();
}///-------------------------------------------------------

    int kayitSil(){
    telefon tel;
    int i;
    FILE *fp;
    fp=fopen("TelefonRehber.txt","rt+");
    if(fp==NULL) exit(1);
    long long rkod;
    int index=0;
    printf("\n\tSilinecek Kaydin Ozel Rehber Kodunu Giriniz : ");
    scanf("%lld",&rkod);
    printf("\n\tINDEX\t\t\tISIM \t\tNUMARA \t\tOZEL KOD");
    telefon COPKUTUSU ={"",0,0};
    while(fread(&tel,sizeof(tel),1,fp))
    {
        index++;
        if(tel.kod==rkod){
        printf("\n\t<INDEX-%d>\t\t%s \t\t%lld \t\t%lld",index,tel.isim,tel.numara,tel.kod);
        fseek(fp,(index-1)*sizeof(tel),SEEK_SET);
        fwrite(&COPKUTUSU,sizeof(tel),1,fp);
        printf("\n\n\tKAYIT COPKUTUSUNA ATILDI!");
        break;}
    }
    if (tel.kod!=rkod || fp==NULL || fread(&tel,sizeof(tel),1,fp)!=1) printf("\n\n\n\tKayit yok veya Hatali Arama !!!");
    fclose(fp);
    char s;
    printf("\n\n\t-->menuye donmek icin bir tusa basiniz : ");
    scanf("%s",&s);
    return main();
}
