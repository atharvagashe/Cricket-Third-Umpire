/*globaly defined variables appear here*/
const int photoResistorPin = A2;      // the number of the photoresistor pin
const int vibratorPin = 4;            // the number of the vibrator pin
const int ledPin =  13;               // the number of the LED pin
const int thresh = 5;
int photoResistorState = 0;           // variable for reading the photoresistor status
int thresholdValue = 0;               // variable for storing threshold value to compare photoresistor state with
int threshdiff = 0;
int vibratorReading = 0;              //variable for reading ball sensor status
int x = 0;
bool hit = false;
bool ran = false;
bool out;
bool first=true;
bool keepRunning=true;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
  pinMode(photoResistorPin, INPUT);
  pinMode(vibratorPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop(){
  while(keepRunning){
    threshdiff = abs(thresholdValue-analogRead(photoResistorPin));
    if(x%10==0 and (threshdiff<=thresh or first)){
      thresholdValue = analogRead(photoResistorPin)+thresh;
    }
    
    // read the state of the sensor values:
    photoResistorState = analogRead(photoResistorPin);
    vibratorReading = digitalRead(vibratorPin);
  
    while(photoResistorState<thresholdValue and first){
      photoResistorState = analogRead(photoResistorPin);
      Serial.println(photoResistorState);
      delay(200);
    }
      while(photoResistorState>=thresholdValue and first){
      photoResistorState = analogRead(photoResistorPin);
      Serial.println(photoResistorState);    
      delay(200);
    }
    first=false;
   
    if(photoResistorState>=thresholdValue){
      ran = true;
      Serial.println("we out here");
      delay(100);
    }
    if(vibratorReading==1){
      hit = true;
    }
    if(ran) {
      out = false;
      keepRunning = false;
      Serial.println("we here");
    }
    else if(hit) {
      out = true;
      keepRunning = false;
    }
    //output sensor value for debugging
    if(not keepRunning and not out)
      Serial.println("not out \t" + (String)photoResistorState + "\t" + (String)vibratorReading);
    else if(not keepRunning and out)
        Serial.println("out \t" + (String)(photoResistorState-thresholdValue) + "\t" + (String)vibratorReading);
    //Serial.println("out \t" + (String)(photoResistorState) + "\t" + (String)vibratorReading);
      
    /*
      //turn on led if bat is over the sensor
      if(photoResistorState>=thresholdValue){
        digitalWrite(ledPin, HIGH);
        ran = true;
        //stay here until bat is not over photoresistors
        while(photoResistorState>=thresholdValue){
          photoResistorState = analogRead(photoResistorPin);
          delay(100);
        }
      }
      //turn led off once sensor is not covered
      digitalWrite(ledPin, LOW);
    */    
    delay(200);
  }
  digitalWrite(ledPin, HIGH);
  if(not out){
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
