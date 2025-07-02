#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Membaca sensor...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float suhu = dht.readTemperature();==
  float hum = dht.readHumidity();

  if (isnan(suhu) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    Serial.println("Sensor tidak terbaca");
    delay(2000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print("  | Kelembapan: ");
  Serial.println(hum);

  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhu);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("RH: ");
  lcd.print(hum);
  lcd.print(" %");

  delay(2000);
}
