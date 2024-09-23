#include "main.hpp"

static const char *TAG = __FILE__;

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
// TaskHandle_t TaskHandle_4;
// TaskHandle_t TaskHandle_5;
// TaskHandle_t TaskHandle_6;

String cpuId = "";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

void get_cpuID()
{
  ESP_LOGD(TAG, "%s", "Get CpuID start");

  uint64_t chipid = ESP.getEfuseMac();
  cpuId = String((uint16_t)(chipid >> 32)) + String((uint32_t)chipid);

  ESP_LOGD(TAG, "%s", "Get CpuID end");
}

void get_led()
{

  strip.begin(); // Инициализация ленты
  strip.show();  // Обновление ленты
}
void setup()
{

  UART.begin(UART_BAUNDRATE);

  get_cpuID();

  get_led();

  ESP_LOGD(TAG, "--------------------------------------------------------------------------------------------------------------------------------------------");

  ESP_LOGI(TAG, "FIRMWARE NAME       - : %s", FIRMWARE_NAME);
  ESP_LOGI(TAG, "SERIAL NUMBER       - : %s", cpuId.c_str());
  ESP_LOGI(TAG, "VERSION FIRMWARE    - : %s", VERSION_FIRMWARE);

  ESP_LOGI(TAG, "MANUFACTURE         - : %s", MANUFACTURE);
  ESP_LOGI(TAG, "MODEL               - : %s", MODEL);

  ESP_LOGD(TAG, "--------------------------------------------------------------------------------------------------------------------------------------------");

  // xTaskCreate(TaskTest, "TaskModbus", STACK_SIZE_TEST, NULL, 2, &TaskHandle_1);
  xTaskCreate(TaskCounter, "TaskCounter", STACK_SIZE_COUNTER, NULL, 2, &TaskHandle_2);
  xTaskCreate(TaskLed, "TaskLed", STACK_SIZE_LED, NULL, 2, &TaskHandle_3);
}

void loop()
{
}
