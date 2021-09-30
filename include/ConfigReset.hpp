/**********************************************/
void configReset(){
    /* ------------------- CLIENTE -------------------- */
    strlcpy(id, "ESP32_ADMIN", sizeof(id));
    strlcpy(ssid, "MIWIFI_aRkF", sizeof(ssid));
    strlcpy(pw, "uDr63hce", sizeof(pw));

    /* ------------------- AP -------------------- */
    strlcpy(nameap, deviceID().c_str(), sizeof(nameap));
    strlcpy(passwordap, "password", sizeof(passwordap));

    /* ------------------- UMBRAL TEMPERATURAS -------------------- */
    umbralTemp1 = -14;
    umbralTemp2 = -14;
    umbralTemp3 = -14;
    umbralTemp4 = -14;

    /* ------------------- TELEGRAM -------------------- */
    strlcpy(CHAT_ID, "1174064360", sizeof(CHAT_ID));

    /* ------------------- WATSAPP -------------------- */
    strlcpy(apiKey, "730591", sizeof(apiKey));
    strlcpy(phoneNumber, "+34625607134", sizeof(phoneNumber));
}