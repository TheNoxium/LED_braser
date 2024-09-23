#include "TaskLed.hpp"

static const char *TAG = __FILE__;

// extern Adafruit_NeoPixel strip;

bool state = 0;

// void led_green()
// {
//     state = 0;
// }

// void led_red()
// {
//     state = 0;
// }

void TaskLed(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskLed start");

    for (;;)
    {
        try
        {

            // if (state == 0)
            // {
            //     // Затухание и свечение по одному светодиоду
            //     for (int i = 0; i < NUM_LEDS; i++)
            //     {
            //         // Свечение основного светодиода
            //         for (int j = 0; j <= 255; j++)
            //         { // Увеличиваем яркостьП
            //             // Устанавливаем яркость для текущего светодиода
            //             strip.setPixelColor(i, strip.Color(0, j, 0)); // Яркий зеленый
            //             // Устанавливаем тусклый зеленый для остальных
            //             for (int k = 0; k < NUM_LEDS; k++)
            //             {
            //                 if (k != i)
            //                 {
            //                     strip.setPixelColor(k, strip.Color(0, j / 4, 0)); // Тусклый зеленый
            //                 }
            //             }
            //             strip.show();
            //             vTaskDelay(5); // Задержка для контроля скорости
            //         }

            //         // Затухание основного светодиода
            //         for (int j = 255; j >= 0; j--)
            //         { // Уменьшаем яркость
            //             // Устанавливаем яркость для текущего светодиода
            //             strip.setPixelColor(i, strip.Color(0, j, 0)); // Яркий зеленый
            //             // Устанавливаем тусклый зеленый для остальных
            //             for (int k = 0; k < NUM_LEDS; k++)
            //             {
            //                 if (k != i)
            //                 {
            //                     strip.setPixelColor(k, strip.Color(0, j / 4, 0)); // Тусклый зеленый
            //                 }
            //             }
            //             strip.show();
            //             vTaskDelay(5); // Задержка для контроля скорости
            //         }
            //     }
            // }
            // else
            // {
            //     // Затухание и свечение по одному светодиоду
            //     for (int i = 0; i < NUM_LEDS; i++)
            //     {
            //         // Свечение основного светодиода
            //         for (int j = 0; j <= 255; j++)
            //         { // Увеличиваем яркость
            //             // Устанавливаем яркость для текущего светодиода
            //             strip.setPixelColor(i, strip.Color(j, 0, 0)); // Яркий красный
            //             // Устанавливаем тусклый красный для остальных
            //             for (int k = 0; k < NUM_LEDS; k++)
            //             {
            //                 if (k != i)
            //                 {
            //                     strip.setPixelColor(k, strip.Color(j / 4, 0, 0)); // Тусклый красный
            //                 }
            //             }
            //             strip.show();
            //             vTaskDelay(5); // Задержка для контроля скорости
            //         }

            //         // Затухание основного светодиода
            //         for (int j = 255; j >= 0; j--)
            //         { // Уменьшаем яркость
            //             // Устанавливаем яркость для текущего светодиода
            //             strip.setPixelColor(i, strip.Color(j, 0, 0)); // Яркий красный
            //             // Устанавливаем тусклый красный для остальных
            //             for (int k = 0; k < NUM_LEDS; k++)
            //             {
            //                 if (k != i)
            //                 {
            //                     strip.setPixelColor(k, strip.Color(j / 4, 0, 0)); // Тусклый красный
            //                 }
            //             }
            //             strip.show();
            //             vTaskDelay(5); // Задержка для контроля скорости
            //         }
            //     }
            // }
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskLed");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskLed end");
    vTaskDelete(NULL);
}
