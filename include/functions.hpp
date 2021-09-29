/* Funciones Personalizadas YHP */

/**********************************************/
/*  Genera un log en el puerto Serial */
void log(String s){
    Serial.println(s);
}
/**********************************************/
/*  Retorna IPAddress en formato "n.n.n.n" de IP a String */
String ipStr(const IPAddress &ip){    
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}
/**********************************************/
/*  De HEX a String */
String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}
/**********************************************/
/*  Create a Unique ID from MAC address */
String idUnique(){
    // Retorna los ultimos 4 Bytes del MAC rotados
    char idunique[15]; 
    uint64_t chipid = ESP.getEfuseMac();           
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}
/**********************************************/
// ID del Dispositivo para La Base de Datos
const String device_id = hexStr(ESP.getEfuseMac()) + "CE" + String(idUnique()); 
/*  ESP32 utiliza funcion getEfuseMac() */
String deviceID(){
    return "ESP32" + hexStr(ESP.getEfuseMac()) + String(idUnique());
}

/**********************************************/
// Function used for encoding the url
String urlencode(String str) {
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
        if (c == ' '){
        encodedString+= '+';
        } else if (isalnum(c)){
        encodedString+=c;
        } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
        }

        yield();
    }

    return encodedString;
}


