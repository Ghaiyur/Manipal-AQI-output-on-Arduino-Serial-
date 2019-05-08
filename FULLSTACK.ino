
int measurePin = A5;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;


float voMeasured = 0;
float calcVoltage = 0;
float dustavg = 0;

float avg; // value for moving average
 unsigned long n; // number of samples
  float t;  // value for current sample



void setup()
{
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);

   for (int i = 1; i <= 60; i++)
  {
    delay(1000); // 1s
    Serial.print(i);
    Serial.println(" s (wait 60s for Device to warm up)");
  }
  
  Serial.println("Ready!");

    
}

 void loop()
{
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustavg = (0.17*calcVoltage-0.1)*1000;

  if ( dustavg < 0)
  {
    dustavg = 0.00;
  }

  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);

  Serial.println("Voltage:");
  Serial.println(calcVoltage);

  Serial.println("Dust avg [ug/m3] :");
  Serial.println(dustavg);

  

  // get sample
 t = dustavg;
 // update sample count
 n++;
  //calculate moving average
 avg += (t - avg) / n;

 Serial.println("Average Concentration [ug/m3] : ");
 Serial.println(avg);

 delay(3600000);

unsigned int sycn=',';

  if ( avg == 0 ) {
    Serial.println("AQI : 0 (Good)");
    return 0;
  }
    else if ( avg <=120 ) { 
    int aqi=( 50 - 0 ) * ( avg - 0 ) / ( 120 - 0 ) + 0;
    Serial.println("AQI : ");
    Serial.println(aqi);
    Serial.println("Good");
  }
    else if (avg <=354 ) {
    int aqi= ( 100 - 51 ) * ( avg - 121 ) / ( 354 - 121 ) + 51;
    Serial.println("AQI : ");
    Serial.println(aqi);
    Serial.println("Satisfactory");
  }  
    else if (avg <=554 ) {
    int aqi= ( 150 - 101 ) * ( avg - 355 ) / ( 554 - 355 ) + 101;
    Serial.println("AQI : ");
 Serial.println(aqi);
    Serial.println("Moderately Polluted");

  }
    else if (avg <=1504 ) {
    int aqi= ( 200 - 151 ) * ( avg - 555 ) / ( 1504 - 555 ) + 151;
    Serial.println("AQI : ");
   Serial.println(aqi);
    Serial.println("Poor");
  }
    else if (avg <=2504 ) {
    int aqi= ( 300 - 201 ) * ( avg - 2504 ) / ( 2504 - 1505 ) + 201;
    Serial.println("AQI : ");
  Serial.println(aqi);
    Serial.println("Very Poor");
  }
    else if (avg <=3504 ) {
    int aqi= ( 500 - 401 ) * ( avg - 2505 ) / ( 5004 - 2505 ) + 401;
    Serial.println("AQI : ");
    Serial.println(aqi);
    Serial.println("Severe");
  } } 
    
