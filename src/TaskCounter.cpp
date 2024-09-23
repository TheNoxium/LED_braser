#include "TaskCounter.hpp"

static const char *TAG = __FILE__;

extern Adafruit_NeoPixel strip;

bool state = 0;

void grean_leads()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Яркий зеленый
    }
    strip.show(); // Обновление состояния
}

void red_leads()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip.setPixelColor(i, strip.Color(255, 0, 0)); // Яркий красный
    }
    strip.show(); // Обновление состояния
}

void TaskCounter(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskCounter start");

    pinMode(PIEZO_SENSOR_PIN, INPUT); // Устанавливаем пин D18 как вход

    pinMode(PIEZO_SOUND_PIN, OUTPUT); // Устанавливаем пин как выход

    for (;;)
    {
        try
        {

            int signal = digitalRead(PIEZO_SENSOR_PIN); // Читаем состояние пина

            if (signal == HIGH)
            {

                state = 1;
                red_leads();
                ESP_LOGI(TAG, "Был удар>");

                tone(PIEZO_SOUND_PIN, 500); // Частота

                // vTaskDelay(500);
                delay(1000);
                noTone(PIEZO_SOUND_PIN);
            }
            else
            {

                // ESP_LOGI(TAG, "Сигнал низкий");
            }

            if (state == 0)
            {
                grean_leads();
            }
            if (state == 1)
            {

            }
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskCounter");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskCounter end");
    vTaskDelete(NULL);
}
