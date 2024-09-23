#ifndef APP_CONFIG
#define APP_CONFIG

//--------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------ Общие настройки приложения ----------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------//

#define FIRMWARE_NAME "LED_braser" // Название прошивки
#define MANUFACTURE "MOX corp"
#define MODEL "1"
#define VERSION_FIRMWARE "0.3.7"

//--------------------------------------------------------------------------------------------------------------------------//
//------------------------------------- Размеры стека памяти для потоков ---------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------//

#define STACK_SIZE_TEST 8192
#define STACK_SIZE_COUNTER 8192
#define STACK_SIZE_LED 8192
#define STACK_SIZE_WEBSERVER 8192
//--------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------- Настройка интерфейсов связи -----------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------//

#define UART Serial
#define UART_BAUNDRATE 115200

//--------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------- Настройка пинов  ----------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------//

#define PIEZO_SENSOR_PIN 18
#define PIEZO_SOUND_PIN 23
#define GERO_PIN 19

#define PIN_LED        22  // Пин, к которому подключена лента
#define NUM_LEDS   5  // Количество светодиодов в ленте

//--------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------- Настройки LITTLEFS ---------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------//

#define FORMAT_LITTLEFS_IF_FAILED true

#define FILE_SISTEM "/sistem.json"
#define FILE_NETWORK "/network.json"
#define DEFAULT_HP 1
#define DEFAULT_SOUND_FREEZE 500
#define DEFAULT_NETWORK 0
#define DEFAULT_SERVER_NAME "LED_Braser_Server"
#define DEFAULT_TYPE_CONNECTION 0






#endif
