#pragma once
#include <Arduino.h>
#include <vector>

/*
 * ModelSettings: Kombi model dosyalarını (JSON/XML) okuyup hafızada tutar.
 * - Her modelin giriş/çıkış/parametre tanımlarını dinamik olarak içerir.
 */

struct IOEntry {
    String id;
    String type;
    String label;
    int ohm;
};

struct ParameterEntry {
    String key;
    String value;
    String desc;
};

class ModelSettings {
public:
    bool loadFromJson(const String& file);
    bool loadFromXml(const String& file);
    bool saveToJson(const String& file) const;
    bool saveToXml(const String& file) const;
    String getModelName() const;
    String getDescription() const;
    const std::vector<IOEntry>& getInputs() const;
    const std::vector<IOEntry>& getOutputs() const;
    const std::vector<ParameterEntry>& getParameters() const;
    String getParam(const String& key) const;
    void setParam(const String& key, const String& value);
    String toJson() const;

private:
    String modelName;
    String description;
    std::vector<IOEntry> inputs;
    std::vector<IOEntry> outputs;
    std::vector<ParameterEntry> parameters;
};
extern ModelSettings modelSettings;