 #include "TaskWebSocketServer.hpp"

static const char *TAG = __FILE__;

void TaskWebSocketServer(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskWebSocketServer start");

    for (;;)
    {
        try
        {
         vTaskDelay(10);
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskWebSocketServer");
        }

    }
    ESP_LOGE(TAG, "%s", "TaskWebSocketServer end");
    vTaskDelete(NULL);
}
