# ESP32 Kombi Kart Test ve Simülasyon Sistemi

Bu proje, farklı marka ve model (yoğuşmalı / yoğuşmasız) kombi elektronik kartlarının giriş/çıkışlarını test etmek ve simüle etmek için geliştirilmiştir.  
Tüm giriş/çıkış/parametreler dinamik model dosyası (JSON/XML) ile yönetilir.  
Web arayüzünden canlı izleme, test başlatma ve model düzenleme mümkündür.

---

## Derleyici ve Uyumluluk

- **PlatformIO (VSCode ile):** Tam uyumlu, önerilir.
- **Arduino IDE:** Tam uyumlu.
- **Espressif ESP-IDF:** Küçük değişikliklerle uyarlanabilir.

### Tavsiye edilen sürümler:
- **ESP32 Arduino Core:** >= 2.0.5
- **PlatformIO platform-espressif32:** >= 6.1.0
- **Kicad:** >= 6.0

## Bağımlı Kütüphaneler

- ArduinoJson (>= 6.x)
- TinyXML2 (>= 9.x)
- ESPAsyncWebServer
- SPIFFS veya LittleFS (ESP32 dosya sistemi)
- Donanım: Wire, SPI, ledc (PWM), vs.

---

## Klasör ve Dosya Yapısı

```
proje_kok_dizini/
├── README.md
├── platformio.ini
├── src/
│   ├── main.cpp
│   ├── settings/
│   │   ├── model_settings.h
│   │   └── model_settings.cpp
│   ├── hardware/
│   │   ├── pinmap_dynamic.h
│   │   ├── fan_pwm_driver.cpp
│   │   ├── gas_valve_driver.cpp
│   │   └── ntc_sim_driver.cpp
│   └── app/
│       ├── hardware_manager.cpp
│       └── test_engine.cpp
├── data/
│   ├── model_editor.html
│   └── live_monitor.html
├── models/
│   ├── demirdokum_neo_2023.xml / .json
│   ├── bosch_condense_2024.xml / .json
│   ├── eca_proteus_2022.xml / .json
│   ├── baymak_duotec_2021.xml / .json
│   ├── vaillant_ecotecplus_2024.xml / .json
│   ├── daikin_premix_2024.xml / .json
│   ├── ... (tüm diğer marka/model xml+json dosyaları)
│   └── örnek_klasik_yoğuşmasız.xml / .json
├── hardware/
│   ├── hardware_guide.md
│   └── esp32_kombi.csv
├── kicad/
│   ├── esp32_kombi.pro
│   ├── esp32_kombi.sch
│   ├── esp32_kombi.kicad_pcb
│   ├── esp32_kombi.lib
│   ├── esp32_kombi-footprints.pretty/
│   │   └── .keep
│   └── esp32_kombi.net
└── README_KICAD.md
```

---

## Kurulum ve Kullanım

1. **Kütüphaneleri yükleyin** (Arduino IDE Library Manager veya PlatformIO ile).
2. Dosya ve klasörleri yukarıdaki yapıya göre düzenleyin.
3. Web arayüzü dosyalarını (`data/`) SPIFFS/LittleFS ile ESP32'ye yükleyin.
4. Model dosyalarını (`models/`) web arayüzüyle veya doğrudan SPIFFS/LittleFS ile cihaza aktarın.
5. PlatformIO veya Arduino IDE ile derleyip yükleyin.

---

Daha fazla bilgi için:
- [Donanım bağlantı rehberi → hardware/hardware_guide.md](hardware/hardware_guide.md)
- [Kicad proje ve PCB açıklaması → README_KICAD.md](README_KICAD.md)