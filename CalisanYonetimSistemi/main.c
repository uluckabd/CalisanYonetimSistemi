#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max 20

struct employee {
    char isim[20];
    int code;
    char job[20];
    int experience;
    int age;
};

struct employee emp[max];
int number = 0;


int guvenli_int_oku(const char* mesaj) {
    int sayi;
    char c;
    while (1) {
        printf("%s", mesaj);
        if (scanf("%d", &sayi) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // input temizleme
            return sayi;
        } else {
            printf("HATALI GIRIS! Lutfen sadece int(sayý) degerler ile giriniz.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}


void guvenli_string_oku(const char* mesaj, char* hedef, int boyut) {
    char giris[100];
    int gecerli = 0;
    while (!gecerli) {
        printf("%s", mesaj);
        if (fgets(giris, sizeof(giris), stdin) != NULL) {
            size_t len = strlen(giris);
            if (len > 0 && giris[len - 1] == '\n') {
                giris[len - 1] = '\0';
            }

            gecerli = 1;
            for (int i = 0; giris[i] != '\0'; i++) {
                if (!isalpha((unsigned char)giris[i])) {
                    gecerli = 0;
                    break;
                }
            }

            if (!gecerli) {
                printf("HATALI GIRIS! Lutfen sadece string deðer giriniz.\n");
            } else {
                strncpy(hedef, giris, boyut - 1);
                hedef[boyut - 1] = '\0';
            }
        }
    }
}


int id_var_mi(int id) {
    for (int i = 0; i < number; i++) {
        if (emp[i].code == id) {
            return 1;
        }
    }
    return 0;
}

void build() {
    printf("max calisan sayisi: %d\n", max);
    number = guvenli_int_oku("lutfen calisan sayisini giriniz: ");

    if (number > max) {
        printf("maksimum calisan sayisi sinirini astiniz. %d olarak ayarlandi.\n", max);
        number = max;
    }

    for (int i = 0; i < number; i++) {
        printf("\n%d. calisan bilgilerini giriniz:\n", i + 1);

        guvenli_string_oku("ad: ", emp[i].isim, sizeof(emp[i].isim));

        int geciciID;
        do {
            geciciID = guvenli_int_oku("calisan id: ");
            if (id_var_mi(geciciID)) {
                printf("Bu ID daha once kullanilmis. Farkli bir ID giriniz.\n");
            }
        } while (id_var_mi(geciciID));
        emp[i].code = geciciID;

        guvenli_string_oku("calisan meslegi: ", emp[i].job, sizeof(emp[i].job));
        emp[i].experience = guvenli_int_oku("calisan tecrubesi (yil olarak): ");
        emp[i].age = guvenli_int_oku("calisan yasi: ");

        printf("islem basarili\n");
    }

    showmenu();
}

void ekleme() {
    if (number < max) {
        guvenli_string_oku("ad: ", emp[number].isim, sizeof(emp[number].isim));

        int yeniID;
        do {
            yeniID = guvenli_int_oku("calisan id: ");
            if (id_var_mi(yeniID)) {
                printf("Bu ID daha once kullanilmis. Farkli bir ID giriniz.\n");
            }
        } while (id_var_mi(yeniID));
        emp[number].code = yeniID;

        guvenli_string_oku("calisan meslegi: ", emp[number].job, sizeof(emp[number].job));

        emp[number].experience = guvenli_int_oku("calisan tecrubesi (yil olarak): ");
        emp[number].age = guvenli_int_oku("calisan yasi: ");

        printf("islem basarili\n");
        number++;
    } else {
        printf("maksimum calisan sayisini astiniz.\n");
    }

    showmenu();
}

void kaydiara() {
    int code = guvenli_int_oku("calisan bilgilerine ulasmak icin id giriniz: ");
    for (int i = 0; i < number; i++) {
        if (emp[i].code == code) {
            printf("Ad: %s\n", emp[i].isim);
            printf("Meslek: %s\n", emp[i].job);
            printf("Tecrube: %d\n", emp[i].experience);
            printf("Yas: %d\n", emp[i].age);
            break;
        }

    }
    showmenu();
}

void calisansayisigoster() {
    printf("calisan sayisi: %d\n", number);
    showmenu();
}

void silindex(int i) {
    for (int j = i; j < number - 1; j++) {
        strcpy(emp[j].isim, emp[j + 1].isim);
        emp[j].code = emp[j + 1].code;
        strcpy(emp[j].job, emp[j + 1].job);
        emp[j].experience = emp[j + 1].experience;
        emp[j].age = emp[j + 1].age;
    }
}

void kaydisil() {
    int code = guvenli_int_oku("calisani silmek icin id giriniz: ");
    for (int i = 0; i < number; i++) {
        if (emp[i].code == code) {
            silindex(i);
            number--;
            printf("silme islemi basarili\n");
            break;
        }
    }
    showmenu();
}

void showmenu() {
    int secim;

    printf("\n\n--- Calisan Yonetim Sistemi ---\n");
    printf("1 - Calisan tablosu olustur\n");
    printf("2 - Yeni calisan ekle\n");
    printf("3 - Calisan bilgilerini sil\n");
    printf("4 - Calisan bilgilerini getir\n");
    printf("5 - Calisan sayisini goster\n");
    printf("6 - Cikis yap\n");

    secim = guvenli_int_oku("Islem seciniz: ");

    switch (secim) {
        case 1: build();
        break;
        case 2: ekleme();
        break;
        case 3: kaydisil();
        break;
        case 4: kaydiara();
         break;
        case 5: calisansayisigoster();
         break;
        case 6:
            return;
        default:
            printf("Yanlis secim yaptiniz. ust menuye aktarýlýyosunuz.\n");
            showmenu();
            break;
    }
}

int main() {
    showmenu();
    return 0;
}
