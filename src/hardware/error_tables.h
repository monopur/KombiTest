#pragma once
struct ErrorEntry { uint16_t code; const char* description; };

// Vaillant hata kodları
static const ErrorEntry vaillant_error_table[] = {
    {0xF22, "F.22 – Su eksikliği"},
    {0xF23, "F.23 – Sirkülasyon düşük"},
    {0xF24, "F.24 – Aşırı ısınma"},
    {0xF28, "F.28 – Ateşleme yok"},
    {0xF29, "F.29 – Alev kaybı"},
    {0xFFFF, "Bilinmeyen arıza kodu"}
};

// Demirdöküm hata kodları
static const ErrorEntry demirdokum_error_table[] = {
    {0x01, "E01 – Ateşleme başarısız"},
    {0x02, "E02 – Alev kaybı"},
    {0x05, "E05 – Fan arızası"},
    {0x06, "E06 – Sıcaklık sensörü arızası"},
    {0x10, "E10 – Su basıncı düşük"},
    {0xFFFF, "Bilinmeyen arıza kodu"}
};

// ECA hata kodları
static const ErrorEntry eca_error_table[] = {
    {0x01, "E01 – Ateşleme başarısız"},
    {0x02, "E02 – Alev kaybı"},
    {0x05, "E05 – Fan arızası"},
    {0x09, "E09 – NTC sensörü arızası"},
    {0x10, "E10 – Su basıncı düşük"},
    {0xFFFF, "Bilinmeyen arıza kodu"}
};

// Yardımcı fonksiyon
inline String error_description(const ErrorEntry* table, uint16_t code) {
    for (int i = 0; table[i].code != 0xFFFF; i++)
        if (table[i].code == code) return String(table[i].description);
    return "Bilinmeyen arıza kodu";
}