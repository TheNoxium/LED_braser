#include "TaskCounter.hpp"

static const char *TAG = __FILE__;

extern Adafruit_NeoPixel strip;

bool state = 0;
bool flag = 1;

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

    pinMode(GERO_PIN, INPUT_PULLUP);

    for (;;)
    {
        try
        {

            int signal = digitalRead(PIEZO_SENSOR_PIN); // Читаем состояние пина

            if (signal == HIGH)
            {

                state = 1;

                ESP_LOGI(TAG, "Был удар>");
            }

            if (state == 0)
            {
                if (flag == 1)
                {
                    grean_leads();
                    flag = 0;
                }
            }
            else if (state == 1)
            {
                if (flag == 0)
                {
                    ESP_LOGI(TAG, "Б123123123");
                    red_leads();
                    tone(PIEZO_SOUND_PIN, 500); // Частота

                    // vTaskDelay(500);
                    delay(1000);
                    noTone(PIEZO_SOUND_PIN);
                    flag = 1;
                }

                int state1 = digitalRead(GERO_PIN);
                if (state1 == HIGH)
                { // Если геркон замкнут
                     Serial.println("Геркон замкнут");
                    // Здесь можно добавить код для выполнения действия
                    state = 0;


                } else{Serial.println("Геркон говно");}

            }

            vTaskDelay(1);
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskCounter");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskCounter end");
    vTaskDelete(NULL);
}
