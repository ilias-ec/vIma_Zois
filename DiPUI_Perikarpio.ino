//
// DiPUI - Γυμνάσιο Κανήθου
//

// Sensor MPU6050 - 3 axes Accel/Gyro
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
float f_X, f_Y , f_Z;
int flag = 1;
//////////////////////////////////////

// Heart Pulse Sensor
int pulsePin = A0;
int blinkPin = 13;
volatile int BPM;
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false;
volatile boolean QS = false;
static boolean serialVisual = true;
volatile int rate[10];
volatile unsigned long sampleCounter = 0;
volatile unsigned long lastBeatTime = 0;
volatile int P = 512;
volatile int T = 512;
volatile int thresh = 525;
volatile int amp = 100;
volatile boolean firstBeat = true;
volatile boolean secondBeat = false;
////////////////////////////////////////

// 433MHz RF Transmitter
#include <RH_ASK.h>
#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver;
////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Sensor MPU6050 - 3 axes Accel/Gyro
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // Heart Pulse Sensor
  pinMode(blinkPin, OUTPUT);
  interruptSetup();
  // 433MHz RF Transmitter
  if (!driver.init())
    Serial.println("init failed");

}

void loop()
{
  // Sensor MPU6050 - 3 axes Accel/Gyro
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
  //delay(500);
  if (flag == 1)
  {
    f_X = mpu6050.getAngleX();
    f_Y = mpu6050.getAngleY();
    f_Z = mpu6050.getAngleZ();
    Serial.println(f_X);
    Serial.println(f_Y);
    Serial.println(f_Z);
    flag = 0;
    f_X = f_X * 1.01;
    f_Y = f_Y * 1.01;
    f_Z = f_Z * 1.01;
  }
  if (mpu6050.getAngleX() > f_X && mpu6050.getAngleY() > f_Y && mpu6050.getAngleZ() > f_Z )
  {
    Serial.print("A man/woman FELL!!!!");
    const char *msgF = "";
    const char *msgFE = "";
    Serial.println(dtostrf(999, 6, 0, msgF));
    msgFE = dtostrf(999, 6, 0, msgF);
    driver.send((uint8_t *)msgFE, strlen(msgFE));
    driver.waitPacketSent();
    //delay(500);
  }
  ///////////////////////////////////////////
  // Heart Pulse Sensor
  serialOutput();
  if (QS == true)
  {
    serialOutputWhenBeatHappens();
    QS = false;
  }
  delay(20);

}
//////////////////////////////////////////////////////////////////////////////
// Heart Pulse Sensor
void interruptSetup()
{
  TCCR2A = 0x02;
  TCCR2B = 0x06;
  OCR2A = 0X7C;
  TIMSK2 = 0x02;
  sei();
}

void serialOutput()
{
  if (serialVisual == true)
  {
    arduinoSerialMonitorVisual('-', Signal);
  }
  else
  {
    sendDataToSerial('S', Signal);
  }
}

void serialOutputWhenBeatHappens()
{
  if (serialVisual == true)
  {
    Serial.print(" Heart-Beat Found ");
    Serial.print("BPM: ");
    Serial.println(BPM);
    if ( BPM > 160)
    {
      const char *msg1 = "";
      const char *msg = "";
      Serial.println(dtostrf(BPM, 6, 0, msg1));
      msg = dtostrf(BPM, 6, 0, msg1);
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      //delay(500);
    }
  }
  else
  {
    sendDataToSerial('B', BPM);
    sendDataToSerial('Q', IBI);
  }
}

void arduinoSerialMonitorVisual(char symbol, int data )
{
  const int sensorMin = 0;
  const int sensorMax = 1024;
  int sensorReading = data;
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);
}


void sendDataToSerial(char symbol, int data )
{
  Serial.print(symbol);
  Serial.println(data);
}

ISR(TIMER2_COMPA_vect)
{
  cli();
  Signal = analogRead(pulsePin);
  sampleCounter += 2;
  int N = sampleCounter - lastBeatTime;
  if (Signal < thresh && N > (IBI / 5) * 3)
  {
    if (Signal < T)
    {
      T = Signal;
    }
  }

  if (Signal > thresh && Signal > P)
  {
    P = Signal;
  }
  if (N > 250)
  {
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI / 5) * 3) )
    {
      Pulse = true;
      digitalWrite(blinkPin, HIGH);
      IBI = sampleCounter - lastBeatTime;
      lastBeatTime = sampleCounter;

      if (secondBeat)
      {
        secondBeat = false;
        for (int i = 0; i <= 9; i++)
        {
          rate[i] = IBI;
        }
      }

      if (firstBeat)
      {
        firstBeat = false;
        secondBeat = true;
        sei();
        return;
      }

      word runningTotal = 0;
      for (int i = 0; i <= 8; i++)
      {
        rate[i] = rate[i + 1];
        runningTotal += rate[i];
      }

      rate[9] = IBI;
      runningTotal += rate[9];
      runningTotal /= 10;
      BPM = 60000 / runningTotal;
      QS = true;
    }
  }

  if (Signal < thresh && Pulse == true)
  {
    digitalWrite(blinkPin, LOW);
    Pulse = false;
    amp = P - T;
    thresh = amp / 2 + T;
    P = thresh;
    T = thresh;
  }

  if (N > 2500)
  {
    thresh = 512;
    P = 512;
    T = 512;
    lastBeatTime = sampleCounter;
    firstBeat = true;
    secondBeat = false;
  }

  sei();
}
