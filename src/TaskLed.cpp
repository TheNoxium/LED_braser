#include "TaskLed.hpp"

static const char *TAG = __FILE__;
extern Adafruit_NeoPixel strip;

int led = 0;

void led_green()
{
    led = 0;
    ESP_LOGD(TAG, "led = 0");
}

void led_red()
{
    led = 1;
    ESP_LOGD(TAG, "led = 1");
}

void led_yellow()
{
    led = 2;
    ESP_LOGD(TAG, "led = 2");
}

void led_orange()
{
    led = 3;
    ESP_LOGD(TAG, "led = 3");
}

void led_violet()
{
    led = 4;
    ESP_LOGD(TAG, "led = 4");
}

void led_blue()
{
    led = 5;
    ESP_LOGD(TAG, "led = 5");
}

void TaskLed(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskLed start");

    for (;;)
    {
        try
        {

            switch (led)
            {
            case 0: // ЗЕЛЕНЫЙ
                // Затухание и свечение по одному светодиоду
                for (int i = 0; i < NUM_LEDS && led == 0; i++)
                {
                    // Свечение основного светодиода
                    for (int j = 30; j <= 255 && led == 0; j++)
                    { // Увеличиваем яркостьП
                        // Устанавливаем яркость для текущего светодиода
                        strip.setPixelColor(i, strip.Color(0, j, 0)); // Яркий зеленый
                        // Устанавливаем тусклый зеленый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 0; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(0, j / 4, 0)); // Тусклый зеленый
                            }
                        }
                        strip.show();
                        vTaskDelay(1); // Задержка для контроля скорости
                    }

                    // Затухание основного светодиода
                    for (int j = 255; j >= 30 && led == 0; j--)
                    { // Уменьшаем яркость
                        // Устанавливаем яркость для текущего светодиода
                        strip.setPixelColor(i, strip.Color(0, j, 0)); // Яркий зеленый
                        // Устанавливаем тусклый зеленый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 0; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(0, j / 4, 0)); // Тусклый зеленый
                            }
                        }
                        strip.show();
                        vTaskDelay(1); // Задержка для контроля скорости
                    }
                }
                break;
            case 1: // КАРСНЫЙ
                // Затухание и свечение по одному светодиоду
                for (int i = 0; i < NUM_LEDS && led == 1; i++)
                {
                    // Свечение основного светодиода
                    for (int j = 100; j <= 255 && led == 1; j++)
                    { // Увеличиваем яркость
                        // Устанавливаем яркость для текущего светодиода
                        strip.setPixelColor(i, strip.Color(j, 0, 0)); // Яркий красный
                        // Устанавливаем тусклый красный для остальных
                        for (int k = 0; k < NUM_LEDS && led == 1; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 4, 0, 0)); // Тусклый красный
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }

                    // Затухание основного светодиода
                    for (int j = 255; j >= 100 && led == 1; j--)
                    { // Уменьшаем яркость
                        // Устанавливаем яркость для текущего светодиода
                        strip.setPixelColor(i, strip.Color(j, 0, 0)); // Яркий красный
                        // Устанавливаем тусклый красный для остальных
                        for (int k = 0; k < NUM_LEDS && led == 1; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 4, 0, 0)); // Тусклый красный
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }
                }
                break;
            case 2: // ЖЕЛТЫЙ
                for (int i = 0; i < NUM_LEDS && led == 2; i++)
                {
                    // Свечение основного светодиода
                    for (int j = 100; j <= 255 && led == 2; j++)
                    {
                        // Устанавливаем яркость для текущего светодиода (желтый)
                        strip.setPixelColor(i, strip.Color(j, j, 0)); // Яркий желтый
                        // Устанавливаем тусклый желтый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 1; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 4, j / 4, 0)); // Тусклый желтый
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }

                    // Затухание основного светодиода
                    for (int j = 255; j >= 100 && led == 2; j--)
                    {
                        // Устанавливаем яркость для текущего светодиода (желтый)
                        strip.setPixelColor(i, strip.Color(j, j, 0)); // Яркий желтый
                        // Устанавливаем тусклый желтый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 2; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 4, j / 4, 0)); // Тусклый желтый
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }
                }
                break;
            case 3: // Оранжеввый
                for (int i = 0; i < NUM_LEDS && led == 3; i++)
                {
                    // Свечение основного светодиода
                    for (int j = 100; j <= 255 && led == 3; j++)
                    {
                        // Устанавливаем яркость для текущего светодиода (темно-оранжевый)
                        strip.setPixelColor(i, strip.Color(j, j / 2, 0)); // Яркий темно-оранжевый
                        // Устанавливаем тусклый темно-оранжевый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 3; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 4, j / 8, 0)); // Тусклый темно-оранжевый
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }

                    // Затухание основного светодиода
                    for (int j = 255; j >= 100 && led == 3; j--)
                    {
                        // Устанавливаем яркость для текущего светодиода (темно-оранжевый)
                        strip.setPixelColor(i, strip.Color(j, j / 2, 0)); // Яркий темно-оранжевый
                        // Устанавливаем тусклый темно-оранжевый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 3; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 4, j / 8, 0)); // Тусклый темно-оранжевый
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }
                }
                break;
            case 4: // Фиолетоывый
                for (int i = 0; i < NUM_LEDS && led == 4; i++)
                {
                    // Свечение основного светодиода
                    for (int j = 100; j <= 255 && led == 4; j++)
                    {
                        // Устанавливаем яркость для текущего светодиода (фиолетовый)
                        strip.setPixelColor(i, strip.Color(j, 0, j)); // Фиолетовый
                        // Устанавливаем тусклый фиолетовый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 4; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 8, 0, j / 8)); // Тусклый фиолетовый
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }

                    // Затухание основного светодиода
                    for (int j = 255; j >= 100 && led == 4; j--)
                    {
                        // Устанавливаем яркость для текущего светодиода (фиолетовый)
                        strip.setPixelColor(i, strip.Color(j, 0, j)); // Фиолетовый
                        // Устанавливаем тусклый фиолетовый для остальных
                        for (int k = 0; k < NUM_LEDS && led == 4; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(j / 8, 0, j / 8)); // Тусклый фиолетовый
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }
                }
                break;
            case 5: // синий
                // Затухание и свечение по одному светодиоду
                for (int i = 0; i < NUM_LEDS && led == 5; i++)
                {
                    // Свечение основного светодиода
                    for (int j = 100; j <= 255 && led == 5; j++)
                    { // Увеличиваем яркость
                        // Устанавливаем яркость для текущего светодиода
                        strip.setPixelColor(i, strip.Color(0, 0, j)); // Яркий синий
                        // Устанавливаем тусклый синий для остальных
                        for (int k = 0; k < NUM_LEDS && led == 5; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(0, 0, j / 4)); // Тусклый синий
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }

                    // Затухание основного светодиода
                    for (int j = 255; j >= 100 && led == 5; j--)
                    { // Уменьшаем яркость
                        // Устанавливаем яркость для текущего светодиода
                        strip.setPixelColor(i, strip.Color(0, 0, j)); // Яркий синий
                        // Устанавливаем тусклый синий для остальных
                        for (int k = 0; k < NUM_LEDS && led == 5; k++)
                        {
                            if (k != i)
                            {
                                strip.setPixelColor(k, strip.Color(0, 0, j / 4)); // Тусклый синий
                            }
                        }
                        strip.show();
                        vTaskDelay(2); // Задержка для контроля скорости
                    }
                }
                break;
            case 6:
              break;
            }
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskLed");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskLed end");
    vTaskDelete(NULL);
}