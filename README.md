# KombiTest Yardım ve Kullanıcı Rehberi

---

## 1. Genel Bilgiler

**KombiTest**, farklı kombi markalarının (Vaillant, Demirdöküm, E.C.A., Bosch) hata kodlarını okuyabilen, test/reset işlemlerini yapabilen ve donanım/yazılım/model güncellemelerini otomatik olarak yönetebilen bir teşhis ve test cihazıdır.

- **Tek RX/TX hattı** üzerinden çoklu marka desteği.
- **Donanım sürümüyle uyumlu yazılım güncellemesi** (donanım yükseltilebilir, yazılım da uygun olmalı).
- **Model dosyası ve hata tablosu** otomatik güncellenebilir.
- **Kullanıcıya web arayüzüyle güncelleme ve test/reset menüsü sunar.**
- **Güncelleme tercihi** (açık/kapalı) web arayüzünden ayarlanabilir.

---

## 2. Donanım Özellikleri

- Tek bir diagnostik RX/TX hattı ile tüm marka bağlantılarını destekler.
- Test padleri/probları:  
  - `DIAG_RX` ve `DIAG_TX` (tüm markalar için ortak)
- Bosch için özel pad gerekmez, mevcut hatta bağlanır.
- Kicad şema ve PCB dosyalarında Bosch desteği ve tüm marka desteği notları bulunur.

---

## 3. Yazılım Yapısı ve Dosya Dizini

```text
src/
  main.cpp
  hardware/
    diagnostic_driver.cpp
    error_tables.h
    error_tables.cpp
    pinmap_dynamic.h
  settings/
    hw_version.h
    update_settings.h
    update_settings.cpp
  app/
    update_manager.cpp
    diagnostic_api.cpp
models/
  vaillant_ecotecplus_2024.xml
  demirdokum_neo_2023.xml
  eca_proteus_2022.xml
  bosch_condens_2025.xml
guncelle/
  firmware_version_1.2.0.json
  firmware_version_1.1.0.json
  firmware_version_1.0.0.json
  release_notes_1.2.0.txt
  error_tables/
    vaillant_error_table.json
    demirdokum_error_table.json
    eca_error_table.json
    bosch_error_table.json
data/
  diagnostic_menu.html
  update_menu.html
```

---

## 4. Güncelleme Sistemi

- **Firmware güncellemeleri:**  
  `/guncelle/firmware_version_x.x.x.json` dosyaları ile yapılır.  
  Her dosyada sürüm, uyumlu donanım listesi, notlar ve indirme linki bulunur.

- **Model dosyası güncellemeleri:**  
  `/models/` altındaki XML dosyaları cihaz tarafından otomatik kontrol edilir, eksikse indirilir.

- **Hata tabloları güncellemeleri:**  
  `/guncelle/error_tables/` altındaki her marka için ayrı JSON dosyası cihaz tarafından kontrol edilir ve gerekirse güncellenir.

- **Kullanıcı güncelleme tercihi:**  
  Web arayüzünden açılıp kapatılabilir (`/api/update_pref`).

---

## 5. Web Arayüzü

Cihaza bağlandığınızda şu menülerden erişebilirsiniz:

- **Diagnostik Menüsü:**  
  Marka seçin, test (hata okuma) ve reset işlemleri yapın.  
  Bosch dahil tüm markalar desteklenir.

- **Güncelleme Menüsü:**  
  Otomatik güncellemeyi açıp kapatın, yeni yazılım varsa bildirim alın ve doğrudan güncelleyin.

---

## 6. Marka Desteği ve Protokoller

- **Desteklenen Markalar:**  
  - Vaillant  
  - Demirdöküm  
  - E.C.A.  
  - Bosch

- **Hata tabloları** her marka için `/guncelle/error_tables/` altında JSON olarak tutulur ve cihazda dinamik olarak yüklenir.
- **Reset ve test fonksiyonları** her marka için tanımlanmıştır, Bosch dahil.

---

