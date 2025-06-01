# KombiTest: Bosch Desteği ve Dinamik Hata Tablosu Güncellemesi

## Yeni Özellikler
- Bosch marka kombi desteği (test, reset, hata kodu okuma)
- Tüm hata tabloları (Bosch dahil) dinamik olarak repo'dan otomatik güncellenir
- Bosch için örnek model dosyası ve güncellenmiş hata tablosu JSON'u
- Web menü ve API'de Bosch marka desteği
- Kicad donanım projesi: Bosch için ayrı RX/TX gerekmez, ortak hatta devam

## Kicad Proje Notu
Tüm markalar (Vaillant, Demirdöküm, E.C.A., Bosch) için RX/TX hatları ortaktır.
Eğer Bosch'a özel bir hat eklenirse, şema ve PCB dosyalarına "BOSCH_RX" ve "BOSCH_TX" olarak ekleyin ve açıklamada belirtin.

## /guncelle/error_tables/ altında tutulması gereken güncel hata tablosu JSON dosyaları:
- vaillant_error_table.json
- demirdokum_error_table.json
- eca_error_table.json
- bosch_error_table.json

## Web arayüzünde Bosch seçimi ve test/reset mümkündür.

## Firmware, model ve hata tablosu güncellemeleri repo'dan otomatik çekilir.
