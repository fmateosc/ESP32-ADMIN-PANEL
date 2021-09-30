/**************** Librerias *************************/
#include <Arduino.h>
#include <Colors.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include "esp32-hal-cpu.h"
#include <DNSServer.h>
#include <NTPClient.h>
#include <ESP32Time.h>
#include <Separador.h>
#include <HTTPClient.h>


/************** Archivos de Apoyo ******************/
#include "header.hpp"
#include "functions.hpp"
#include "ConfigReset.hpp"
#include "ConfigRead.hpp"
#include "ConfigSave.hpp"
#include "ESP32_WIFI.hpp"
#include "ReadTemperature.hpp"
#include "ConfigRtc.hpp"
#include "Server.hpp"

// Telegram bot token
#define BOT_TOKEN "2026069004:AAG2J6w3fPV32riTVTtbAtB2VPUA4QzAHpw"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

/************** Definición de funciones ******************/
void sendMessageBotTelegram(String frigorifico, int tempFrigo, int tempUmbral);
void sendMessageBotWatsApp(String frigorifico, int tempFrigo, int tempUmbral);
void postData();

/************** Setup ******************/
void setup() {
  /* SERIAL BAUDRATE */
  Serial.begin(115200);

  /* CPU FREQU */
  setCpuFrequencyMhz(240);

  Serial.println(Blue + "\n\nIniciando setup");
  
  /* SPIFFS */                  
  if (!SPIFFS.begin()){
    Serial.print(Red + "\n\nFallo inicializando SPIFFS");

    while (true);
  }

  /* Lee la Configuración */
  configRead();

  /* Guarda la Configuración */
  configSave();

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  /* Configuracion WIFI */
  WiFi.disconnect(true);

  delay(1000);

  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
  
  configWiFi();

  /* Actualizamos la fecha y hora */
  configRtc();

  /* Iniciamos el Server */
  InitServer();

  /* Temperatura de los frigorificos */
  readTemperature();

  /* Listo */
  Serial.println(Blue + "Setup completado");
}

/************** Bucle Infinito ******************/
void loop() {  
  /************ Leer la temp del CPU *************/
  TempCPU = (temprature_sens_read() - 32) / 1.8;

  // Comprobamos si la temperatura de los frigorificos ha superado el umbral
  // En caso positivo enviamos un mensaje al bot de Telegram
  if (millis() > lastTimeBotRan + readTemperatureDelay) {
    if (tempFrigo1 > umbralTemp1) {
      //sendMessageBotTelegram("frigorífico 1", tempFrigo1, umbralTemp1);
      sendMessageBotWatsApp("frigorífico 1", tempFrigo1, umbralTemp1);
    }

    if (tempFrigo2 > umbralTemp2) {
      //sendMessageBotTelegram("frigorífico 2", tempFrigo2, umbralTemp2);
      sendMessageBotWatsApp("frigorífico 2", tempFrigo2, umbralTemp2);
    }

    if (tempFrigo3 > umbralTemp3) {
      //sendMessageBotTelegram("frigorífico 3", tempFrigo3, umbralTemp3);
      sendMessageBotWatsApp("frigorífico 3", tempFrigo3, umbralTemp3);
    }

    if (tempFrigo4 > umbralTemp4) {
      //sendMessageBotTelegram("frigorífico 4", tempFrigo4, umbralTemp4);
      sendMessageBotWatsApp("frigorífico 4", tempFrigo4, umbralTemp4);
    }

    lastTimeBotRan = millis();    
  }
}

/************** ENVIAR MENSAJE BOT TELEGRAM ******************/
void sendMessageBotTelegram(String frigorifico, int tempFrigo, int tempUmbral){ 
  messageBot = "\n\n\nLa temperatura del " + frigorifico + " (" + String(tempFrigo) + " ºC)"; 
    messageBot += " ha superado la del umbral (" + String(tempUmbral) + " ºC)"; 

  Serial.println(messageBot);  

  bot.sendMessage(CHAT_ID, messageBot, "");

  delay(1000);  
}

void sendMessageBotWatsApp(String frigorifico, int tempFrigo, int tempUmbral) {
  messageBot = "\n\n\nLa temperatura del " + frigorifico + " (" + String(tempFrigo) + " ºC)"; 
    messageBot += " ha superado la del umbral (" + String(tempUmbral) + " ºC)";

  // Adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" 
    + String(phoneNumber) 
    + "&apikey=" 
    + String(apiKey) 
    + "&text=" 
    + urlencode(messageBot);

  // Calling postData to run the above-generated url once so that you will receive a message.
  postData(); 
}

void postData(){
  // Declare object of class HTTPClient
  HTTPClient http;  

  // begin the HTTPClient object with generated url
  http.begin(url);  

  // Finaly Post the URL with this function and it will store the http code
  httpCode = http.POST(url); 

  Serial.println(httpCode);
}

