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
    ESP_LOGD(TAG, "Read config from file %s start", FILE_SISTEM);

    File file = LittleFS.open(FILE_SISTEM, FILE_READ);

    StaticJsonDocument<1024> root;
    DeserializationError error = deserializeJson(root, file);

    if (error)
    {
        file.close();
        default_station_config();
        ESP_LOGE(TAG, "ERROR %s", FILE_SISTEM);
    }
    else
    {
        // config_STATION.TYPE = root["TYPE"].as<int>();
        config_SISTEM.HP = root["HP"].as<int>();
        config_SISTEM.SOUND_FREEZE = root["SOUND_FREEZE"].as<int>();

        file.close();
        ESP_LOGW(TAG, "HP -  %d", configuration.config_SISTEM.HP);
        ESP_LOGW(TAG, "SOUND_FREEZE -  %d", configuration.config_SISTEM.SOUND_FREEZE);
        ESP_LOGD(TAG, "Close file %s", FILE_SISTEM);
    }

    file.close();

    ESP_LOGD(TAG, "Read config from file %s end", FILE_SISTEM);
}

void Configuration::set_station_config(void)
{
    ESP_LOGD(TAG, "Save config to file %s start", FILE_SISTEM);

    if (LittleFS.remove(FILE_SISTEM))
    {
        ESP_LOGD(TAG, "%s - file deleted", FILE_SISTEM);
    }
    else
    {
        ESP_LOGE(TAG, "%s - delete failed", FILE_SISTEM);
    }

    File file = LittleFS.open(FILE_SISTEM, FILE_WRITE);

    if (!file || file.isDirectory())
    {
        ESP_LOGE(TAG, "Failed to create file -  %s", FILE_SISTEM);
        return;
    }

    StaticJsonDocument<1024> root;

    // root["TYPE"] = config_STATION.TYPE;
    root["HP"] = config_SISTEM.HP;
    root["SOUND_FREEZE"] = config_SISTEM.SOUND_FREEZE;

    if (serializeJson(root, file) == 0)
    {
        ESP_LOGE(TAG, "Failed to write to file %s", FILE_SISTEM);
    }

    file.close();
    ESP_LOGD(TAG, "Close file %s", FILE_SISTEM);

    ESP_LOGD(TAG, "Save config to file %s end", FILE_SISTEM);

    get_station_config();
}

void Configuration::default_station_config(void)
{
    ESP_LOGD(TAG, "Save default config to file %s start", FILE_SISTEM);

    if (LittleFS.remove(FILE_SISTEM))
    {
        ESP_LOGE(TAG, "%s - file deleted", FILE_SISTEM);
    }
    else
    {
        ESP_LOGE(TAG, "%s - delete failed", FILE_SISTEM);
    }

    File file = LittleFS.open(FILE_SISTEM, FILE_WRITE);

    if (!file || file.isDirectory())
    {
        ESP_LOGE(TAG, "Failed to create file -  %s", FILE_SISTEM);
        return;
    }

    StaticJsonDocument<1024> root;

    // root["TYPE"] = DEFAULT_STATION_TYPE;
    root["HP"] = DEFAULT_HP;
    root["SOUND_FREEZE"] = DEFAULT_SOUND_FREEZE;

    if (serializeJson(root, file) == 0)
    {
        ESP_LOGE(TAG, "Failed to write to file %s", FILE_SISTEM);
    }

    file.close();
    ESP_LOGD(TAG, "Close file %s", FILE_SISTEM);

    ESP_LOGD(TAG, "Save config to file %s end", FILE_SISTEM);

    get_station_config();
}
