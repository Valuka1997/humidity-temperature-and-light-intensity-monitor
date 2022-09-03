  #include <LiquidCrystal.h>
#include <DHT.h>

#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

#define FIREBASE_HOST " **** Firebase host link ***** "
#define FIREBASE_AUTH " ****Firebase auth code **** "

#define WIFI_SSID " WIFI router SSID (Name) "
#define WIFI_PASSWORD " WIFI router password "

#define DHTPIN 6
#define LDR_PIN A0
#define DHTTYPE    DHT11

char data = 0;
int ldr_read = 0;

DHT dht(DHTPIN, DHTTYPE);

float tem = dht.readTemperature();
float hum = dht.readHumidity();

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;


void setup(){
  
  Serial.begin(115200);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(LDR_PIN, INPUT);
  delay(1000);
}


void loop(){

  sensorUpdate();
  
  lcd.clear();
  ldr_read = analogRead(LDR_PIN);
  lcd.setCursor(0, 0);
  lcd.print("LDR-");
  lcd.setCursor(4, 0);
  lcd.print(ldr_read);

  lcd.setCursor(0, 1);
  lcd.print("Tem-");
  lcd.setCursor(4, 1);
  lcd.print(tem);

  lcd.setCursor(8, 1);
  lcd.print("Hum-");
  lcd.setCursor(12, 1);
  lcd.print(hum);
  delay(5000);
}

void sensorUpdate(){

  hum = dht.readHumidity();
  tem = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(hum) || isnan(tem)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(tem);
  Serial.print(F("C  ,"));

  if (Firebase.setFloat(firebaseData, "*** Store location ***", tem))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "*** Store location ***", hum))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}
