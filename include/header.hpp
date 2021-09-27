/* Defines */
//EEPROM
#define EEPROM_SIZE 512 

/* Variables Globales */
// Variable para no bloquear la reconexion del MQTT
long lastSendWS = 0; 
// Tamaño del Objeto JSON
const size_t JSON_CONFIG = JSON_OBJECT_SIZE(5) + 500;
//New mqtt
const size_t JSONMQTT_SIZE = JSON_OBJECT_SIZE(6) + 500; 

// ID del dispositivo           
char id[30];

// Red WiFi
char ssid[30];               
char pw[30];

// Para ssid AP
char nameap[31]; 

// Para ssid AP Password       
char passwordap[63];  

//Temperaturas 
int umbralTemp1, umbralTemp2, umbralTemp3, umbralTemp4;

// Variable para Temperatura de CPU
float TempCPU; 

// Telegram
char BOT_TOKEN[46];
char CHAT_ID[10];


/****************************************
 * Sensor Temp Interno CPU
 ****************************************/
//Para ESP32 temperatura del CPU
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();


/* Instancias */


/****************************************
 * Init DNS
 ****************************************/
const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;



