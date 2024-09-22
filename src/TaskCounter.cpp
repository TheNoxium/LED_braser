 #include "TaskCounter.hpp"

static const char *TAG = __FILE__;

void TaskCounter(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskCounter start");

    for (;;)
    {
        try
        {

        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskCounter");
        }

    }
    ESP_LOGE(TAG, "%s", "TaskCounter end");
    vTaskDelete(NULL);
}
