#include "TaskCounter.hpp"
// #include "TaskLed.hpp"

static const char *TAG = __FILE__;

extern Adafruit_NeoPixel strip;

int state_giro;
int state_piezo;
int flag_led = 0;
int count = 0;
int HP = 15;
int frequency = 1000;

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

            state_piezo = digitalRead(PIEZO_SENSOR_PIN); // Читаем состояние пина
            state_giro = digitalRead(GERO_PIN);
            // ESP_LOGI(TAG, "state_giro - %d", state_giro);

            if (flag_led != 6)
            {
                if (state_piezo == HIGH)
                {

                    ESP_LOGI(TAG, "Был удар>");

                    tone(PIEZO_SOUND_PIN, frequency); // Частота

                    vTaskDelay(300);
                    noTone(PIEZO_SOUND_PIN);

                    count++;

                     ESP_LOGI(TAG, "Счетчик ударов %d", count);
                }
            }

            if (count > HP * 0.2 && flag_led == 0)
            {
                led_yellow_green();
                frequency = 800;
                flag_led = 1;
            }
            else if (count > HP * 0.4 && flag_led == 1)
            {
                led_yellow();
                frequency = 600;
                flag_led = 2;
            }
            else if (count > HP * 0.5 && flag_led == 2)
            {
                led_yellow_orange();
                frequency = 500;
                flag_led = 3;
            }
            else if (count > HP * 0.7 && flag_led == 3)
            {
                led_orange();
                frequency = 400;
                flag_led = 4;
            }
            else if (count > HP * 0.8 && flag_led == 4)
            {
                frequency = 300;
                led_orange_red();
                flag_led = 5;
            }
            else if (count == HP && flag_led == 5)
            {

                ESP_LOGI(TAG, "хп кончилось");
                led_red();
                flag_led = 6;
                tone(PIEZO_SOUND_PIN, 200); // Частота

                vTaskDelay(300);
                noTone(PIEZO_SOUND_PIN);
            }

            if (state_giro == LOW && flag_led == 6)
            { // Если геркон замкнут
                ESP_LOGW(TAG, "%s", "Гиркон замкнут");
                count = 0;
                flag_led = 0;
                led_green();
                state_giro = HIGH;
                frequency = 1000;
            }

            vTaskDelay(2);
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskCounter");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskCounter end");
    vTaskDelete(NULL);
}
