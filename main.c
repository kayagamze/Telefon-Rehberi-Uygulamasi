/*
  Cansu ECEVİT 162802035
  Gamze KAYA   162802023
  İlayda EVCİL 152802030
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct telephone
{
    char isim[100];
    long int kod;
    long int numara;
};

void Menu()//MENU FONKSİYONU
{
    printf("TELEFON REHBERI PROGRAMI\n");
    printf("ISLEMLER\n");
    printf("1-Kayit Ekle\n");
    printf("2-Telefonlari Listele\n");
    printf("3-Kaydi Duzenle\n");
    printf("4-Numara Ile Kayit Bul\n");
    printf("5-Isim Ile Kayit Bul\n");
    printf("6-Kayit Sil\n");
    printf("7-Cikis\n");
}

int KayitEkle()//KAYIT EKLEME İŞLEMLERİ GERÇEKLEŞTİRİLİR.
{
    struct telephone yeni_kayit;
    FILE *fp;
    if((fp=fopen("TelefonRehber.txt","ab"))==NULL)//DOSYA AÇMA VE KONTROL ETME
    {
         return -1;
    }
    fseek(fp,0,SEEK_END);
    printf("Isim giriniz:");
    scanf("%s",&yeni_kayit.isim);
    fflush(stdin);
    printf("Kodu giriniz:");
    scanf("%ld",&yeni_kayit.kod);
    fflush(stdin);
    printf("Numarayi giriniz:");
    scanf("%ld",&yeni_kayit.numara);!
    fflush(stdin);
    fwrite(&yeni_kayit,sizeof(struct telephone),1,fp);//ALINAN BİLGİLER DOSYAYA YAZILIR
    fclose(fp);
    return 0;
}

int Listeleme()//LİSTELEME İŞLEMLERİ GERÇEKLETİRİLİR
{
    struct telephone kayit;
    FILE *fp;
    int kontrol;
    if((fp=fopen("TelefonRehber.txt","rb"))==NULL)
        return -1;
        rewind(fp);
        printf("----------------Rehber----------------\n");
        while(!feof(fp))
        {
           kontrol=fread(&kayit,sizeof(struct telephone),1,fp);//DOSYADAN OKUNANLAR DEĞİŞKENE ATILIR
           if(kontrol==1)//DOSYADAN OKUMA KONTROL EDİLİR
           {
           printf("isim:%s\nkod:%ld\nnumara:%ld\n",kayit.isim,kayit.kod,kayit.numara);//OKUNANLAR EKRANA YAZDIRILIR
           }
        }
    fclose(fp);//DOSYA KAPANIR
    return 0;
}

void KayitDuzenleme(char aranan[],int n )//KAYIT DÜZENLEME İŞLEMLERİ GERÇEKLEŞTİRİLİR
{
    struct telephone guncelkayit;
    FILE *fp;
    FILE *fp1;
    if((fp=fopen("TelefonRehber.txt","rb"))==NULL)
        return -1;
    if((fp1=fopen("TelefonRehber1.txt","ab"))==NULL)
        return -1;
    rewind(fp);
    while(!feof(fp))//DOSYA SONU GELENE KADAR DÖNGÜ DEVAM EDER
    {
        fread(&guncelkayit,sizeof(struct telephone),1,fp);//DOSYADAN BİLGİLER OKUNUR
        if(strcmp(aranan,guncelkayit.isim)==0)
        {//ARANAN İLE DOSYA UYUŞURSA YENİ BİLGİLER ALINIR        {
            printf("Yeni ismi giriniz:");
            scanf("%s",&guncelkayit.isim);
            fflush(stdin);//TAMPON BÖLGE TEMİZLENİR
            printf("Yeni kodu giriniz:");
            scanf("%ld",&guncelkayit.kod);
            fflush(stdin);
            printf("Yeni numarayi giriniz:");
            scanf("%ld",&guncelkayit.numara);
            fflush(stdin);
            fwrite(&guncelkayit,sizeof(struct telephone),1,fp1);//YENİ BİLGİLER YENİ DOSYAYA YAZILIR
        }
        else
            fwrite(&guncelkayit,sizeof(struct telephone),1,fp1);//ESKİ BİLGİLER YENİ DOSYAYA YAZILIR
    }

            fclose(fp);
            fclose(fp1);
            remove("TelefonRehber.txt");// ESKİ DOSYA SİLİNİR
            rename("TelefonRehber1.txt","TelefonRehber.txt");//YENİ DOSYANIN İSMİ ESKİ DOSYANINN İSMİYLE DEĞİŞTİRİLİR

}
int GuncellemeKontrol()//GUNCELLEME İÇİN ARAMA YAPILIR
{
    struct telephone guncelkayit;
    FILE *fp;
    char aranan[100];
    if((fp=fopen("TelefonRehber.txt","rb"))==NULL)
        return -1;
    printf("\nDuzeltmek istediginiz kisinin ismini giriniz:");
    scanf("%s",&aranan);//ARANACAK İSİM ALINIR
    rewind(fp);
    while(fread(&guncelkayit,sizeof(struct telephone),1,fp)==1)
    {
        if(strcmp(aranan,guncelkayit.isim)==0)//ARANAN İSİM DOSYADA BULUNURSA GEREKLİ FONKSİYON ÇAĞRILIR.
        {
            fclose(fp);
            KayitDuzenleme(aranan,100);//FONKSİYONUN ÇAĞRILMASI
            return 0;
        }
    }
    fclose(fp);
    return -1;
}
void KayitSilme(long int aranankod)//KAYIT SİLME İŞLEMLERİ GERÇEKLEŞTİRİLİR
{
    struct telephone kayit;
    FILE *fp;
    FILE *fp1;
        if((fp=fopen("TelefonRehber.txt","rb"))==NULL)
            return -1;
        if((fp1=fopen("TelefonRehber1.txt","wb"))==NULL)
            return -1;
    while(fread(&kayit,sizeof(struct telephone),1,fp)==1)
    {
        if(kayit.kod!=aranankod)//ARANAN KOD İLE DOSYADAN OKUNAN BİLGİ AYNI OLMAMASINI KONTROL EDER
            fwrite(&kayit,sizeof(struct telephone),1,fp1);//YENİ DOSYAYA YAZAR
    }
            fclose(fp);
            fclose(fp1);
            remove("TelefonRehber.txt");
            rename("TelefonRehber1.txt","TelefonRehber.txt");
}
int SilmeKontrol()//SİLME İÇİN ARAMA YAPILIR
{
    struct telephone kayit;
    FILE *fp;
        if((fp=fopen("TelefonRehber.txt","rb"))==NULL)
                 return -1;
    long int aranankod;
    printf("\nSilmek istedginiz kaydin kodunu girin:");
    scanf("%ld",&aranankod);//ARANAN KOD ALINIR
    rewind(fp);
    while(fread(&kayit,sizeof(struct telephone),1,fp)==1)//DOSYADAN BİLGİ OKUNDUKÇA DÖNGÜ DEVAM EDER
    {
        if(kayit.kod==aranankod)//ARANAN KOD İLE DOSYA UYUŞURSA GEREKLİ FONKSİYON ÇAĞRILIR
        {
            fclose(fp);
            KayitSilme(aranankod);//FONKSİYONUN ÇAĞRILMASI
            return 0;
        }
    }
    fclose(fp);
    return -1;
}
int NumaraileBulma()//NUMARA İLE BULMA İŞLEMLERİ GERÇEKLETİRİLİR
{
    struct telephone kayit;
    FILE *fp;
    long int aranan_numara;
    if((fp=fopen("telefonrehber.txt","rb"))==NULL)
     return -1;
    printf("Bulmak istediginiz kisinin numarasini giriniz:");
    scanf("%ld",&aranan_numara);
    rewind(fp);
    while((fread(&kayit,sizeof(struct telephone),1,fp))==1);
    {
        if(aranan_numara==kayit.numara)//ARANAN NUMARA İLE DOSYA UYUŞURSA EKRANA BİLGİLER YAZDIRILIR
        {
            printf("\nIsim:%s\n",kayit.isim);
            printf("Kod:%ld\n",kayit.kod);
            printf("Numara:%ld\n",kayit.numara);

        }

    }
    fclose(fp);
}
int IsimileBulma()//İSİM İLE BULMA İŞLEMLERİ GERÇEKLEŞTİRİLİR
{
    struct telephone kayit;
    FILE *fp;
    char aranan_isim[100];
    if((fp=fopen("TelefonRehber.txt","rb"))==NULL)
        return -1;
    printf("Bulmak istediginiz kaydin ismini girin:");
    scanf("%s",&aranan_isim);
    rewind(fp);
    while((fread(&kayit,sizeof(struct telephone),1,fp))==1)
    {
        if(strcmp(aranan_isim,kayit.isim)==0)//ARANAN İSİM İLE DOSYA UYUŞURSA EKRANA BİLGİLER YAZDIRILIR
        {
            printf("\nIsim:%s\n",kayit.isim);
            printf("Kod:%ld\n",kayit.kod);
            printf("Numara:%ld\n",kayit.numara);
        }
    }
    fclose(fp);
}
int main()
{
    setlocale(LC_ALL,"Turkish");//TÜRKÇE KARAKTER SORUNUNU ÇÖZER
    int secim,tercih;
    do
    {
        Menu();//MENÜ FONKSİYONU ÇAĞRILIR
        printf("Yapmak istediginiz islemi seciniz:");
        scanf("%d",&secim);//YAPILMAK İSTENEN İŞLEM KULLANICIDAN ALINIR
    if(secim==1)
    {
        if(KayitEkle()==0)//FONKSİYONUN DOĞRU ÇALIŞMASI DURUMU
            printf("\nTelefon numarasi rehbere eklendi.\n");
        else
            printf("\nTelefon numarasi rehbere eklenemedi.\n");
    }
    if(secim==2)
    {
      if(Listeleme()==0)
        printf("\nRehber basariyla listelendi.\n");
      else
        printf("\nListelenme basarisiz.\n");
    }
    if(secim==3)
    {
        if(GuncellemeKontrol()==0)
            printf("\nKayit basariyla guncellendi.\n");
        else//FONKSİYON ARANAN İSMİ BULAMAZSA BU İŞLEM GERÇEKLEŞİR
        {
            printf("Aranan isim bulunamadi.Tekrar arama yapmak ister misiniz?\n");
            printf("Evet için 1 e basiniz\nHayir icin 2 ye basiniz.");
            scanf("%d",&tercih);
            if(tercih==1)
                GuncellemeKontrol();
        }
    }
    if(secim==4)
    {
        if(NumaraileBulma()==0)
            printf("\nNumara ile kayit bulma basarili.\n");
        else
            printf("\nNumara ile kayit bulma basarisiz.\n");
    }
    if(secim==5)
    {
        if(IsimileBulma()==0)
            printf("\nIsim ile kayit bulma basarili\n");
        else
            printf("\nIsim ile kayit bulma basarisiz\n");
    }
    if(secim==6)
        if(SilmeKontrol()==0)
            printf("\nKayit basariyla silindi.\n");
            else
            {
                printf("Aranan kod bulunamadi.Tekrar arama yapmak ister misiniz?\n");
                printf("Evet icin 1 e basiniz\nHayir icin 2 ye basiniz.");
                scanf("%d",&tercih);
                if(tercih==1)
                    SilmeKontrol();
            }
    }while(secim!=7);//KULLANICI ÇIKIŞ MENÜSÜNÜ SEÇENE KADAR DÖNGÜ DEVAM EDER
    printf("Rehberden cikis yapildi!\n");

    return 0;
    }
