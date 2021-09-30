#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define LDR A0
#define WIFI_SSID "myconnection"// your wifi connection Name
#define WIFI_PASSWORD "mypassword"// your wifi password
#define FIREBASE_HOST "myfirebaseconnectionlink"// your firebase Auth link
#define FIREBASE_AUTH "myauthentication" // your firebase authentication

FirebaseData fbdo;


void setup() {
  Serial.begin(115200);
  delay(100);

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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);


}

void loop() {
  int light = analogRead(A0);
  int upload;
  Serial.println(light);
  if(light > 600)
  {
    upload = 0;
  
  }
  else 
  {
    upload = 1;
   
  }

  if(Firebase.setInt(fbdo, "/LDR",upload))
  {
    Serial.println("load data success");
  }
  else{
    Serial.print("Error in load value, ");
    Serial.println(fbdo.errorReason());
  }
    delay(2000);
}