## 7. Kicad Donanım Projesi

- Bosch ve diğer markalar için tek RX/TX hattı kullanılır.
- Şema ve PCB üzerinde açıklama olarak “Bosch desteği” eklenmiştir.
- Eğer ileride ayrı bir pad gerekirse, şemada BOSCH_RX/BOSCH_TX olarak eklenebilir.

---

## 8. Geliştirme ve Özelleştirme

- Kendi donanım sürümünüzü `src/settings/hw_version.h` dosyasında belirleyin.
- Yeni marka eklemek için:
  - `models/` altına yeni model XML’i ekleyin.
  - `guncelle/error_tables/` altına yeni hata tablosu JSON’u koyun.
  - `diagnostic_driver.cpp` ve `diagnostic_api.cpp`’de ilgili protokolleri ekleyin.

---

## 9. Sürüm Geçmişi ve Kazanımlar

### Başlangıçta:
- Temel test/reset ve hata okuma fonksiyonları vardı.
- Güncellemeler elle, donanım/yazılım uyumu gözetilmeden yapılıyordu.
- Sadece bazı markalar destekleniyordu.

### Son Haliyle:
- Donanım sürümüne uygun güncelleme, model ve hata tablosu güncellemesi dinamik ve otomatik.
- Bosch desteği ve diğer markalar için ortak hata okuma/tespit/reset işlevleri.
- Tüm kullanıcı ayarları ve güncellemeler web arayüzünden yönetilebiliyor.
- Kicad projelerinde Bosch desteği ve açıklamaları yer alıyor.

---

## 10. Sık Sorulan Sorular

**S: Bosch için ayrı bir RX/TX pad’i gerek var mı?**  
C: Hayır, tüm markalar ortak hatta desteklenir. İleride değişirse şemada ayrı pad eklenmelidir.

**S: Güncelleme dosyalarını nerede bulurum?**  
C: GitHub reposu `guncelle/` altında firmware, model ve hata tablosu dosyaları tutulur.

**S: Desteklenmeyen marka eklemek istiyorum, nasıl yaparım?**  
C: Model XML’i ve hata tablosu JSON’u ekleyin, yazılımda ilgili marka için case ekleyin.

---

## 11. Destek ve Lisans

MIT Lisansı ile özgürce kullanabilirsiniz.  
Yardım ve katkı için GitHub Issues veya Pull Request açabilirsiniz.
# KombiTest Otomatik Güncelleme Sistemi

## Özellikler
- Tüm marka hata kodu, test ve reset desteği (Vaillant, Demirdöküm, E.C.A., Bosch)
- **Firmware güncellemesi için kullanıcı onayı**
- **Model dosyası ve hata tabloları otomatik güncellenir**
- Tüm modeller ve hata tabloları artık `guncelle/models/` ve `guncelle/error_tables/` dizinlerinde tutulur

## Dizin Yapısı
```text
src/
guncelle/
  firmware_version_1.2.0.json
  firmware_version_1.1.0.json
  firmware_version_1.0.0.json
  release_notes_1.2.0.txt
  models/
    vaillant_ecotecplus_2024.xml
    demirdokum_neo_2023.xml
    eca_proteus_2022.xml
    bosch_condens_2025.xml
  error_tables/
    vaillant_error_table.json
    demirdokum_error_table.json
    eca_error_table.json
    bosch_error_table.json
data/
  diagnostic_menu.html
  update_menu.html
```

## Kullanım
1. Firmware güncellemesi için web arayüzünden onay alınır.
2. Model dosyaları ve hata tabloları internete bağlıysa Github'dan otomatik güncellenir.
3. İlk yüklemede `/data` klasörünü SPIFFS/LittleFS ile cihaza yüklemeyi unutmayın.

## Not
- Otomatik güncellenen dosyalar: `guncelle/models/` (model dosyaları), `guncelle/error_tables/` (hata tabloları)
- Firmware için her zaman kullanıcı onayı alınır.
---
