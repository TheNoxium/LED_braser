 #include "TaskTest.hpp"

static const char *TAG = __FILE__;

void TaskTest(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskTest start");

    for (;;)
    {
        try
        {

        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskTest");
        }

    }
    ESP_LOGE(TAG, "%s", "TaskTest end");
    vTaskDelete(NULL);
}
