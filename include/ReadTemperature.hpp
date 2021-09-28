String readTemperature() {
  tempFrigo1 = random(-18, -8);
  tempFrigo2 = random(-18, -8);
  tempFrigo3 = random(-18, -8);
  tempFrigo4 = random(-18, -8);

  ultActu = rtc.getTime("%H:%M");

  return String(tempFrigo1) + "@" + String(tempFrigo2) + "@" 
      + String(tempFrigo3) + "@" + String(tempFrigo4) + "@" + ultActu;
}