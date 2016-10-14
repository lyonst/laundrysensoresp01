void checkSensor(int pin, int *pVal, unsigned long *plastTime, boolean *pAlarm, time_t *palarmTime)
{  
  *pVal = getReading(pin);
 
  if (*pVal > 300) {
    
    *plastTime = millis() + alarmTime;

    if (!*pAlarm) {
      delay(10000);
      *pVal = getReading(pin);

      if (*pVal > 300)
      {
        *pAlarm = true;
        *palarmTime = now();
      }
    }
  }
  else {
    if ((long)(millis() - *plastTime) >= 0 && *pAlarm) {
      *pAlarm = false;
      *palarmTime = now();
    }
  }
}

int getReading(int pin)
{
  Serial.println(pin);

  delay(500);

  if (Serial.available() <= 0)
  {
    return 0;
  }

  String inString = Serial.readString();

  for (int i = 0; i < inString.length(); i++)
  {
    if (isDigit(inString[i]))
    {
      continue; 
    }

    inString[i] = 0;
    return inString.toInt();
  }

  return 0;
}

