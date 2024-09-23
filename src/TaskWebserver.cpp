#include "TaskWebserver.hpp"

static const char *TAG = __FILE__;

extern Configuration configuration;

GyverPortal ui(&LittleFS);

#define AP_SSID "terratok2"
#define AP_PASS "12QW!@QW"

void build()
{
    ESP_LOGV(TAG, "%s", "Build page start");

    GP.BUILD_BEGIN(800); // ширина колонки

    GP.PAGE_TITLE("OCPP настройка");

    GP.THEME(GP_DARK);
    // GP.THEME(GP_LIGHT);

    // при ширине меньше 600 GRID отключится (блоки пойдут по вертикали)
    GP.GRID_RESPONSIVE(600);

    GP.TITLE("Настройка");
    GP.HR();

    M_GRID(
        M_BLOCK_TAB(
            "Настройка системы",

            // M_BOX(GP.LABEL("Количество Хит Поинтов"); GP.SELECT("HP", "2", configuration.config_SISTEM.HP););
            M_BOX(GP.LABEL("Количество Хит Поинтов"); GP.NUMBER("HP", "", configuration.config_SISTEM.HP););


            GP.ALERT("altT", "Alert Text");
            GP.BUTTON("btnReset", "Reset");
            GP.UPDATE_CLICK("altT", "btnReset"););

        ;);

    // M_GRID(
    //     M_BLOCK_TAB(
    //         "Настройка счетчика",
    //         M_BOX(GP.LABEL("Вкл/выкл"); GP.SWITCH("swCounter", configuration.config_COUNTER.ENABLED);););

    //     M_BLOCK_TAB(
    //         "Тут может быть ваша рекламма", ););

    M_BLOCK_TAB(
        "Системная информация",
        GP.SYSTEM_INFO(VERSION_FIRMWARE);

    );

    M_BLOCK_TAB(
        "Файловая система",
        GP.FILE_MANAGER(&LittleFS);

    );

    GP.BUILD_END();

    ESP_LOGV(TAG, "%s", "Build page end");
}

void action()
{
    if (ui.click())
    {
        if (ui.click("HP"))
        {
            ESP_LOGI(TAG, "HP = %d ", ui.getInt("HP")); // настройка тока 16/32
            configuration.config_SISTEM.HP = ui.getInt("HP");
            configuration.set_station_config();
        }

    //     if (ui.click("swOSPP"))
    //     {
    //         ESP_LOGI(TAG, "swOSPP = %d ", ui.getBool("swOSPP")); // свич настройка OCPP
    //         configuration.config_OCPP.ENABLED = ui.getBool("swOSPP");
    //         configuration.set_ocpp_config();
    //     }
        // if (ui.clickString("HP", configuration.config_SISTEM.HP)) // изменение полей OCPP ID
        // {

        //     ESP_LOGI(TAG, "HP = %s ", ui.getString("HP"));
        //     configuration.config_SISTEM.HP = ui.getString("HP");
        //     configuration.set_station_config();
        // }
    //     if (ui.clickString("url", configuration.config_OCPP.URL)) // изменение полей OCPP url
    //     {

    //         ESP_LOGI(TAG, "url = % ", ui.getString("url"));
    //         configuration.config_OCPP.URL = ui.getString("url");
    //         configuration.set_ocpp_config();
    //     }

    //     if (ui.click("swCounter"))
    //     {
    //         ESP_LOGI(TAG, "swCounter = %d ", ui.getBool("swCounter")); // свич настройка OCPP
    //         configuration.config_COUNTER.ENABLED = ui.getBool("swCounter");
    //         configuration.set_counter_config();
    //     }

        if (ui.click("btnReset")) // кнопка ресет
        {
            ESP_LOGI(TAG, "%s", "Нажата кнопка RESET");
            ui.answer(1);
            vTaskDelay(500);
            ESP.restart();
        }
    }
}

void TaskWebserver(void *pvParameters)
{
    (void)pvParameters;

    ESP_LOGI(TAG, "%s", "TaskWebserver start");
    ESP_LOGV(TAG, "%s", "Init WebServer");

    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        ESP_LOGE(TAG, "LittleFS Mount failed");
        return;
    }
    else
    {
        ESP_LOGD(TAG, "LittleFS Mount conplete");
    }

    // WiFi.mode(WIFI_AP);
    // WiFi.softAP("ABOBA");

    if (!LittleFS.begin())
        Serial.println("FS Error");

    // WiFi.mode(WIFI_STA);
    // WiFi.begin(AP_SSID, AP_PASS);
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     delay(500);
    //     Serial.print(".");
    // }
    // Serial.println(WiFi.localIP());

    // ESP_LOGI(TAG, "%d", WiFi.localIP());
    // Serial.println(WiFi.localIP());

    WiFi.mode(WIFI_AP);
    WiFi.softAP("LED_braser_wifi");

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    ESP_LOGI(TAG, "%d", WiFi.localIP());

    // подключаем конструктор и запускаем
    ui.attachBuild(build);
    ui.attach(action);
    ui.start();

    for (;;)
    {
        try
        {
            ui.tick();
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskWebserver");
        }
    }

    ESP_LOGE(TAG, "%s", "TaskWebserver end");
    vTaskDelete(NULL);
}
