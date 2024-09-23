#include "TaskWebSocketClient.hpp"

static const char *TAG = __FILE__;

extern int count, SOUND_FREEZE, HP;
extern bool flag_client;
// Определяем адрес сервера
const char *ADDR = "192.168.4.1";

// Определяем url подключения
const char *URL = "/";

// Определяем порт
const uint16_t PORT = 81;

// Создаём массив для отправки
int sdata1[3]{0, 0, 0};

// Создаём массив для получения
unsigned long rdata1[3]{0};

// Кол-во элементов массива для получения
const size_t glen = sizeof(rdata1) / sizeof(rdata1[0]);

// Создаём экземпляр класса клиента
WebSocketsClient webSocketClient;

/* Callback функция события WebSocket.
 * Парамтетры:
 * type - тип событыя
 * payload - указатель на данные
 * length - размер данных
 */
void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{

    // Если тип данных двоичный и размер больше нуля
    if (type == WStype_BIN && length > 0)
    {

        // Преобразуем данные из байтов в десятичные числа без знака
        const unsigned long *tmp = (unsigned long *)payload;

        // Вычисляем размер данных в новом формате
        const size_t len = length / sizeof(*rdata1);

        // Записываем в глобальную переменную
        for (size_t i = 0; i < len && i < glen; i++)
        {
            rdata1[i] = tmp[i];
        }
        Serial.println();
    }
}

void WiFi_connect()
{

    // Устанавливаем режим работы в качестве клиента
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    // Ждём подключения WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.print("IP адрес: ");
    Serial.println(WiFi.localIP());

    // Подключаемся к серверу
    webSocketClient.begin(ADDR, PORT, URL);

    // Метод событий WebSocket
    webSocketClient.onEvent(webSocketEvent);

    // Если соединение прервано, повторить попытку через 5 сек.
    webSocketClient.setReconnectInterval(5000);
}

void TaskWebSocketClient(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "%s", "TaskWebSocketClient start");
    WiFi_connect();
    for (;;)
    {
        try
        {
            // vTaskDelay(10);

            // Цикл WebSocket
            webSocketClient.loop();

            // Если прошла одна секунда и сервер хотя бы раз прислал данные
            if (millis() % 1000 == 0)
            {
                flag_client = 1;
                // Отвечаем клиенту
                sdata1[0] = HP;
                sdata1[1] = SOUND_FREEZE;
                sdata1[2] = count;
                // Отправляем данные в двоичном формате серверу
                webSocketClient.sendBIN((uint8_t *)sdata1, sizeof(sdata1));

                Serial.println("Данные отправлены.");

                // Если данные сервера были получены хотябы один раз
                if (rdata1[0] != 0)
                {

                    Serial.println("Текущие данные сервера:");

                    if (rdata1[0] > HP)
                    {
                        HP = rdata1[0];
                    }
                    if (rdata1[1] > SOUND_FREEZE)
                    {
                        SOUND_FREEZE = rdata1[1];
                    }
                    if (rdata1[2] > count)
                    {
                        count = rdata1[2];
                    }

                    // Выводим массив данных в последовательный порт
                    for (size_t i = 0; i < glen; i++)
                        Serial.println(rdata1[i]);
                }
            }
            // Если соединение WiFi прервано
            if (WiFi.status() != WL_CONNECTED)

                // Вызываем функцию setup(), для повторного подключения
                WiFi_connect();
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "%s", "Crash TaskWebSocketClient");
        }
    }
    ESP_LOGE(TAG, "%s", "TaskWebSocketClient end");
    vTaskDelete(NULL);
}
