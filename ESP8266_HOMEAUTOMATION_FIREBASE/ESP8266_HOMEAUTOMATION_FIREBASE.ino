#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "ACS712.h"
#include <Servo.h>
Servo servo;
//1. Change the following info
#define WIFI_SSID " "// your wifi connection name
#define WIFI_PASSWORD " "// your wifi connection password
#define FIREBASE_HOST " "// your firebase host link
#define FIREBASE_AUTH " "// your firebase authentication key

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData fbdo;

#define Relay1 D7  //D1
#define Relay2 D6  //D2
#define Relay3 D5  //D3
#define Relay4 D4 //D4

#define Relay5 D0  //D5
#define Relay6 D1  //D6
#define Relay7 D2  //D7
#define Relay8 D3  //D8

ACS712 sensor1(ACS712_20A, A0);

int I1;

int rel1,rel2,rel3,rel4,rel5,rel6,rel7,rel8;


void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);
  pinMode(Relay5,OUTPUT);
  pinMode(Relay6,OUTPUT);
  pinMode(Relay7,OUTPUT);
  pinMode(Relay8,OUTPUT);
  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);
  digitalWrite(Relay5,HIGH);
  digitalWrite(Relay6,HIGH);
  digitalWrite(Relay7,HIGH);
  digitalWrite(Relay8,HIGH);
  servo.attach(D8);
  servo.write(60);
  sensor1.calibrate();

  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  //5. Try to set int data to Firebase
  //The set function returns bool for the status of operation
  //fbdo requires for sending the data
  if(Firebase.setInt(fbdo, "/LED_Status", 0))
  {
    //Success
     Serial.println("Set int data success");

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in setInt, ");
    Serial.println(fbdo.errorReason());
  }


  //6. Try to get int data from Firebase
  //The get function returns bool for the status of operation
  //fbdo requires for receiving the data
  if(Firebase.getInt(fbdo, "/LED_Status"))
  {
    //Success
    Serial.print("Get int data success, int = ");
    Serial.println(fbdo.intData());

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }

  /*

  In case where you want to set other data types i.e. bool, float, double and String, you can use setBool, setFloat, setDouble and setString.
  If you want to get data which you known its type at specific node, use getInt, getBool, getFloat, getDouble, getString.
  If you don't know the data type at specific node, use get and check its type.

  The following shows how to get the variant data

  */

 if(Firebase.get(fbdo, "/LED_Status"))
  {
    //Success
    Serial.print("Get variant data success, type = ");
    Serial.println(fbdo.dataType());

    if(fbdo.dataType() == "int"){
      Serial.print("data = ");
      Serial.println(fbdo.intData());
    }else if(fbdo.dataType() == "bool"){
      if(fbdo.boolData())
        Serial.println("data = true");
      else
        Serial.println("data = false");
    }

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in get, ");
    Serial.println(fbdo.errorReason());
  }



}

void loop()
{
   if(Firebase.getInt(fbdo, "/LED1"))
  {
    //Success
    Serial.print("data success, LED1 = ");
    Serial.println(fbdo.intData());
   
    if (fbdo.intData()==1){
    digitalWrite(Relay1, LOW);
    Serial.println("RELAY 1 ONN");
    }
    else{
      digitalWrite(Relay1, HIGH);
      Serial.println("RELAY 1 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in LED1, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/LED2"))
  {
    //Success
    Serial.print("data success, LED2 = ");
    Serial.println(fbdo.intData());
    
    if (fbdo.intData()==1){
    digitalWrite(Relay2, LOW);
    Serial.println("RELAY 2 ONN");
    }
    else{
      digitalWrite(Relay2, HIGH);
      Serial.println("RELAY 2 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in LED2, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/LED3"))
  {
    //Success
    Serial.print("data success, LED3 = ");
    Serial.println(fbdo.intData());

    if (fbdo.intData()==1){
    digitalWrite(Relay3, LOW);
    Serial.println("RELAY 3 ONN");
    }
    else{
      digitalWrite(Relay3, HIGH);
      Serial.println("RELAY 3 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in LED3, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/LED4"))
  {
    //Success
    Serial.print("data success, LED4 = ");
    Serial.println(fbdo.intData());
    
    if (fbdo.intData()==1){
    digitalWrite(Relay4, LOW);
    Serial.println("RELAY 4 ONN");
    }
    else{
      digitalWrite(Relay4, HIGH);
      Serial.println("RELAY 4 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in LED4, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/FAN1"))
  {
    //Success
    Serial.print("data success, FAN1 = ");
    Serial.println(fbdo.intData());

    if (fbdo.intData()==1){
    digitalWrite(Relay5, LOW);
    Serial.println("FAN 1 ONN");
    }
    else{
      digitalWrite(Relay5, HIGH);
      Serial.println("FAN 1 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in FAN1, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/FAN2"))
  {
    //Success
    Serial.print("data success, FAN2 = ");
    Serial.println(fbdo.intData());

      if (fbdo.intData()==1){
    digitalWrite(Relay6, LOW);
    Serial.println("FAN 2 ONN");
    }
    else{
      digitalWrite(Relay6, HIGH);
      Serial.println("FAN 2 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in FAN2, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/FAN3"))
  {
    //Success
    Serial.print("Gdata success, FAN3 = ");
    Serial.println(fbdo.intData());

      if (fbdo.intData()==1){
    digitalWrite(Relay7, LOW);
    Serial.println("FAN 3 ONN");
    }
    else{
      digitalWrite(Relay7, HIGH);
      Serial.println("FAN 3 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in FAN3, ");
    Serial.println(fbdo.errorReason());
  }
  
  if(Firebase.getInt(fbdo, "/FAN4"))
  {
    //Success
    Serial.print("data success, FAN4 = ");
    Serial.println(fbdo.intData());

       if (fbdo.intData()==1){
    digitalWrite(Relay8, LOW);
    Serial.println("FAN 4 ONN");
    }
    else{
      digitalWrite(Relay8, HIGH);
      Serial.println("FAN 4 OFF");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in FAN4, ");
    Serial.println(fbdo.errorReason());
  }
  
    if(Firebase.getInt(fbdo, "/Door"))
  {
    //Success
    Serial.print("data success, DOOR = ");
    Serial.println(fbdo.intData());

       if (fbdo.intData()==1){
    servo.attach(D8);
    servo.write(140);
    Serial.println("DOOR OPEN");
    }
    else{
    servo.attach(D8);
    servo.write(60);
    Serial.println("DOOR CLOSED");
    }
  }
  else{
    //Failed?, get the error reason from fbdo
    Serial.print("Error in FAN4, ");
    Serial.println(fbdo.errorReason());
  }
  delay(2000);
  float I = sensor1.getCurrentDC();
  Serial.println(I);
  I1 = sensor1.getCurrentDC();
  int i= -I1;
  Serial.print("I =");
  Serial.println(i);
 // String I = String(I1) + String("Amp");
 // Firebase.pushString(fbdo,"/Load_Value",I);
  if(Firebase.setInt(fbdo, "/Load_Value",i))
  {
    //Success
     Serial.println("Load data success");

  }else{
    //Failed?, get the error reason from fbdo
   
    Serial.print("Error in Load Value, ");
    Serial.println(fbdo.errorReason());
    }
    delay(2000);
  
}
