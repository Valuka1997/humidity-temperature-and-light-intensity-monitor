#include <LiquidCrystal.h>
#include <DHT.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);



#define DHTPIN 6
#define LDR_PIN A0
#define DHTTYPE    DHT11

char data = 0;
int ldr_read = 0;

DHT dht(DHTPIN, DHTTYPE);


float tem = dht.readTemperature();
float hum = dht.readHumidity();

void setup()

{
  Serial.begin(115200);
  lcd.begin(16, 2);
  dht.begin();
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