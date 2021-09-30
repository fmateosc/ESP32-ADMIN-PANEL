/**********************************************/
boolean configRead(){
    // Lee la configuración
    StaticJsonDocument<JSON_CONFIG> jsonConfig;

    File file = SPIFFS.open("/Config.json", "r");

    if (deserializeJson(jsonConfig, file)){
        // Si falla la lectura inicia valores por defecto
        configReset();

        log("\nError: Falló la lectura de la configuración, iniciando valores por defecto");
        
        return false;
    }else{
        /* ------------------- CLIENTE -------------------- */
        strlcpy(id, jsonConfig["id"] | "", sizeof(id));
        strlcpy(ssid, jsonConfig["ssid"] | "", sizeof(ssid));
        strlcpy(pw, jsonConfig["pw"] | "", sizeof(pw));

        /* ------------------- AP -------------------- */
        strlcpy(nameap, jsonConfig["nameap"] | "", sizeof(nameap));
        strlcpy(passwordap, jsonConfig["passwordap"] | "", sizeof(passwordap));

        /* ------------------- UMBRAL TEMPERATURAS -------------------- */
        umbralTemp1 = jsonConfig["umbralTemp1"];
        umbralTemp2 = jsonConfig["umbralTemp2"];
        umbralTemp3 = jsonConfig["umbralTemp3"];
        umbralTemp4 = jsonConfig["umbralTemp4"];

        /* ------------------- TELEGRAM -------------------- */
        strlcpy(CHAT_ID, jsonConfig["CHAT_ID"] | "", sizeof(CHAT_ID));

        /* ------------------- WHATSAPP -------------------- */
        strlcpy(apiKey, jsonConfig["apiKey"] | "", sizeof(apiKey));
        strlcpy(phoneNumber, jsonConfig["phoneNumber"] | "", sizeof(phoneNumber));

        file.close();

        log("\nInfo: Lectura correcta configuración general");

        return true;        
    }
}

