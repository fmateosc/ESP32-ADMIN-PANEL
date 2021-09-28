void configRtc(){
  Serial.println(Blue + "\n\nOBTENIENDO FECHA Y HORA NTP");

  /*------OBTENEMOS LA HORA NTP-----*/
  // Initialize a NTPClient to get time
  timeClient.begin();

  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600);

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);

  Serial.print("FECHA: ");
  Serial.println(dayStamp);

  // Extract time
  timeStamp = formattedDate.substring(splitT + 1, formattedDate.length()-1);
  Serial.print("HORA: ");
  Serial.println(timeStamp);
  
  hora = s.separa(timeStamp, ':', 0).toInt();
  minutos = s.separa(timeStamp, ':', 1).toInt();
  segundos = s.separa(timeStamp, ':', 2).toInt();

  year = s.separa(dayStamp, '-', 0).toInt();
  mes = s.separa(dayStamp, '-', 1).toInt();
  dia = s.separa(dayStamp, '-', 2).toInt();

  /*------ACTUALIZAMOS LA HORA DEL RTC-----*/
  rtc.setTime(segundos, minutos, hora, dia, mes, year);  // (segundos, minutos, hora, dia, mes, año)

  Serial.println("\n\nLa fecha y hora del RTC es: " + rtc.getTime("%d/%m/%Y %H:%M:%S"));
}