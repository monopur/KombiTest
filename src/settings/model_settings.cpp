#include "model_settings.h"
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <TinyXML2.h>

/*
 * ModelSettings: JSON/XML dosyalarını okur ve giriş/çıkış/parametreleri dinamik olarak doldurur.
 */

ModelSettings modelSettings;

bool ModelSettings::loadFromJson(const String& file) {
    File f = SPIFFS.open(file, FILE_READ);
    if (!f) return false;
    String content = f.readString();
    f.close();
    DynamicJsonDocument doc(4096);
    DeserializationError err = deserializeJson(doc, content);
    if (err) return false;

    inputs.clear(); outputs.clear(); parameters.clear();

    auto m = doc["model"];
    modelName = m["name"].as<String>();
    description = m["description"].as<String>();

    for (JsonObject i : m["inputs"].as<JsonArray>()) {
        IOEntry e;
        e.id = i["id"].as<String>();
        e.type = i["type"].as<String>();
        e.label = i["label"].as<String>();
        e.ohm = i.containsKey("ohm") ? i["ohm"].as<int>() : 0;
        inputs.push_back(e);
    }
    for (JsonObject o : m["outputs"].as<JsonArray>()) {
        IOEntry e;
        e.id = o["id"].as<String>();
        e.type = o["type"].as<String>();
        e.label = o["label"].as<String>();
        outputs.push_back(e);
    }
    for (JsonObject p : m["parameters"].as<JsonArray>()) {
        ParameterEntry pe;
        pe.key = p["key"].as<String>();
        pe.value = p["value"].as<String>();
        pe.desc = p["desc"].as<String>();
        parameters.push_back(pe);
    }
    return true;
}

bool ModelSettings::loadFromXml(const String& file) {
    File f = SPIFFS.open(file, FILE_READ);
    if (!f) return false;
    String text = f.readString();
    f.close();
    tinyxml2::XMLDocument doc;
    if (doc.Parse(text.c_str()) != tinyxml2::XML_SUCCESS)
        return false;

    inputs.clear(); outputs.clear(); parameters.clear();

    auto* root = doc.FirstChildElement("model");
    if (!root) return false;
    auto* nameNode = root->FirstChildElement("name");
    if (nameNode) modelName = nameNode->GetText();
    auto* descNode = root->FirstChildElement("description");
    if (descNode) description = descNode->GetText();

    auto* ins = root->FirstChildElement("inputs");
    if (ins) {
        for (auto* i = ins->FirstChildElement("input"); i; i = i->NextSiblingElement("input")) {
            IOEntry e;
            e.id = i->Attribute("id") ? i->Attribute("id") : "";
            e.type = i->Attribute("type") ? i->Attribute("type") : "";
            e.label = i->Attribute("label") ? i->Attribute("label") : "";
            e.ohm = i->Attribute("ohm") ? atoi(i->Attribute("ohm")) : 0;
            inputs.push_back(e);
        }
    }
    auto* outs = root->FirstChildElement("outputs");
    if (outs) {
        for (auto* o = outs->FirstChildElement("output"); o; o = o->NextSiblingElement("output")) {
            IOEntry e;
            e.id = o->Attribute("id") ? o->Attribute("id") : "";
            e.type = o->Attribute("type") ? o->Attribute("type") : "";
            e.label = o->Attribute("label") ? o->Attribute("label") : "";
            outputs.push_back(e);
        }
    }
    auto* params = root->FirstChildElement("parameters");
    if (params) {
        for (auto* p = params->FirstChildElement("parameter"); p; p = p->NextSiblingElement("parameter")) {
            ParameterEntry pe;
            pe.key = p->Attribute("key") ? p->Attribute("key") : "";
            pe.value = p->Attribute("value") ? p->Attribute("value") : "";
            pe.desc = p->Attribute("desc") ? p->Attribute("desc") : "";
            parameters.push_back(pe);
        }
    }
    return true;
}

String ModelSettings::getParam(const String& key) const {
    for (const auto& p : parameters)
        if (p.key == key) return p.value;
    return "";
}
void ModelSettings::setParam(const String& key, const String& value) {
    for (auto& p : parameters)
        if (p.key == key) { p.value = value; return; }
}

String ModelSettings::getModelName() const { return modelName; }
String ModelSettings::getDescription() const { return description; }
const std::vector<IOEntry>& ModelSettings::getInputs() const { return inputs; }
const std::vector<IOEntry>& ModelSettings::getOutputs() const { return outputs; }
const std::vector<ParameterEntry>& ModelSettings::getParameters() const { return parameters; }

String ModelSettings::toJson() const {
    DynamicJsonDocument doc(4096);
    auto m = doc.createNestedObject("model");
    m["name"] = modelName;
    m["description"] = description;
    auto ins = m.createNestedArray("inputs");
    for (const auto& in : inputs) {
        auto io = ins.createNestedObject();
        io["id"] = in.id;
        io["type"] = in.type;
        io["label"] = in.label;
        io["ohm"] = in.ohm;
    }
    auto outs = m.createNestedArray("outputs");
    for (const auto& out : outputs) {
        auto io = outs.createNestedObject();
        io["id"] = out.id;
        io["type"] = out.type;
        io["label"] = out.label;
    }
    auto params = m.createNestedArray("parameters");
    for (const auto& p : parameters) {
        auto param = params.createNestedObject();
        param["key"] = p.key;
        param["value"] = p.value;
        param["desc"] = p.desc;
    }
    String out;
    serializeJson(doc, out);
    return out;
}