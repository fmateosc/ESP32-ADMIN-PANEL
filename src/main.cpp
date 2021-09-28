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

  /* Configuracion WIFI */
  WiFi.disconnect(true);

  delay(1000);

  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
  
  configWiFi();

  /* Actualizamos la fecha y hora */
  configRtc();
  
  // Telegram Bot
  WiFiClientSecure secured_client;
  UniversalTelegramBot bot(BOT_TOKEN, secured_client);
  // Add root certificate for api.telegram.org
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);   

  /* Iniciamos el Server */
  InitServer();

  /* Listo */
  Serial.println(Blue + "Setup completado"); 

  bot.sendMessage(CHAT_ID, "Bot inicializado", "");
}

/************** Bucle Infinito ******************/
void loop() {  
  /************ Leer la temp del CPU *************/
  TempCPU = (temprature_sens_read() - 32) / 1.8;
}