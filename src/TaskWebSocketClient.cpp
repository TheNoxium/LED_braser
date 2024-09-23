 #include "TaskWebSocketClient.hpp"

static const char *TAG = __FILE__;

void TaskWebSocketClient(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskWebSocketClient start");

    for (;;)
    {
        try
        {
        vTaskDelay(10);
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskWebSocketClient");
        }

    }
    ESP_LOGE(TAG, "%s", "TaskWebSocketClient end");
    vTaskDelete(NULL);
}
