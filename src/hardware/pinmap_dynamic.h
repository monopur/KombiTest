#pragma once
#include <map>
#include <Arduino.h>

// Tüm marka/model için tek diagnostik RX/TX pini kullanılacak!
static std::map<String, int> modelPinMapping = {
    {"diag_rx", 16},
    {"diag_tx", 17},
};