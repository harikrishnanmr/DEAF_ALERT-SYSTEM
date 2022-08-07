const int sampleWindow = 50;
unsigned int sensorA;
unsigned int sensorB;
unsigned int sensorC;
unsigned int sensorD;
int leftLedPin=12;
int rightLedPin=13;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long startMillis = millis();
 
  unsigned int peakToPeakA = 0;
  unsigned int maxA = 0;
  unsigned int minA = 1024;
  double voltsA;

  unsigned int peakToPeakB = 0;
  unsigned int maxB = 0;
  unsigned int minB = 1024;
  double voltsB;

  unsigned int peakToPeakC = 0;
  unsigned int maxC = 0;
  unsigned int minC = 1024;
  double voltsC;

  unsigned int peakToPeakD = 0;
  unsigned int maxD = 0;
  unsigned int minD = 1024;
  double voltsD;

  while (millis() - startMillis < sampleWindow)
  {
    sensorA = analogRead(A0);
    sensorB = analogRead(A1);
    sensorC = analogRead(A2);
    sensorD = analogRead(A3);
    //Serial.print("sensor c -> ");
    //Serial.println(sensorC);
    if (sensorA < 1024)
    {
      if (sensorA > maxA)
      {
        maxA = sensorA;
      }
      else if (sensorA < minA)
      {
        minA = sensorA;
      }
    }
   
    if (sensorB < 1024)
    {
      if (sensorB > maxB)
      {
        maxB = sensorB;
      }
      else if (sensorB < minB)
      {
        minB = sensorB;
      }
    }

    if (sensorC < 1024)
    {
      if (sensorC > maxC)
      {
        maxC = sensorC;
      }
      else if (sensorC < minC)
      {
        minC = sensorC;
      }
    }
       if (sensorD < 1024)
    {
      if (sensorD > maxD)
      {
        maxD = sensorD;
      }
      else if (sensorD < minD)
      {
        minD = sensorD;
      }
    }
  }

  peakToPeakA = maxA - minA;
  double voltA = (peakToPeakA * 5.0) / 1024;

  peakToPeakB = maxB - minB;
  double voltB = (peakToPeakB * 5.0) / 1024;

  peakToPeakC = maxC - minC;
  double voltC = (peakToPeakC * 5.0) / 1024;

  peakToPeakD = maxD - minD;
  double voltD = (peakToPeakD * 5.0) / 1024;
  /*
  Serial.print("voltA -> ");
  Serial.print(voltA);
  Serial.print("   voltB -> ");
  Serial.print(voltB);
  Serial.print("   voltC -> ");
  Serial.print(voltC);
  Serial.print("   voltD -> ");
  Serial.println(voltD);
  */
  if(voltA + voltB + voltC + voltD > 0.09) {
      if(voltA > voltB and voltA > voltC and voltA > voltD){
      digitalWrite(leftLedPin, LOW);
      digitalWrite(rightLedPin, HIGH);  
      Serial.print("A  ");
     // Serial.print(voltA - voltB);
     
      Serial.print("   voltA -> ");
      Serial.print(voltA);
      Serial.print("   voltB -> ");
      Serial.print(voltB);
      Serial.print("   voltC -> ");
      Serial.print(voltC);
      Serial.print("   voltD -> ");
      Serial.println(voltD);
    } else if (voltB > voltA and voltB > voltC  and voltB > voltD) {
      digitalWrite(leftLedPin, HIGH);
      digitalWrite(rightLedPin,   LOW);
      Serial.print("B  ");
      //Serial.print(voltB - voltA);
      Serial.print("   voltA -> ");
      Serial.print(voltA);
      Serial.print("   voltB -> ");
      Serial.print(voltB);
      Serial.print("   voltC -> ");
      Serial.print(voltC);
      Serial.print("   voltD -> ");
      Serial.println(voltD);
    }
    else if(voltC > voltA and voltC > voltB  and voltC > voltD)
    {
      //digitalWrite(leftLedPin, HIGH);
      //digitalWrite(rightLedPin, LOW);
      Serial.print("C  ");
      //Serial.print(voltB - voltA);
      Serial.print("   voltA -> ");
      Serial.print(voltA);
      Serial.print("   voltB -> ");
      Serial.print(voltB);
      Serial.print("   voltC -> ");
      Serial.print(voltC);
      Serial.print("   voltD -> ");
      Serial.println(voltD);
    }
    else
    {
      Serial.print("D  ");
      Serial.print("   voltA -> ");
      Serial.print(voltA);
      Serial.print("   voltB -> ");
      Serial.print(voltB);
      Serial.print("   voltC -> ");
      Serial.print(voltC);
      Serial.print("   voltD -> ");
      Serial.println(voltD);
    }
  }
}