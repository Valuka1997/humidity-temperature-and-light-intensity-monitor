#include <LiquidCrystal.h>
#include <dht.h>

const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

dht DHT;

float tem = 0;
float hum = 0;

#define DHT11_PIN D1
#define LDR_PIN A0

char data = 0;
int ldr_read = 0;

void setup()

{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(LDR_PIN, INPUT);
  delay(1000);
}


void loop()

{
  lcd.clear();
  ldr_read = analogRead(LDR_PIN);
  lcd.setCursor(0, 0);
  lcd.print("LDR-");
  lcd.setCursor(4, 0);
  lcd.print(ldr_read);

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  tem = DHT.temperature;
  lcd.setCursor(0, 1);
  lcd.print("Tem-");
  lcd.setCursor(4, 1);
  lcd.print(tem);
  Serial.println(tem);

  Serial.print("Humidity = ");
  hum = DHT.humidity;
  lcd.setCursor(8, 1);
  lcd.print("Hum-");
  lcd.setCursor(12, 1);
  lcd.print(hum);
  Serial.println(hum);  
}
