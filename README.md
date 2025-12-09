# 🍅 ESP32 Advanced Pomodoro Timer (v1.0)

**Nesne Yönelimli Mimari (OOP) ve Kalıcı Hafıza Yönetimi ile Geliştirilmiş Profesyonel Pomodoro Sayacı**

Bu proje, standart bir zamanlayıcıdan farklı olarak; **Solid Yazılım Prensipleri**, **Non-Blocking I/O**, **Dependency Injection** ve **Persistent Memory** (Flash Hafıza) teknikleri kullanılarak ESP32 üzerinde geliştirilmiştir.

## 🚀 Proje Özellikleri

Bu sistem, "Gömülü Sistem Mühendisliği" standartlarına uygun olarak tasarlanmıştır:

### 🛠 Yazılım Mimarisi
- **OOP & Encapsulation:** Tüm donanım ve zamanlama mantığı `Time`, `Pins` ve `lcdprint` sınıfları içinde izole edildi.
- **Dependency Injection:** Ekran sınıfı (`lcdprint`), zaman verisine doğrudan erişmez; `Time` sınıfını pointer olarak alır. Bu sayede bağımlılık (coupling) minimize edildi.
- **Finite State Machine (FSM):** Cihazın durumları (`DEVAM`, `DUR`, `GOSTER`, `SIFIRLA`) kararlı bir durum makinesi ile yönetilir.
- **Non-Blocking Multitasking:** `delay()` kullanılmadan, `millis()` tabanlı zamanlayıcılar ile buton okuma ve ekran güncelleme eş zamanlı çalışır.

### 💾 Hafıza ve Veri (Preferences API)
- **Kalıcı Tur Sayacı:** ESP32'nin `Preferences.h` kütüphanesi kullanılarak, tamamlanan Pomodoro turları Flash hafızaya kaydedilir. Cihaz kapansa bile kaldığınız yerden devam edersiniz.
- **Ayarların Korunması:** Kullanıcı ayarları elektrik kesintisinden etkilenmez.

## ⚙️ Donanım Gereksinimleri

| Bileşen | Açıklama |
| :--- | :--- |
| **Mikrodenetleyici** | ESP32 Dev Kit V1 |
| **Ekran** | 16x2 LCD (I2C Modüllü) |
| **Giriş Birimleri** | 4x Push Button |
| **Uyarıcı** | Buzzer (Opsiyonel) |

## 🔌 Pin Bağlantı Şeması (Pinout)

Kod içerisindeki `Pins` sınıfı yapılandırması şöyledir:

| İşlev | ESP32 GPIO Pin | Açıklama |
| :--- | :--- | :--- |
| **SDA** | 21 | I2C Veri Hattı |
| **SCL** | 22 | I2C Saat Hattı |
| **Durdur (Stop)** | 23 | Sayacı durdurur ve duraklatır |
| **Başlat (Play)** | 14 | 25 dakikalık sayacı başlatır |
| **Tur Göster (Show)** | 25 | Toplam tamamlanan tur sayısını gösterir |
| **Tur Sıfırla (Reset)** | 26 | Tur sayacını sıfırlar ve hafızadan siler |

*(Not: Pin numaraları `main.cpp` içerisinden değiştirilebilir.)*

## 📂 Kütüphane Yapısı (`efe_pomodoro`)

Proje modüler bir yapıya sahiptir:

- **`class Time`**: Zaman hesaplamaları, `millis()` takibi ve Flash hafıza işlemlerini (Save/Load) yönetir.
- **`class lcdprint`**: Sunum katmanıdır. Zaman verisini işleyip kullanıcı dostu formatta (MM:SS) ekrana basar. `Time` sınıfından veri çeker.
- **`class Pins`**: Donanım soyutlama katmanıdır.

## 🚀 Kurulum ve Kullanım

1. Bu repoyu indirin.
2. `efe_pomodoro.h`, `efe_pomodoro.cpp` ve `main.cpp` dosyalarını proje klasörüne alın.
3. Gerekli kütüphaneleri (`LiquidCrystal_I2C`) yükleyin (`Preferences` zaten dahili gelir).
4. Kodu ESP32'ye yükleyin.
5. **Kullanım:**
   - **Başlat:** Sayacı 25 dakikadan geriye başlatır.
   - **Süre Bittiğinde:** Otomatik olarak tur sayısı artar, hafızaya kaydedilir ve zil çalar.
   - **Tur Göster:** Toplam çalışma sayınızı gösterir (Fişi çekseniz bile silinmez).

---
*Geliştirici: Efe [Soyadın]*
*Bilgisayar Mühendisliği Öğrencisi*
