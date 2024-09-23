#include "TaskWebSocketServer.hpp"

static const char *TAG = __FILE__;

extern int count, SOUND_FREEZE, HP;
extern bool flag_server;

// Массив для отправки
unsigned long sdata[3]{0, 0, 0};

// Массив для получения
int rdata[3]{0};

// Кол-во элементов массива для получения
const size_t glen = sizeof(rdata) / sizeof(rdata[0]);

// Создаём объект сервера
WebSocketsServer webSocket = WebSocketsServer(81);

/* Callback функция события WebSocket.
 * Парамтетры:
 * num - номер клиента
 * type - тип событыя
 * payload - указатель на данные
 * length - размер данных
 */
void webSocketServerEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{

    // Если тип данных двоичный и их размер не нулевой
    if (type == WStype_BIN && length > 0)
    {

        // Преобразуем тип данных
        const int *tmp = (int *)payload;

        // Вычисляем размер данных нового типа
        size_t len = length / sizeof(&rdata);

        // Записываем в глобальную переменную
        for (size_t i = 0; i < len && i < glen; i++)
        {
            rdata[i] = tmp[i];
        }

        // Отвечаем клиенту
        sdata[0] = HP;
        sdata[1] = SOUND_FREEZE;
        sdata[2] = count;

        webSocket.sendBIN(num, (uint8_t *)sdata, sizeof(sdata));
    }
}

void TaskWebSocketServer(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskWebSocketServer start");

    Serial.println("Инициируем точку доступа WiFi");

    // Инициируем точку доступа WiFi
    WiFi.softAP(SSID, PASSWORD);
    IPAddress myIP = WiFi.softAPIP();

    // Выводим IP-адрес Веб-сервера
    Serial.print("IP-адрес точки доступа: ");
    Serial.println(myIP);

    // Инициируем сервер
    webSocket.begin();

    // Метод событий WebSocket
    webSocket.onEvent(webSocketServerEvent);

    Serial.println("Сервер запущен.");

    for (;;)
    {
        try
        {

            webSocket.loop();

            // Если прошло 5 секунд...
            if (millis() % 1000 == 0)
            {

                // Если данные были получены хотя бы один раз
                if (rdata[0] != 0)
                {
                    flag_server = 1;
                    Serial.println("Текущие данные от клиента: ");

                    if (rdata[2] > count)
                    {
                        count = rdata[2];
                    }

                    // Выводим данные в последовательный порт
                    for (size_t i = 0; i < glen; i++)
                    {
                        Serial.println(rdata[i]);
                    }
                    Serial.println();
                }
            }
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskWebSocketServer");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskWebSocketServer end");
    vTaskDelete(NULL);
}
