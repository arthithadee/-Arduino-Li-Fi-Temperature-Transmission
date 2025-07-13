#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define LED_PIN 5
#define LDR_PIN A0

#define BIT_DELAY 1000
#define SAMPLES 10
#define THRESHOLD 200

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("🔁 Li-Fi Temp Transmission + Decoding");
}

void loop() {
  Serial.println("\n🔄 Starting Transmission Cycle");

  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("❌ DHT11 read failed");
    delay(3000);
    return;
  }

  int tempInt = (int)temp;
  String tempStr = String(tempInt);

  Serial.print("📤 Sending Temp: ");
  Serial.println(tempStr);

  String receivedStr = "";

  for (int i = 0; i < tempStr.length(); i++) {
    char c = tempStr[i];
    Serial.print("Sending char: ");
    Serial.println(c);

    byte receivedChar = 0;

    for (int b = 7; b >= 0; b--) {
      bool bitVal = (c >> b) & 1;
      digitalWrite(LED_PIN, bitVal ? HIGH : LOW);

      long sum = 0;
      for (int j = 0; j < SAMPLES; j++) {
        sum += analogRead(LDR_PIN);
        delay(BIT_DELAY / SAMPLES);
      }
      int avg = sum / SAMPLES;
      bool rxBit = (avg > THRESHOLD);
      if (rxBit) receivedChar |= (1 << b);

      Serial.print("  Bit ");
      Serial.print(7 - b);
      Serial.print(": Sent = ");
      Serial.print(bitVal);
      Serial.print(" | LDR avg = ");
      Serial.print(avg);
      Serial.print(" → ");
      Serial.println(rxBit);
    }

    digitalWrite(LED_PIN, LOW);
    receivedStr += (char)receivedChar;
    delay(500);
  }

  Serial.print("📥 Decoded Temp: ");
  Serial.println(receivedStr);
  Serial.println("✅ Transmission complete.");

  delay(5000);
}
