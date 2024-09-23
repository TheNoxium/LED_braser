#include "Configuration.hpp"

static const char *TAG = __FILE__;

extern Configuration configuration;
using namespace ArduinoJson;

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

void Configuration::get_configs()
{
    get_station_config();
}

void Configuration::get_station_config(void)
{
    ESP_LOGD(TAG, "Read config from file %s start", FILE_HP);

    File file = LittleFS.open(FILE_HP, FILE_READ);

    StaticJsonDocument<1024> root;
    DeserializationError error = deserializeJson(root, file);

    if (error)
    {
        file.close();
        default_station_config();
        ESP_LOGE(TAG, "ERROR %s", FILE_HP);
    }
    else
    {
        // config_STATION.TYPE = root["TYPE"].as<int>();
        config_HP.HP = root["HP"].as<int>();
        // config_STATION.FORCED = root["FORCED"].as<bool>();
        file.close();
        ESP_LOGW(TAG, "HP -  %d", configuration.config_HP.HP);
        ESP_LOGD(TAG, "Close file %s", FILE_HP);
    }

    file.close();

    ESP_LOGD(TAG, "Read config from file %s end", FILE_HP);
}

void Configuration::set_station_config(void)
{
    ESP_LOGD(TAG, "Save config to file %s start", FILE_HP);

    if (LittleFS.remove(FILE_HP))
    {
        ESP_LOGD(TAG, "%s - file deleted", FILE_HP);
    }
    else
    {
        ESP_LOGE(TAG, "%s - delete failed", FILE_HP);
    }

    File file = LittleFS.open(FILE_HP, FILE_WRITE);

    if (!file || file.isDirectory())
    {
        ESP_LOGE(TAG, "Failed to create file -  %s", FILE_HP);
        return;
    }

    StaticJsonDocument<1024> root;

    // root["TYPE"] = config_STATION.TYPE;
    root["POWER"] = config_HP.HP;
    // root["FORCED"] = config_STATION.FORCED;

    if (serializeJson(root, file) == 0)
    {
        ESP_LOGE(TAG, "Failed to write to file %s", FILE_HP);
    }

    file.close();
    ESP_LOGD(TAG, "Close file %s", FILE_HP);

    ESP_LOGD(TAG, "Save config to file %s end", FILE_HP);

    get_station_config();
}

void Configuration::default_station_config(void)
{
    ESP_LOGD(TAG, "Save default config to file %s start", FILE_HP);

    if (LittleFS.remove(FILE_HP))
    {
        ESP_LOGE(TAG, "%s - file deleted", FILE_HP);
    }
    else
    {
        ESP_LOGE(TAG, "%s - delete failed", FILE_HP);
    }

    File file = LittleFS.open(FILE_HP, FILE_WRITE);

    if (!file || file.isDirectory())
    {
        ESP_LOGE(TAG, "Failed to create file -  %s", FILE_HP);
        return;
    }

    StaticJsonDocument<1024> root;

    // root["TYPE"] = DEFAULT_STATION_TYPE;
    root["HP"] = DEFAULT_HP;
    // root["FORCED"] = DEFAULT_FORCED;

    if (serializeJson(root, file) == 0)
    {
        ESP_LOGE(TAG, "Failed to write to file %s", FILE_HP);
    }

    file.close();
    ESP_LOGD(TAG, "Close file %s", FILE_HP);

    ESP_LOGD(TAG, "Save config to file %s end", FILE_HP);

    get_station_config();
}
