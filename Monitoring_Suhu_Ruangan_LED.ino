#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define LED_MERAH 3
#define LED_HIJAU 4

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();

  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Membaca sensor...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float suhu = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(suhu) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    delay(2000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C | RH: ");
  Serial.print(hum);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(suhu, 1);
  lcd.print("C ");
  lcd.print("H:");
  lcd.print(hum, 1);
  lcd.print("%");

  lcd.setCursor(0, 1);
  if (suhu > 30 && hum > 70) {
    lcd.print("Panas & Lembap");
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
  } else if (suhu > 30 || hum > 70) {
    lcd.print("Tidak Normal");
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
  } else {
    lcd.print("Normal");
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
  }

  delay(3000);
}
