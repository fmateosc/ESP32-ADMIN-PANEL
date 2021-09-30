/* Defines */

/* Variables Globales */

// Tamaño del Objeto JSON
const size_t JSON_CONFIG = JSON_OBJECT_SIZE(5) + 500;


// ID del dispositivo           
char id[30];

// Red WiFi
char ssid[30];               
char pw[30];

// Para ssid AP
char nameap[31]; 

// Para ssid AP Password       
char passwordap[63];  

// Variables sensores de temperatura frigoríficos 
int umbralTemp1, umbralTemp2, umbralTemp3, umbralTemp4;
int tempFrigo1, tempFrigo2, tempFrigo3, tempFrigo4;
String ultActu;

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;
int hora;
int minutos;
int segundos;
int dia;
int mes;
int year;

// Variable para Temperatura de CPU
float TempCPU; 

// Telegram
char BOT_TOKEN[50];
char CHAT_ID[11];
String messageBot;

// WatsApp bot
char apiKey[10];
char phoneNumber[20];
String url;
int httpCode;

// Temporizadores
unsigned long lastTimeBotRan;
int readTemperatureDelay = 60000;

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


//Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Crea una instancia del RTC_INTERNO
ESP32Time rtc;   

//Crea una instancia del separador
Separador s;




