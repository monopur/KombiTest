# KombiTest: Akıllı Diagnostik ve Otomatik Güncelleme Sistemi

## Özellikler
- **Tek RX/TX ile çoklu marka (Vaillant, Demirdöküm, E.C.A.) hata okuma ve reset**
- **Donanım sürümüne uygun firmware güncellemesi** (repo'dan otomatik kontrol, kullanıcı onaylı)
- **Model dosyası eksikse otomatik senkronizasyon**
- **Kullanıcıya web arayüzüyle güncelleme ve test/reset menüsü**
- **Güncelleme tercihi menüden yönetilebilir**
- **Tüm dosya yapısı ve API'ler sade, entegre ve anlaşılır**

## Dizin Yapısı
```text
src/
  main.cpp
  hardware/
    diagnostic_driver.cpp
    error_tables.h
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
guncelle/
  firmware_version_1.2.0.json
  firmware_version_1.1.0.json
  firmware_version_1.0.0.json
  release_notes_1.2.0.txt
data/
  diagnostic_menu.html
  update_menu.html
```

## Kurulum & Kullanım
1. Donanım sürümünüzü `src/settings/hw_version.h` ile tanımlayın.
2. Yazılımı ESP32'ye yükleyin.
3. Cihaz açılışında otomatik olarak güncelleme kontrolü ve model dosyası senkronizasyonu yapılır.
4. Web arayüzünden test/reset ve güncelleme işlemlerini yönetebilirsiniz.

## Güncelleme Sistemi
- Her firmware için bir JSON dosyası `guncelle/` altında tutulur.
- `"hw_compat"` ile donanım uyumluluğu sağlanır.
- Cihaz, sadece kendi donanımına uygun en yeni sürümü önerir.
- Model dosyaları `models/` altında tutulur; eksikse cihaz otomatik indirir.

## Lisans
MIT
