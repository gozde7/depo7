//
//  main.c
//  bağlı liste
//
//  Created by gözde on 21.02.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Olay kaydını temsil eden yapı burda event tanımladık ve dizilerle özelliklerini girdim
typedef struct Event {
    char zaman[30];  // Olay zamanı
    char seviye[10]; // Olay önemi (INFO, WARNING, ERROR)
    char mesaj[100]; // Olay içeriği
    struct Event* sonraki;
} Event;

// Bağlı listenin başlangıç noktası
Event* bas = NULL;

// Şu anki zamanı almak için fonksiyon
void zamanAl(char* buffer) {
    time_t t;
    struct tm* zamanBilgisi;
    time(&t);
    zamanBilgisi = localtime(&t);
    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", zamanBilgisi);
}

// Yeni bir olay ekleme fonksiyonu
void olayEkle(char* seviye, char* mesaj) {
    Event* yeniOlay = (Event*)malloc(sizeof(Event));
    zamanAl(yeniOlay->zaman);
    strcpy(yeniOlay->seviye, seviye);
    strcpy(yeniOlay->mesaj, mesaj);
    yeniOlay->sonraki = bas;  // Yeni olay başa eklenir
    bas = yeniOlay;
}

// Olayları ekrana yazdırma fonksiyonu
void olaylariGoster(void) {
    Event* gecici = bas;
    printf("\n-- Kayıtlı Olaylar --\n");
    while (gecici != NULL) {
        printf("[%s] %s: %s\n", gecici->zaman, gecici->seviye, gecici->mesaj);
        gecici = gecici->sonraki;
    }
}

int main(void) {
    olayEkle("INFO", "Sistem başlatıldı.");
    olayEkle("WARNING", "Disk kullanım oranı yüksek.");
    olayEkle("ERROR", "Veritabanına bağlanılamadı.");
    
    olaylariGoster();
    
    return 0;
}
//syslog mekanizması nedir: syslog bilgisayar sistemlerine ve ağ cihazlarında gerçekleşen olayları merkezi bir yere iletmek ve saklamak için kullanılır unix tabanlı sistemlerde kullanılır.
//syslog ne için kullanılır: çalışma durumunu ve hataları belirlemek için ,yettkisiz girişleri ve hataları tespit etmek için kullanılır son olarak birden çok cihazı merkezi bir sisteme bağlamak için
// bağlı liste kullanarak olay kayıtları nasıl saklanır: bağlı liste, verileri dinamik olarak yönetmek için kullanılan bir veri yapısıdır. kayıt saklamak için kullanılırsa her olay düğüm olarak saklanır
// neden tek yönlü bağlı liste kullandım: bellekten tasaruf etmemi sağlar, yeni olaylar başta olduğu için olayın güncel olmasını sağlar.

