#include "Maxbotix.h"

int sensorCount = 5;
int minDistance = 0;
int maxDistance = 18;
int rangeValue[3] = {0, 0, 0};
int counter[3] = {0, 0, 0};

Maxbotix rangeSensorPW1(5, Maxbotix::PW, Maxbotix::LV);
Maxbotix rangeSensorPW2(6, Maxbotix::PW, Maxbotix::LV);
Maxbotix rangeSensorPW3(7, Maxbotix::PW, Maxbotix::LV);

int resetPin = 12;

void setup()
{
  Serial.begin(115200);

  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  Serial.println("Arduino Ready");
}

void loop()
{

  updateRange();
  //  for (int i = 0; i < sensorCount; i++)
  //  {
  //    Serial.print(i);
  //    Serial.print("\t");
  //    Serial.println(rangeValue[i]);
  //  }
  scan();
//    Serial.println(rangeValue[2]);
}


void updateRange() {
  rangeValue[0] = rangeSensorPW1.getRange();
  rangeValue[1] = rangeSensorPW2.getRange();
  rangeValue[2] = rangeSensorPW3.getRange();
  delay(5);
}

void scan()
{

  for (int i = 0; i < sensorCount; i++) {


    if (rangeValue[i] > minDistance && rangeValue[i] < maxDistance) {
      //      Serial.println(i);
      counter[i]++;
      if (counter[i] == 2) {
        Serial.println(i + 1);
        break;
      }
      else if (counter[i] > 50 && rangeValue[i] != 14) //Reset arduino if value repeated multiple times
      {
        Serial.print("Resetting");
        //        digitalWrite(resetPin, LOW);
      }
      delay(10);
    }
    else {
      counter[i] = 0;
    }
  }
}
