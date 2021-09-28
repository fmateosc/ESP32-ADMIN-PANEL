/**********************************************/
boolean configSave(){
    // Graba configuración
    StaticJsonDocument<JSON_CONFIG> jsonConfig;

    File file = SPIFFS.open("/Config.json", "w+");

    if (file){
        /* ------------------- CLIENTE -------------------- */
        jsonConfig["id"] = id;
        jsonConfig["ssid"] = ssid;
        jsonConfig["pw"] = pw;

        /* ------------------- AP -------------------- */
        jsonConfig["nameap"] = nameap;
        jsonConfig["passwordap"] = passwordap;

        /* ------------------- UMBRAL TEMPERATURAS -------------------- */
        jsonConfig["umbralTemp1"] = umbralTemp1;
        jsonConfig["umbralTemp2"] = umbralTemp2;
        jsonConfig["umbralTemp3"] = umbralTemp3;
        jsonConfig["umbralTemp4"] = umbralTemp4;

        /* ------------------- TELEGRAM BOT -------------------- */
        jsonConfig["CHAT_ID"] = CHAT_ID;

        serializeJsonPretty(jsonConfig, file);

        file.close();

        log("\nInfo: Grabando configuración general");
        
        return true;
    }else{
      log("\nError: Falló el grabado de la configuración general");

      return false;
    }    
}