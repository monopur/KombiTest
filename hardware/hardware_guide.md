# Donanım Bağlantı Rehberi (ESP32 Kombi Test ve Simülasyon Cihazı)

- Tüm ESP32 pin atamaları ve karşılığı için esp32_kombi.csv dosyasını kullanın.
- Röle çıkışlarını AC’den izole edin.
- I2C hattına OLED ve Touch aynı hatta bağlanır.
- MCP41xxx dijital pot’lar SPI hattında, CS uçları ayrı ayrı atanır.
- PWM çıkışları için MOSFET kullanın.

# Kütüphane ve Versiyon Notları

- ESP32 Arduino Core >= 2.0.5 önerilir.
- PlatformIO platform-espressif32 >= 6.1.0 önerilir.
- ArduinoJson >= 6.21.x
- TinyXML2 >= 9.x
- ESPAsyncWebServer (en son sürüm)

Daha fazla bilgi için README.md dosyasına bakınız.
