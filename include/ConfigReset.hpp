/**********************************************/
void configReset(){
    /* ------------------- CLIENTE -------------------- */
    strlcpy(id, "ESP32_ADMIN", sizeof(id));
    strlcpy(ssid, "MIWIFI_aRkF", sizeof(ssid));
    strlcpy(pw, "uDr63hce", sizeof(pw));

    /* ------------------- AP -------------------- */
    strlcpy(nameap, deviceID().c_str(), sizeof(nameap));
    strlcpy(passwordap, "iotcubaelectronica", sizeof(passwordap));

    /* ------------------- UMBRAL TEMPERATURAS -------------------- */
    umbralTemp1 = -14;
    umbralTemp2 = -14;
    umbralTemp3 = -14;
    umbralTemp4 = -14;

    /* ------------------- TELEGRAM -------------------- */
    strlcpy(BOT_TOKEN, "2026069004:AAG2J6w3fPV32riTVTtbAtB2VPUA4QzAHpw", sizeof(BOT_TOKEN));
    strlcpy(CHAT_ID, "1174064360", sizeof(CHAT_ID));
}